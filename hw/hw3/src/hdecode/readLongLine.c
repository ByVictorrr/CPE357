#include "readLongLine.h"

char *read_long_buff(int inFd)
{
	unsigned sizebuff = MAXCHAR;
	char *strcat(char *dest, const char *src);
	char *temp, c; /*temp is for moving allong pbuff*/

	/*initalize current size of buffer*/	
	int onebuff = 0;

	/*case 2: reading the whole file */
	pbuff = temp = (char*)malloc(MAXCHAR);

	while((read(inFd, &c, sizeof(char))) > 0)
	{
		/*case 3: store value of c in buffer */
		*temp++ = c;
		/*case 4: check if an overflow occured in buffer same buff
		 *		count number of overflows in buff */
		if ( temp >= (MAXCHAR-1)+ pbuff )
		{
			/*Size alloationa are alwaysgoing to be mutliples os MAXCHAr*/
			sizebuff = sizebuff + MAXCHAR;
			pbuff = (char*)realloc(pbuff,sizebuff);
			temp = pbuff + (sizebuff - MAXCHAR); /*tryin to get next spot in stack for word*/
		}
		if ( c == '\n') {
            if (!numLines) {
                /*case 5.1.1: 1st time allocate space for buff*/
                buff = (char *) malloc(onebuff + 1); /*what if not overflowed*/
                strcpy(buff, pbuff);
                prev = buff; /*have prev point to first char*/
                sizeLines = onebuff;
            } else { /*Case 5.1.2: ith time allocating space for buff, also need to only reallocate on condition*/
                /*If were in this scope its assume that there is at least two buffs*/
                buff = (char *) realloc(buff, onebuff + sizeLines + 1);
                /*copy contents from buffer to prev*/
                prev = buff;
                strcpy((prev = prev + sizeLines), pbuff);
                sizeLines += onebuff;

            }
            /*case 6: reset buffer*/ free(pbuff);
            pbuff = (char *) calloc(MAXCHAR, sizeof(char));
            temp = pbuff;

            sizebuff = MAXCHAR;
            numLines++;
        }
	}

	return buff;
}


void freeBuffs(char *buff)
{
    if(pbuff != NULL)
        free(pbuff);
    if(buff != NULL)
        free(buff);
    return;
}

/*


int main(int argc, char *argv[])
{


	int inFd = open(argv[1], O_RDONLY);

	char *buff_ptr = read_long_buff(inFd);


	for (;*buff_ptr != '\0'; buff_ptr++)
		putchar(*buff_ptr);

	close(inFd);

	free(pbuff);
	free(buff);

	return 0;

}
 */
