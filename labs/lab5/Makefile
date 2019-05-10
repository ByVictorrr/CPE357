CC = gcc
CFLAGS = -Wall -ansi -pedantic -g -lm
MAIN = htable
OBJS = htable.o freqTable.o lookUpTable.o node.o pQueue.o huffmanTree.o

all : $(MAIN)

$(MAIN) : $(OBJS) htable.h
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

htable.o : htable.c htable.h
	$(CC) $(CFLAGS) -c htable.c

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

