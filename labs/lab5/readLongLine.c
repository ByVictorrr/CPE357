#include "readLongLine.h"


/*index of buffer*/
int index = 0;

void print_binary(char x) {
    int b = 128;

    while (b != 0) {

        if (b <= x) {
            x -= b;
            printf("1");
        } else
            printf("0");

        b = b >> 1;
    }
}
void printbincharpad(char c)
{
    int i;
    for (i = 7; i >= 0; --i)
    {
        putchar( (c & (1 << i)) ? '1' : '0' );
    }
    putchar('\n');
}
char *read_long_line(int inFd)
{
	int sizebuff = MAXCHAR;
	char c; /*temp is for moving allong pbuff*/

	/*initalize current size of buffer*/	
	int onebuff = 0;

	/*case 2: reading the whole file */
	pbuff = (char*)calloc(MAXCHAR, sizeof(char));

	while((read(inFd, &c, sizeof(char))) > 0)
	{
	   /* print_binary(c);
	    printf(" above is %c \n", c);
	    */
		/*case 3: store value of c in buffer */
		pbuff[index++] = c;
		/*case 4: check if an overflow occured in buffer same buff
		 *		count number of overflows in buff */
		if ( index >= MAXCHAR-1 )
		{
			/*Size alloationa are alwaysgoing to be mutliples os MAXCHAr*/
			sizebuff = sizebuff + MAXCHAR;
			pbuff = (char*)realloc(pbuff,sizebuff);
		}
	}

	return pbuff;
}

void freeBuffs(char *buff)
{
    if(buff != NULL)
        free(buff);
    return;
}

/*
int main(int argc, char *argv[])
{

	int inFd = open(argv[1], O_RDONLY);

	char *buff_ptr = read_long_line(inFd);


	printf("%s\n", buff_ptr);
	for (;*buff_ptr != '\0'; buff_ptr++)
	    putchar(*buff_ptr);


	close(inFd);

	free(pbuff);
	free(buff);

	return 0;

}
 */
