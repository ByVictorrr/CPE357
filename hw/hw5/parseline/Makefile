CC = gcc
CFLAGS = -Wall -ansi -pedantic -g -lm
MAIN = parseline
OBJ =  parseline.o readLongLine.o

all : $(MAIN)

$(MAIN) : $(OBJ) 
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJ)


parseline.o : parseline.c 
	$(CC) $(CFLAGS) -c parseline.c

readLongLine.o : readLongLine.c readLongLine.h
	$(CC) $(CFLAGS) -c readLongLine.c

clean :
	rm *.o $(MAIN) 

