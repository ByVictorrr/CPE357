#include "mytar.h"
#include "creat.h"

#define TRUE 1
#define FALSE 0





/*[valid bit|c|t|x|v|f|S]*/
int* get_option(int *options)
{
	int *option_int = (int *)calloc(MAX_FLAG+1, sizeof(int));
	const int c = 1, t = 2, x = 3, v = 4, f = 5, S = 6;

	option_int[0] = TRUE;

	for(int i = 0; i< MAX_FLAG; i++)
	{	
		switch(options[i])		
		{
			case 'c': /*creation mode - creat archieve*/
				option_int[c] = TRUE;
				break;
			case 't': 
				option_int[t] = TRUE;
				break;
			case 'x':
				option_int[x] = TRUE;
				break;
			case 'v':
				option_int[v] = TRUE;
				break;
			case 'f':
				option_int[f] = TRUE;
				break;
			case 'S':
				option_int[S] = TRUE;
				break;
			default:
				option_int[0] = FALSE;
				break;
		}

	}
	/*Check if one or more option selected*/
	if(option_int[c]+option_int[t]+option_int[x] > 1)
	{
		perror("you can only choose option x,t,c at the same time\n");
		exit(EXIT_FAILURE);
	}
	else if(option_int[c]+option_int[t]+option_int[x] == 0)
	{
		/*only f was givent */
		perror("you must choose one of the options x,t,c same time\n");
		exit(EXIT_FAILURE);
	}
	
	return options;
}


int main(int argc, char *argv[])
{
	
	int *option;
	const int c = 1, t = 2, x = 3, v = 4, f = 5, S=6;
	int inFd, outFd;


	/*Options:
	 * c - creat an archieve
	 * t - Print the table of contents of an archieve
	 * x - extract the contents of an archieve
	 * v - increases verbosity
	 * S - Be strict on std compliance
	 */

	
	
	/*Step 1 - validate the command line input
		
	[valid bit|c|t|x|v|f|S]
	
	*/
	if( (argc != 4 || argc != 3) && (option = get_option(argv[1]))[0] == FALSE)
	{
		perror("Usage: mytar [ctxvS]f tarfile [ path [ ... ] ]\n");
		exit(EXIT_FAILURE);
	}

	/*Step 1.1 - check if valid bit is set*/
	if(option[0] == TRUE)
	{
		/*Case 1 : creation and file*/
		if (option[1] == TRUE && option[5] == TRUE)
		{
		    creat_archieve();

		}
		/*Case 2 : creation, file, and verbosity*/
		else if(option[1] == TRUE && option[2] == TRUE && option[3] == TRUE)
		{

		}
		/*Case 3: table, and file*/
		else if(option[])
		{

		}

	}


	
	return 0;
}



