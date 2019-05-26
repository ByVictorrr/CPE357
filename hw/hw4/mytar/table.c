#include "header.h"
#include "mytar.h"
static unsigned int OctToInt(const char* str, unsigned int len) {
	unsigned int res = 0;
	unsigned int i;
	for (i = 0; i < len; i++) {
		char c = str[i];
		if (c){
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


void print_table(struct headerEntry* header, int verbose){
	const mode_t mode = OctToInt (header->mode, 7);
	char ownergr[20];
	struct tm * time;
	time_t mtime;
	int j;
	char* typestr = "-hlcbdp-";
	/*test*/
	if(verbose){
		j = header->typeflag? header->typeflag -'0':0;
		const char str[28]= {
			typestr[j],
			mode & S_IRUSR?'r': '-',
			mode & S_IWUSR?'w':'-',
			mode & S_IXUSR?'x':'-',
			mode & S_IRGRP?'r':'-',
			mode & S_IWGRP?'w':'-',
			mode & S_IXGRP?'x':'-',
			mode & S_IROTH?'r':'-',
			mode & S_IWOTH?'w':'-',
			mode & S_IXOTH?'x':'-',
			' ',
			'\0'
			};
		/* Writing Permission 10 Owner/Group 17 */
		strcpy(ownergr, header-> uname);
		strcat(ownergr, header-> gname);
		printf("%s %-17s", str, ownergr);	
		printf("%+8s", header -> size);
		mtime = OctToInt(header -> mtime, 11);
		time = localtime(&mtime);
		printf(" %4d-%02d-%02d %02d:%02d ", time -> tm_year + 1900, time -> tm_mon + 1, time -> tm_mday, time -> tm_hour, time -> tm_min);
	}
	
	printf("%s\n", header -> name);

	if (verbose){
		if(header->typeflag == SYMTYPE){
			printf(" -> %s", header -> linkname);
		}
	}
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
  if((tar= fopen(path, "rb")) == NULL)
  {
    perror(path);
    exit(EXIT_FAILURE);
  }
  int len;

  fseek(tar, 0, SEEK_END);
  len = ftell(tar);
  fseek(tar, 0, SEEK_SET);
  struct headerEntry fileHeader;
  while (ftell(tar) < len)
  {
    fread(&fileHeader, sizeof(fileHeader), 1, tar);
    if (fileHeader.name[0] != '\0')
      print_table(&fileHeader, verbose);
    if (fileHeader.typeflag != '5')
    {
      int content_length = atoi(fileHeader.size) + makeBlockSize(atoi(fileHeader.size));
      fseek(tar, content_length, SEEK_CUR);
    }
  }
  fclose(tar);
  return 0;
}
