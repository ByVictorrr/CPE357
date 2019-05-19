#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>


#define OPTION_SIZE 6
#define HEADER_SIZE 512

enum boolean{FALSE,TRUE};

char header[HEADER_SIZE];

void reset_header(char *header)
{
	for(int i = 0; i< HEADER_SIZE; i++)
		header[i] = '\0';
}
void safe_write(int out_fd, char *data)
{
	if (write(data, out_fd) <= 0)
	{
		perror("write failed");
		exit(EXIT_FAILURE);
	}	
}


void print_file_block(struct dirent *dir_entry, int outFd)
{

	struct stat buff;
	/*Step 1 - use dir-entry to get name of file*

	/Step 2 - use that name to get stat of the file*/
	if(stat(dir_entry->d_name, &buff) <= 0)
	{
		perror("stat didnt work");
		exit(EXIT_FAILURE);
	
	/*step 3 - print that header block (512 bytes)*/
	/*step 3.1 - print name to archieve*/
	safe_write(outFd, dir_entry->d_name);
	/*step 3.2 - write mode_t*/
	safe_write(outFd, buff.st_mode);
	printf("Test size of size of buff: %d", sizeof(buff.st_mode));
	/*Step 3.3 - write uid */
	safe_write(outFd, buff.st_uid);
	/*step 3.4 - write gid */
	safe_write(outFd, buff.st_gid);
	/*step 3.5 - write size */
	safe_write(outFd, buff.st_size);
	/*step 3.6 - write mtime*/
	safe_write(outFd, buff.st_mtime);
	/*step  3.7 - write chksum*/
	safe_write(outFd, getChkSum());




	

	

/*[valid bit|c|t|x|v|f|S]*/
int *get_option(char *options)
{
	int *option_int = (int *)calloc(OPTION_SIZE+1, sizeof(int);

	option_int[0] = TRUE;

	for(int i = 0; i< OPTION_SIZE; i++)
	{	
		switch(options[i])		
		{
			case 'c': /*creation mode - creat archieve*/
				option_int[1] = TRUE;
				break;
			case 't': m    b
				option_int[2] = TRUE;
				break;
			case 'x':
				option_int[3] = TRUE;
				break;
			case 'v':
				option_int[4] = TRUE;
				break;
			case 'f':
				option_int[5] = TRUE;
				break;
			case 'S':
				option_int[6] = TRUE;
				break;
			default:
				option_int[0] = FALSE;
				break;
		}

	}
	return option;
}


int main(int argc, char *argv[])
{
	
	int *option;
	int inFd, outFd;


	/*Options:
	 * c - creat an archieve
	 * t - Print the table of contents of an archieve
	 * x - extract the contents of an archieve
	 * v - increases verbosity
	 * S - Be strict on std compliance
	 */

	
	
	/*Step 1 - validate the command line input
		
	[valid bit|c|t|x|v|f|S]
	
	*/
	if( (argc != 4 || argc != 3) && (option = get_option(argv[1]))[0] == FALSE)
	{
		perror("Usage: mytar [ctxvS]f tarfile [ path [ ... ] ]\n");
		exit(EXIT_FAILURE);
	}

	/*Step 1.1 - check if valid bit is set*/
	if(option[0] == TRUE)
	{
		/*Step 2 - open up the */
		if ((outFd=open(argv[2], O_WRONLY | O_TRUNC | O_CREAT) == -1)
		{
			perror(argv[2]);
			exit(EXIT_FAILURE);
		}
		/*Case: creation and file*/
		if (option[1] == TRUE && option[5])
		{


		}


	}
/*=============================================================*/
	


	
	return 0;
}



