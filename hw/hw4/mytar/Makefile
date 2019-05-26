CC = gcc
CFLAGS = -Wall -ansi -pedantic -g -lm
MAIN = mytar
OBJ =  entry.o header.o 

all : $(MAIN)

$(MAIN) : $(OBJ) 
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJ)

#creat.o : creat.c
	#$(CC) $(CFLAGS) -c creat.c

#table.o : table.c
#	$(CC) $(CFLAGS) -c table.c


entry.o : entry.c entry.h
	$(CC) $(CFLAGS) -c entry.c

header.o : header.c header.h
	$(CC) $(CFLAGS) -c header.c

clean :
	rm *.o $(MAIN) 

