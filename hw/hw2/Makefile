#fw - makefile
#Program by : Victor and Justin

CC = gcc
CFLAGS = -Wall -ansi -pedantic
MAIN = fw
OBJS = main.o
all : $(MAIN)

$(MAIN) : $(OBJS) fw.h
	$(CC) $(CFLAGS) $(MAIN) $(OBJS)

main.0 : main.c fw.h
	$(CC) $(CFLAGS) -c main.c

clean :
	rm *.o $(MAIN) core

