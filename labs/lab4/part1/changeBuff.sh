#!/bash/bin
for i in 1 2 16 32 64 128 256 512 1024 2048; 
do
	sed -i 's/\(#define BUFSIZE\) $i/\1 $((i))/g' readFile.c
	gcc -g readFile.c
	/usr/bin/time ./a.out 
done
