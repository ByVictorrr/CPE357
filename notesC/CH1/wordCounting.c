#include <stdio.h>

#define IN 1  // inside a word
#define OUT 0 //outside a word


//counts lines, words, and charaacters in input
int main()
{
	int c,nl, nw, nc, state;
	nl = nw = nc = 0;
	while((c = getchar()) != EOF)
		++nc;
		if(c == '\n')
			++nl;
		if(c == ' ' || c == '\n' || c == '\t')
			state = OUT;
		else if(state == 0){
			state = IN;
			++nw;
		} 

	printf("%d %d %d\n", nl, nw, nc);
	

return 0;
}
