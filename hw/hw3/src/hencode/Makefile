CC = gcc
CFLAGS = -Wall -ansi -pedantic -g -lm
MAIN = hencode
OBJS = hencode.o freqTable.o lookUpTable.o node.o pQueue.o huffmanTree.o

all : $(MAIN)

$(MAIN) : $(OBJS) hencode.h
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

hencode.o : hencode.c hencode.h
	$(CC) $(CFLAGS) -c hencode.c

freqTable.o : freqTable.c freqTable.h
	$(CC) $(CFLAGS) -c freqTable.c

lookUpTable.o : lookUpTable.c lookUpTable.h
	$(CC) $(CFLAGS) -c lookUpTable.c

huffmanTree.o : huffmanTree.c huffmanTree.h
	$(CC) $(CFLAGS) -c huffmanTree.c

node.o : node.c node.h
	$(CC) $(CFLAGS) -c node.c

pQueue.o : pQueue.c pQueue.h
	$(CC) $(CFLAGS) -c pQueue.c

clean :
	rm *.o $(MAIN) core

