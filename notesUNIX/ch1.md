#UNIX System Overview

##1.1 Introduction

All OS provide services to run, these generally inculude executing a new
program, opening a file, reading a file, allocating a region of memory, getting the current time of day, ect.

##1.2 UNIX Arhitecture

OS: defined as the software that controls hardware resouces of the comptuer and provides an environment under which pgorams can run.

-> The software can be defined as the kernal, since its small and resides at the core of then env.




Figure 1.1 shows diagram of the UNIX system arch.

-> The interface to the kernal is a layer of softwar called the system calls.

##1.3 Loggin in 

### Login Name

	When logging into Unix file system, we enter a login name followed by
username.
	-> They system usually looks up our login name in its password file:
/etc/passwd.
	-> This file is composed of seven colon seperated fields:
	1.) Login name
	2.)encrypted password
	3.)numeric user ID
	4.)number group ID
	5.) a comment field
	6.) hom directory
	7.) the shell program

EXAMPLE:sar:x:205:105:Stephen Rago:/home/sar:/bin/ksh

### Shells

	Once we login some system information ar typicall displayed and then we can type command to the shell program.

	SHELL: is a cmd line interpeter that reads user input and executes commands.


COMMON SHELLS:

//inser FIGURE 1.2


-> The system knows which shell to execute for us based on the final field in our entry in passwd


## 1.4 Files and Directories

### File System

	The UNIX file system is a hierachal arrangment of directories and files.

-> Everything starts with a root, /.

Directory: a file that contains directory enteries.

-> the atrributes that these Directories hold are file type of file, size, the owner of the file and permission of file and last modification.

### Filename

filename: names in a directory 

Naming Restriction: 




### Pathname


#### Example : Listing names of all files in a directory


#include <dirent.h>

int main(int argc, char *argv[])
{

	DIR	*dp;
	struct dirent *dirp;

	if(argc != 2)
		err_quit("usage: ls directory_name");

	if((dp = opendir(arv[1])) == NULL)
		err_sys("can't open %s", argv[1]);

	while((dirp = readdir(dp)) != NULL)
		printf("%s\n", dirp-> d_name);

	closedir(dp);
	exit(0);


}


