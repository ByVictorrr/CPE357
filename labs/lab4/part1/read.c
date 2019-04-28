#include <stdio.h>
#include 
/*Description: write a prog that opens a file /usr/lib/locale/locale-archieve on unix and reads the contensts of that file using the read sys call.
 *				Write it in a manner that allows you to change the number of bytes read (use #define f for array size and argument to read*/

#define BUFSIZE 1

char buf[BUFSIZE];
char *bufp;

int main()
{
	int fd, n;
	/*case 1 : cant open the file*/
	if ((fd = open("/usr/lib/local/locale-archieve", O_RDONLY, 0)) == -1)
		error("read: cant open local-acheive\n");
	while((n=read(fd, buf, BUFSIZE)) > 0)

return 0;
}
