CC = gcc
CFLAGS = -Wall -ansi -pedantic -g -lm
MAIN = hdecode
OBJS = hdecode.o readLongLine.o freqTable.o node.o pQueue.o huffmanTree.o 
all : $(MAIN)

$(MAIN) : $(OBJS) hdecode.h 
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

hencode.o : hdecode.c hdecode.h
	$(CC) $(CFLAGS) -c hdecode.c

freqTable.o : freqTable.c freqTable.h
	$(CC) $(CFLAGS) -c freqTable.c

huffmanTree.o : huffmanTree.c huffmanTree.h
	$(CC) $(CFLAGS) -c huffmanTree.c

node.o : node.c node.h
	$(CC) $(CFLAGS) -c node.c

pQueue.o : pQueue.c pQueue.h
	$(CC) $(CFLAGS) -c pQueue.c

readLongLine.o : readLongLine.c readLongLine.h
	$(CC) $(CFLAGS) -c readLongLine.c

clean :
	rm *.o $(MAIN) core

