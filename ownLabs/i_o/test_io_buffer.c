#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>


int main()
{
    int fd1, fd2;
    char buff[10];
    char *filename = "tf";
    fd1 = open(filename,O_RDWR);

    write(fd1, "Really", 4);

    read(fd1, buff, strlen(buff));

    printf("buff %s: ", buff);

    fd2 = open(filename,O_RDONLY | O_CREAT);
    write(fd2,"Traditional!", 9 );

return 0;
}