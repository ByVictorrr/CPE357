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




	

	
	
	/*step 4 - print the content blocks (512 bytes per block)*/

	/*step 5 - print */

}


/*has to be recursive*/
void creat_Archieve(char *path)
{
	struct stat file_info;
	DIR *dp;
	struct dirent *dir_entry;
	
	/*Step 1 - determine if the path is a file or directory*/
	if(stat(path, &file_info) <= 0)
	{
		perror("stat failed");
		exit(EXIT_FAILURE);
	}
	/*Step 2 - determine What type of file it is*/
	if (S_ISDIR(file_info.st_mode))
	{
		/*Step 3 - open directoy*/
		if((dp = opendir(path)) <= 0)
		{
			perror("no able to open directory");
			exit(EXIT_FAILURE);
		}

		/*Step 4 - iterate through each entry of the directory*/
		while ((dir_entry = readdir(dp)) != NULL)
		{
			/*get info about file*/
			if (stat(dir_entry->d_name, &file_info) <= 0)
			{
				/* code */
			}
			/*Case 1 - entry could be another directoy*/


			/*case 2 - reg file */


			/*case 3 - symlin*/
		}
		
	}
	else if(S_ISREG(file_info.st_mode))
	{

	}
	else if (S_ISLNK(file_info.st_mode))
	{

	}else{ /*accepting no other file types*/
		perror("not accepting type of file");
		exit(EXIT_FAILURE);
	}
}


/*[valid bit|c|t|x|v|f|S]*/
int *get_option(char *options)
{
	int *option_int = (int *)calloc(OPTION_SIZE+1, sizeof(int);

	option_int[0] = TRUE;

	for(int i = 0; i< OPTION_SIZE; i++)
	{	
		switch(options[i])		
		{
			case 'c':
				option_int[1] = TRUE;
				break;
			case 't':
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
	char *usage = "Usage: mytar [ctxvS]f tarfile [ path [ ... ] ]\n";
	int option[6] = {0};


	int inFd, outFd;


	if(argc != 4 || argc != 3)
	{

		write(errno(stderr), &usage, strlen(usage));
		exit(EXIT_FAILURE);
	}

	/*Options:
	 * c - creat an archieve
	 * t - Print the table of contents of an archieve
	 * x - extract the contents of an archieve
	 * v - increases verbosity
	 * S - Be strict on std compliance
	 */

	/*Option 0 - f(file to be used)*/
	if ((inFd=open(argv[2], O_RDONLY)) == -1)
	{
		perror(argv[2]);
		exit(EXIT_FAILURE);
	}


	/*Option 1 - c creat archieve*/

	/*Does argv[1] contain c?*/
	if (strstr(argv[1],"c") != NULL)
	{
		/*create file that i*/
	}

	/*Option 2 - */

	
	return 0;
}



