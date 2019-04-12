CC = gcc
CFLAGS = -Wall -ansi -pedantic
MAIN = mytr
OBJS = mytr.o
all : $(MAIN)

$(MAIN) : $(OBJS)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

mytr.o : mytr.c mytr.h
	$(CC) $(CFLAGS) -c funcs.c

clean :
	rm *.o $(MAIN) core

