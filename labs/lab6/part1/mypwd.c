#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


void transverse_back(char *pathname)
{
	DIR *dp;

	static char *pwd;

	struct dirent *dir;

	/*Base case  - when the root has been reached return*/
	if(strcmp("..",pathname) != 0)
		return;

	/*General case - when the root hasnt been reached*/
	if((dp = opendir(".")) == NULL){
			perror("open dir error");
			exit(EXIT_FAILURE);
	}
	while((dir = readdir(dp)) != NULL && dir->d_name != "..")
		;

	chdir("..");
	transverse_back(dir->d_name);
	
	strcat(pwd, "/");
	strcat(pwd, dir->d_name);

	closedir(dp);
	printf("directory %s\n");

}



/*./mypwd
 * 
 *
 * that performs the sam task as /bin/pwd withou using getcwd*/

int main(int argc, char *argv[])
{ 

	transverse_back("..");



return 0;
}

