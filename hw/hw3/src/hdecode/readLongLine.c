#include "readLongLine.h"

void print_binary(unsigned char x) {
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
void printbincharpad(unsigned char c)
{
    int i;
    for (i = 7; i >= 0; --i)
    {
        putchar( (c & (1 << i)) ? '1' : '0' );
    }
    putchar('\n');
}
unsigned char *read_long_line(int inFd)
{
    numLines = 0;
    sizeLines = 0;
	unsigned sizebuff = MAXCHAR;
	unsigned char *temp, c; /*temp is for moving allong pbuff*/

	/*initalize current size of buffer*/	
	int onebuff = 0;

	/*case 2: reading the whole file */
	pbuff = temp = (unsigned char*)calloc(MAXCHAR, sizeof(unsigned char));

	while((read(inFd, &c, sizeof(unsigned char))) > 0)
	{
	   /* print_binary(c);
	    printf(" above is %c \n", c);
	    */
		/*case 3: store value of c in buffer */
		*temp++ = c;
		/*case 4: check if an overflow occured in buffer same buff
		 *		count number of overflows in buff */
		if ( temp >= (MAXCHAR-1)+ pbuff )
		{
			/*Size alloationa are alwaysgoing to be mutliples os MAXCHAr*/
			sizebuff = sizebuff + MAXCHAR;
			pbuff = (unsigned char*)realloc(pbuff,sizebuff);
			temp = pbuff + (sizebuff - MAXCHAR); /*tryin to get next spot in stack for word*/
		}
		if ( c == '\n') {
            if (!numLines) {
                /*case 5.1.1: 1st time allocate space for buff*/
                buff = (unsigned char *) malloc(onebuff + 1); /*what if not overflowed*/
                strcpy(buff, pbuff);
                prev = buff; /*have prev point to first unsigned char*/
                sizeLines = onebuff;
            } else { /*Case 5.1.2: ith time allocating space for buff, also need to only reallocate on condition*/
                /*If were in this scope its assume that there is at least two buffs*/
                buff = (unsigned char *) realloc(buff, onebuff + sizeLines + 1);
                /*copy contents from buffer to prev*/
                prev = buff;
                strcpy((prev = prev + sizeLines), pbuff);
                sizeLines += onebuff;

            }
            /*case 6: reset buffer*/ free(pbuff);
            pbuff = (unsigned char *) calloc(MAXCHAR, sizeof(unsigned char));
            temp = pbuff;

            sizebuff = MAXCHAR;
            numLines++;
        }
	}

	return pbuff;
}

void freeBuffs(unsigned char *buff)
{
    if(buff != NULL)
        free(buff);
    return;
}

/*
int main(int argc, char *argv[])
{

	int inFd = open(argv[1], O_RDONLY);

	unsigned char *buff_ptr = read_long_line(inFd);


	printf("%s\n", buff_ptr);
	for (;*buff_ptr != '\0'; buff_ptr++)
	    putchar(*buff_ptr);


	close(inFd);

	free(pbuff);
	free(buff);

	return 0;

}
 */
