#include "readLongLine.h"


char *read_long_line(int inFd)
{
	int index = 0;
	char *pbuff;
	int sizebuff = MAXCHAR;
	char c; /*temp is for moving allong pbuff*/

	/*initalize current size of buffer*/	
	int onebuff = 0;

	/*case 2: reading the whole file */
	pbuff = (char*)calloc(MAXCHAR, sizeof(char));
	memset(pbuff, '\0', MAXCHAR);
	
	write(STDOUT_FILENO, "8-P: ", strlen("8-P: "));
	while((read(inFd, &c, sizeof(char))) > 0)
	{

		if(c=='\n')
			return pbuff;
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

