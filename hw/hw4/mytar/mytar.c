#include "mytar.h"


enum boolean{FALSE,TRUE};


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
	}
}




/*[valid bit|c|t|x|v|f|S]*/
int *get_option(char *options)
{
	int *option_int = (int *)calloc(OPTION_SIZE+1, sizeof(int);
	const int c = 1, t = 2, x = 3, v = 4, f = 5, S=6;

	option_int[0] = TRUE;

	for(int i = 0; i< OPTION_SIZE; i++)
	{	
		switch(options[i])		
		{
			case 'c': /*creation mode - creat archieve*/
				option_int[c] = TRUE;
				break;
			case 't': 
				option_int[t] = TRUE;
				break;
			case 'x':
				option_int[x] = TRUE;
				break;
			case 'v':
				option_int[v] = TRUE;
				break;
			case 'f':
				option_int[f] = TRUE;
				break;
			case 'S':
				option_int[S] = TRUE;
				break;
			default:
				option_int[0] = FALSE;
				break;
		}

	}
	/*Check if one or more option selected*/
	if(option_int[c]+option_int[t]+option_int[x] > 1)
	{
		perror("you can only choose option x,t,c at the same time\n");
		exit(EXIT_FAILURE);
	}
	else if(option_int[c]+option_int[t]+option_int[x] == 0)
	{
		/*only f was givent */
		perrror("you must choose one of the options x,t,c same time\n");
		exit(EXIT_FAILURE);
	}
	
	return option;
}


int main(int argc, char *argv[])
{
	
	int *option;
	const int c = 1, t = 2, x = 3, v = 4, f = 5, S=6;
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
		/*Case 1 : creation and file*/
		if (option[1] == TRUE && option[5] == TRUE)
		{

		}
		/*Case 2 : creation, file, and verbosity*/
		else if(option[1] == TRUE && option[2] == TRUE && option[3] == TRUE)
		{

		}
		/*Case 3: table, and file*/
		else if(option[])
		{

		}

	}


	
	return 0;
}



