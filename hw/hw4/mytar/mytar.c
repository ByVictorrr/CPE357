#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>






int main(int argc, char *argv[])
{
	char *usage = "Usage: mytar [ctxvS]f tarfile [ path [ ... ] ]\n";
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
