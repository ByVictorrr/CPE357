#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <syscall.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "header.h"
#define BLOCK_SIZE 512


void write_header(int tarFd , headerEntry header)
{
    uint16_t padd_header = '\0';

    write(tarFd, header.name, NAME_LEN);
    write(tarFd, header.mode, MODE_LEN);
    write(tarFd, header.uid, UID_LEN);
    write(tarFd, header.gid, GID_LEN);
    write(tarFd, header.size, SIZE_LEN);
    write(tarFd, header.mtime, MTIME_LEN);
    write(tarFd, header.chksum, CHKSUM_LEN);
    write(tarFd, &header.typeflag, TYPEFLAG_LEN);
    write(tarFd, header.linkname, LINKNAME_LEN);
    write(tarFd, header.magic, MAGIC_LEN);
    write(tarFd, header.version, VERSION_LEN);
    write(tarFd, header.uname, UNAME_LEN);
    write(tarFd, header.gname, GNAME_LEN);
    write(tarFd, header.devmajor, DEVMAJOR_LEN);
    write(tarFd, header.devminor, DEVMINOR_LEN);
    write(tarFd, header.prefix, PREFIX_LEN);
    /*Above is only 500 bytes*/

    /*We need to writ 512 bytes*/
    write(tarFd, &padd_header, 12);
}

/*Assuming the tar - output file is opened*/
void add_entry(char *pathname, int tarFd , headerEntry header)
{
    int currFd;
    int num_writes, num_to_pad;
    uint8_t padder[BLOCK_SIZE] = {'\0'};
    uint8_t c;

   /*Step 1 - First write 1 block - header to the tar file */
   write_header(tarFd, header);
   /*Step 2 -  2nd open that file with pathname and then */
   if((currFd = open(pathname, O_RDONLY)) == -1){
       print_err("open error in add_entry");
   }
   /*step 3 - write to tarFd while reading contents*/
   while(read(currFd, &c, 1) != 0)
   {
       /*write that to the file*/
       write(tarFd, &c, 1);
       num_writes++;
   }
   /*If the number of writes isnt divisble by 512 then padd it with extra null char*/
   if((num_to_pad = num_writes % BLOCK_SIZE) != 0)
   {
      num_to_pad = BLOCK_SIZE-num_to_pad;
      write(tarFd, padder, num_to_pad);
   }
   
}



int main(int argc, char **argv)
{
    headerEntry header_entry;

    /*Test 1- name works
    get_name(argv[1], &header_entry);
    printf("pathname = : %s", header_entry.name);
    */

   char *pathname = "inputs/test1";
   int tarFd = open("outputs/test1.tar", O_RDONLY| O_TRUNC | O_WRONLY);
   /*Test 2- header work, expcept for gid , uname*/
    get_stats(pathname, &header_entry);
    print_header(&header_entry);
     add_entry(pathname, tarFd, header_entry);

    return 0;

}