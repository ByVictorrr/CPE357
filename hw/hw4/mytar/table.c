#include "header.h"
#include "entry.h"
#include <stdlib.h>
#define SYMTYPE '2'

static unsigned int OctToInt(const char *str, unsigned int len)
{
	unsigned int res = 0;
	unsigned int i;
	char c;
	for (i = 0; i < len; i++)
	{
		c = str[i];
		if (c)
		{
			res *= 8;
			res += c - '0';
		}
		else
		{
			break;
		}
	}
	return res;
}

uint32_t extract_special_int(char *where, int len) {
/* For interoperability with GNU tar. GNU seems to
* set the high–order bit of the first byte, then
* treat the rest of the field as a binary integer
* in network byte order.
* I don’t know for sure if it’s a 32 or 64–bit int, but for * this version, we’ll only support 32. (well, 31)
* returns the integer on success, –1 on failure.
* In spite of the name of htonl(), it converts int32 t */
	int32_t val= -1;
	if ( (len >= sizeof(val)) && (where[0] & 0x80)) {
	/* the top bit is set and we have space * extract the last four bytes */
	val = (int32_t)(*(where + len - sizeof(val)));
	val = ntohl(val); /* convert to host byte order */ }
	return val; 
}


unsigned long extract_octal(char *where, int len, int strict) {
/* extract an octal value that is either nul– or space–terminated 320
       * increments *err on error.
*/
	char tmpstring[513]; /* used for numeric conversions */ 
	char *end;
	long num;/* make a string that we’re sure is nul–terminated */ 
	memcpy(tmpstring, where, len);
	tmpstring[len] = '\0';
	/* convert the number */
	num = strtol(tmpstring, &end, 8);
	if ( *end !='\0'&& *end !=' ') {
		if ( strict  ) 
				perror("strict");
		else {
	/* see if it’s an encoded int like GNU does */ 
	num = extract_special_int(where, len);
			if ( num < 0 )
					perror("extract octal");
		} 
	}
	return num; 
}


void print_table(headerEntry *header, int verbose)
{
	const mode_t mode = OctToInt((char *)header->mode, 7);
	char ownergr[20];
	struct tm *time;
	time_t mtime;
	int j;
	char *typestr = "-hlcbdp-";
	/*test*/
	if (verbose)
	{
		j = header->typeflag ? header->typeflag - '0' : 0;
		const char str[28] = {
				typestr[j],
				mode & S_IRUSR ? 'r' : '-',
				mode & S_IWUSR ? 'w' : '-',
				mode & S_IXUSR ? 'x' : '-',
				mode & S_IRGRP ? 'r' : '-',
				mode & S_IWGRP ? 'w' : '-',
				mode & S_IXGRP ? 'x' : '-',
				mode & S_IROTH ? 'r' : '-',
				mode & S_IWOTH ? 'w' : '-',
				mode & S_IXOTH ? 'x' : '-',
				' ',
				'\0'};
		/* Writing Permission 10 Owner/Group 17 */
		strcpy(ownergr, (char *)header->uname);
		strcat(ownergr, (char *)header->gname);
		printf("%s %-17s", str, ownergr);
		printf("%8d", (int)extract_octal((char *)header -> size, 11, 0));
		mtime = extract_octal((char *)header -> mtime, 11, 0);
		/*mtime = OctToInt(header -> mtime, 11);*/
		time = localtime(&mtime);
		printf(" %4d-%02d-%02d %02d:%02d ", time->tm_year + 1900, time->tm_mon + 1, time->tm_mday, time->tm_hour, time->tm_min);
	}

	printf("%s", header->name);

	if (verbose)
	{
		if (header->typeflag == SYMTYPE)
		{
			printf(" -> %s", header->linkname);
		}
	}
	printf("\n");
}
int makeBlockSize(int x)
{
	if (x == 512)
		return 0;
	else
		return (512 - (x % 512));
}

int table(char *path, int verbose)
{
	FILE *tar;
	int fileInnerds;
	int len;
	if ((tar = fopen(path, "rb")) == NULL)
	{
		perror(path);
		exit(EXIT_FAILURE);
	}

	fseek(tar, 0, SEEK_END);
	len = ftell(tar);
	fseek(tar, 0, SEEK_SET);
	headerEntry fileHeader;
	while (ftell(tar) < len)
	{
		fread(&fileHeader, sizeof(fileHeader), 1, tar);
		if (fileHeader.name[0] != '\0')
			print_table(&fileHeader, verbose);
		if (fileHeader.typeflag != '5')
		{
			fileInnerds = atoi(fileHeader.size) + makeBlockSize(atoi((char *)fileHeader.size));
			fseek(tar, fileInnerds, SEEK_CUR);
		}
	}
	fclose(tar);
	return 0;
}

int main()
{

	headerEntry header_entry;

	char *pathname = "inputs/header/test2";
	char *tarPath = "outputs/header/test2.tar";
	int tarFd = open(tarPath, O_RDWR | O_CREAT | O_TRUNC, 0666);
	add_entry(pathname, tarFd, header_entry);
	table(tarPath, 1);
	return 0;
}
