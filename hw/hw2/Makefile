#fw - makefile
#Program by : Victor and Justin

#Vars:
CC= gcc
CFLAGS = -g
MAIN = fw
OBJS = fw.o MergeSortBaby.o bufferinput.o bst.o readOutWords.o
all : $(MAIN)

$(MAIN) : $(OBJS)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

fw.o : fw.c fw.h


MergeSortBaby.o : MergeSortBaby.c
		$(CC) $(CFLAGS) -c MergeSortBaby.c

	

bufferinput.o : bufferinput.c
		$(CC) $(CFLAGS) -c bufferinput.c
	
bst.o : bst.c
	$(CC) $(CFLAGS) -c bst.c


readOutWords.o : readOutWords.c
		$(CC) $(CFLAGS) -c readOutWords.c


clean :
	rm *.o $(MAIN) core

