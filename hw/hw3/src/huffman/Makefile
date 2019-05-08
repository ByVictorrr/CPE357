CC = gcc
CFLAGS = -Wall -ansi -pedantic -g -lm
EMAIN = hencode
DMAIN = hdecode
EOBJ = hencode.o freqTable.o lookUpTable.o node.o pQueue.o huffmanTree.o
DOBJ = hdecode.o freqTable.o lookUpTable.o node.o pQueue.o huffmanTree.o readLongLine.o


all : $(EMAIN) $(DMAIN)

$(EMAIN) : $(EOBJ) hencode.h
	$(CC) $(CFLAGS) -o $(EMAIN) $(EOBJ)

$(DMAIN) : $(DOBJ) hdecode.h
	$(CC) $(CFLAGS) -o $(DMAIN) $(DOBJ)

hencode.o : hencode.c hencode.h
	$(CC) $(CFLAGS) -c hencode.c

hdecode.o : hdecode.c hdecode.h
	$(CC) $(CFLAGS) -c hdecode.c

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

readLongLine.o : readLongLine.c readLongLine.h
	$(CC) $(CFLAGS) -c readLongLine.c
clean :
	rm *.o $(MAIN) core

