rm header
gcc -g -o header header.c
gdb -x debugger.gdb header
valgrind header

