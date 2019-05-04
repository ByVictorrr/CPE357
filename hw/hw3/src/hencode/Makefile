C = gcc
CFLAGS = -Wall -ansi -pedantic -g -lm
MAIN = hencode
OBJS = hencode.c
all : $(MAIN)

$(MAIN) : $(OBJS) h
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

hencode.o : hencode.c
	$(CC) $(CFLAGS) -c hencode.c

freqTable.o : freqTable.c
	$(CC) $(CFLAGS) -c freqTable.c

lookUpTable.o : lookUpTable.c
	$(CC) $(CFLAGS) -c lookUpTable.c

node.o : node.c node.h
	$(CC) $(CFLAGS) -c node.c

pQueue.o : pQueue.c
	$(CC) $(CFLAGS) -c pQueue.c

clean :
	rm *.o $(MAIN) core
