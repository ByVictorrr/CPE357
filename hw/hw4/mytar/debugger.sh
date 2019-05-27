rm header
gcc -g -o header header.c
#make clean &&  make
gdb -x debugger.gdb header
valgrind ./header

