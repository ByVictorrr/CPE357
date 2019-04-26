C = gcc
CFLAGS = -Wall -ansi -pedantic -g
MAIN = fw
OBJS = fw.c
all : $(MAIN)

$(MAIN) : $(OBJS) fw.h
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

fw.o : fw.c fw.h
	$(CC) $(CFLAGS) -c fw.c

clean :
	rm *.o $(MAIN) core
