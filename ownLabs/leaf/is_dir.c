#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PATH 500


void error(char *err)
{
	perror(err);
	exit(EXIT_FAILURE);
}

int isLeafDir(char *path)
{
	struct stat buff;
	DIR *dp;
	char *relative_path;
	struct dirent *entry;

	/*Step 1- get the mode of the pathname*/
	if(lstat(path, &buff) == -1)
		error(path);
	/*Step 2 - determine if the pathname is a directory*/
	if(S_ISDIR(buff.st_mode))
	{
		if((dp = opendir(path))==NULL)
			error(path);

		/*Step 3 - iterate through that directory*/
		while((entry = readdir(dp)) != NULL)
		{

			if((relative_path = (char *)malloc(sizeof(char)*strlen(path)+strlen(entry->d_name)+1)) == NULL){
				error("malloc err");
			}
			strcpy(relative_path, path);
			strcat(relative_path, "/");
			strcat(relative_path, entry->d_name);

			printf("relative path: %s\n", relative_path);

			if(lstat(relative_path, &buff) == -1)
				error("stat error\n");	

			/*Case 1 - could be current directory || or parent*/
			if((strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) && S_ISDIR(buff.st_mode))
			{
				printf("shouldnt get here for non leaf%s\n",relative_path);
				return 0;	
			}

			free(relative_path);
		}
	}
	return 1;
}

int main(int argc, char *argv[])
{

	if(isLeafDir(argv[1]) == 1)
		printf("this is a leaf directory");
	else
		printf("this is not a leaf directory");
	return 0;
}

