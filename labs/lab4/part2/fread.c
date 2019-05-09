#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

/*Description: write a prog that opens a file /usr/lib/locale/locale-archieve on unix and reads the contensts of that file using the read sys call.
 *
 *				Write it in a manner that allows you to change the number of bytes read (use #define f for array size and argument to read*/



char *bufp;

int main(int argc, char *argv[])
{

	int buff_size = atoi(argv[1]), fd, n;

	bufp=(char*)malloc(sizeof(char)*buff_size);

	FILE *fp;
	/*case 1 : cant open the file*/
	if ((fp = fopen("/usr/lib/locale/locale-archive", "r")) == NULL)
		printf("read: cant open local-acheive\n");
	while((fread(bufp,buff_size,1,fp)) > 0)

	fclose(fp);
	free (bufp);

	return 0;
}
