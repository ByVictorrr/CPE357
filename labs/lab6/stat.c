#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#define ACCESS_SIZE 11 /*it should be 10 but because of null char at access[10] = '\0'*/
#define SETUID_PLACE 3
#define SETGID_PLACE 6
/*Ouput should look like:
 * File: 
 * Type:
 * size:
 * Inode:
 * Links:
 * Acess:
*/



int main(int argc, char *argv[])
{

	char *errMsg = "Usage: stat [file]\n", *type;
	unsigned char access[ACCESS_SIZE] = {'\0'};
	struct stat info;


	if (argc != 2)
	{
		write(fileno(stderr), errMsg, strlen(errMsg));
		exit(EXIT_FAILURE);
	}

	if(stat(argv[1], &info) == -1)
	{
		perror(argv[1]);
		exit(EXIT_FAILURE);
	}

	
	/*Step 1 - print out fileName*/
	printf("File: `%s`\n", argv[1]);


	/*Step 2 - get file type*/
	if(S_ISREG(info.st_mode))
	{
		type = "regular";
		access[0] = '-';
	}
	else if(S_ISDIR(info.st_mode))
	{
		type = "directory";
		access[0] = 'd';
	}
	else if(S_ISCHR(info.st_mode))
	{
		type = "character special";
		access[0] = 'c';
	}
	else if(S_ISBLK(info.st_mode))
	{
		type = "block special";
		access[0] = 'b';
	}
	else if(S_ISFIFO(info.st_mode))
	{
		type = "fifo";
		access[0] = 'p';
	}
	else if(S_ISLNK(info.st_mode))
	{
		type = "symbolic link";
		access[0] = 'l';
	}
	else if(S_ISSOCK(info.st_mode))
	{
		type = "socket";
		access[0] = 's';
	}else{
		type = "** unknown mode **";
	}

	printf("Type: %s\n", type);



	/*Step 3 - get file size*/
	printf("Size: %lu\n", info.st_size);

	/*Step 4 - get inode number*/
	printf("Inode: %lu\n", info.st_ino);

	/*Step 5 - get number of links to the file*/
	printf("Links: %lu\n", info.st_nlink);

	/*Step 6 - Acess */
	/*step 6.1 - get rwx for u, g, o*/

	/*User*/
	if (S_IRUSR & info.st_mode)
		access[1] = 'r';
	else
		access[1] = '-';

	if (S_IWUSR & info.st_mode)
		access[2] = 'w';
	else
		access[2] = '-';

	if (S_IXUSR & info.st_mode)
		access[3] = 'x';
	else
		access[3] = '-';


	/*group*/
	if(S_IRGRP & info.st_mode )
		access[4] = 'r';
	else
		access[4] = '-';

	if (S_IWGRP & info.st_mode )
		access[5] = 'w';
	else
		access[5] = '-';

	if(S_IXGRP & info.st_mode )
		access[6] = 'x';
	else
		access[6] = '-';

	/*owner*/
	if(S_IROTH & info.st_mode )
		access[7] = 'r';
	else
		access[7] = '-';
	if(S_IWOTH & info.st_mode )
		access[8] = 'w';
	else
		access[8] = '-';
	if(S_IXOTH & info.st_mode )
		access[9] = 'x';
	else
		access[9] = '-';
	
	/*step 6.2 - get setuid and setgid*/
	if (S_ISUID & info.st_mode)
		access[SETUID_PLACE] = 's';
	if (S_ISGID & info.st_mode)
		access[SETGID_PLACE] = 's';

	printf("Acess: %s\n", access);

	return 0;
}
