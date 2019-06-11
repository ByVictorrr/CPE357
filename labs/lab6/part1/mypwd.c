/*
 * mypwd.c
 * Copyright (C) 2019 victor <victor@TheShell>
 *
 * Distributed under terms of the MIT license.
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#define CWD 0


void transverse(ino_t prev_ino, ino_t root_ino, ino_t cwd_ino, char *pwd, int *pwd_ptr){

	DIR *dp;
	struct dirent *entry;
	struct stat buff, buff_cwd;

	if(*pwd_ptr > PATH_MAX){
		perror("path name to long");
		exit(EXIT_FAILURE);
	}
	/*Base case prev_ino == root_ino */
	if(prev_ino == root_ino){
		strcpy(pwd, "/");
		*pwd_ptr = 1;
		return;
	}
	/*Case 1 - in current directory  */
	if(prev_ino == CWD){
		/*Step 1 - get current current dir i_node number  */
		lstat(".", &buff);
		/*Step 2 - get inode  */
		prev_ino = buff.st_ino;
		/*Step 3- change dir to parent */
		if (chdir("..") < 0){
			perror("..");
			exit(EXIT_FAILURE);
		}
	}
	/*Case 2 - get name of current directory*/
	if((dp = opendir(".")) == NULL){
		perror(".");
		exit(EXIT_FAILURE);
	}
	/*Case 3 - go through current directory */
	while((entry = readdir(dp)) != NULL){
		/*Step 1 - get stats of the the entry*/
		if(lstat(entry->d_name, &buff) < 0){
			perror(entry->d_name);
			exit(EXIT_FAILURE);
		}
		/*Step 2 - if the entry is a directory and has the inode number of prev_ino get that name*/
		if(S_ISDIR(buff.st_mode) && prev_ino == buff.st_ino){
			/*Step 3 - get st_ino of . and call function*/
			lstat(".", &buff_cwd);
			chdir("..");
			transverse(buff_cwd.st_ino, root_ino, cwd_ino, pwd, pwd_ptr);
			/*Step 4 - strcat entry->d_name to pwd */
			strcat(pwd, entry->d_name);
			if(cwd_ino != prev_ino)
				strcat(pwd, "/");
			
			*pwd_ptr = strlen(pwd);
			closedir(dp);
			return;
		}

	}

}




int main(int argc, char **argv)
{
	ino_t prev = CWD; /*We cant get the name in the current directory so we have to use the ino_t to compare if thats the name in the parrent  */
	char pwd[PATH_MAX] = {'\0'};
	int pwd_ptr = 0;
	struct stat root_buff, cwd_buff;

	
	if(lstat("/", &root_buff) < 0){
		perror("/");
		exit(EXIT_FAILURE);
	}

	if(lstat(".", &cwd_buff) < 0){
		perror("/");
		exit(EXIT_FAILURE);
	}
	transverse(prev, root_buff.st_ino, cwd_buff.st_ino, pwd, &pwd_ptr);

	printf("pwd = %s ", pwd);

	return 0;
}
