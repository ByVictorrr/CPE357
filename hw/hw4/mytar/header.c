#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <syscall.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
/*===================Header function and vars=====================================*/
#define NAME_LEN 100
#define MODE_LEN 8
#define UID_LEN 8
#define GID_LEN 8
#define SIZE_LEN 12
#define MTIME_LEN 12
#define CHKSUM_LEN 8
#define TYPEFLAG_LEN 1
#define LINKNAME_LEN 100
#define MAGIC_LEN 6
#define VERSION_LEN 2
#define UNAME_LEN 32
#define GNAME_LEN 32
#define DEVMAJOR_LEN 8
#define DEVMINOR_LEN 8
#define PREFIX_LEN 155

typedef struct header{
    uint8_t name[NAME_LEN];
    uint8_t mode[MODE_LEN];
    uint8_t uid[UID_LEN];
    uint8_t gid[GID_LEN];
    uint8_t size[SIZE_LEN];
    uint8_t mtime[MTIME_LEN];
    uint8_t chksum[CHKSUM_LEN];
    uint8_t typeflag;
    uint8_t linkname[LINKNAME_LEN];
    uint8_t magic[MAGIC_LEN];
    uint8_t version[VERSION_LEN];
    uint8_t uname[UNAME_LEN];
    uint8_t gname[GNAME_LEN];
    uint8_t devmajor[DEVMAJOR_LEN];
    uint8_t devminor[DEVMINOR_LEN];
    uint8_t prefix[PREFIX_LEN];
}headerEntry;


void print_err(char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}



/*get_name : gets the name of the pathname with nothing in front*/
void get_name(char *pathname, headerEntry *header_entry)
{
    char *name = (char *)malloc(sizeof(char)*strlen(pathname));

    /*Step 1- Next we shall go through and seperate the prefix and the actual name to be used in entry*/
    while((pathname = strtok(pathname, "/")) != NULL)
    {
        strcpy(name, pathname);
        pathname = NULL;
    }
    /*Step 2- if the length of the name is to big*/
    if(strlen(name) >= NAME_LEN)
    {
        ;
    }
    strncpy(header_entry->name, name, NAME_LEN);

    free(name);
}

void get_typeflags(char *pathname, headerEntry *header_entry){

   struct stat file_info;

   if(lstat(pathname, &file_info) == -1)
       print_err("stat err in uid in get_uid_gid");

   if(S_ISDIR(file_info.st_mode))
   {
       header_entry->typeflag = '5';
   }
   else if(S_ISREG(file_info.st_mode))
   {
       header_entry->typeflag = '\0';
   }
   else if(S_ISLNK(file_info.st_mode))
   {
       header_entry->typeflag = '2';
   }
}

void get_linkname(char *pathname, headerEntry *header_entry)
{
    struct stat file_info;
    char c, buff[LINKNAME_LEN];
    int fd, i, n;

    if(lstat(pathname, &buff) == -1)
        print_err("stat error in get_linkname");
    if((fd = open(pathname, O_RDONLY)) == -1)
        print_err("open err in get_linkname");

    for(i = 0; (n=read(fd, &c, 1)) > 0 || i<= LINKNAME_LEN-1; i++)
    {
        buff[i] = c;
    }
    if(i<LINKNAME_LEN) /*fill with zeros*/
    {
        memset(buff[LINKNAME_LEN - i], '\0', LINKNAME_LEN-i);
    }

    memcpy(header_entry->linkname, buff, LINKNAME_LEN);

   }


void get_stats(const char *pathname, headerEntry *header_entry)
{
   struct stat file_info;

   if(lstat(pathname, &file_info) == -1)
       print_err("stat err, {in get_stats function");

   /*Setting each member in header struct to that of pathname attribute*/
   get_name(pathname, header_entry);
   memcpy(header_entry->mode,&file_info.st_mode, MODE_LEN);
   memcpy(header_entry->uid, &file_info.st_uid, UID_LEN);
   memcpy(header_entry->gid, &file_info.st_gid, GID_LEN);
   memcpy(header_entry->size, &file_info.st_size, SIZE_LEN);
   memcpy(header_entry->mtime, &file_info.st_mtime, MTIME_LEN);
   get_typeflags(pathname, header_entry);

   if(header_entry->typeflag == '2')
       get_linkname(pathname, header_entry);
   else
       memset(header_entry->linkname, '\0', LINKNAME_LEN);
    
    strncpy(header_entry->magic, "ustar", MAGIC_LEN);
    memset(header_entry->version, 0, VERSION_LEN);
    memcpy(header_entry->uname, &file_info.st_uid, UID_LEN);
    memcpy(header_entry->gid, &file_info.st_gid, GID_LEN);
   /* memcpy(header_entry->devmajor, MAJOR(file_info.st_dev), DEVMAJOR_LEN);
    memcpy(header_entry->devminor, MINOR(file_info.st_dev), DEVMINOR_LEN);
    */
   memset(header_entry->devmajor, '\0', DEVMAJOR_LEN);
   memset(header_entry->devminor, '\0', DEVMINOR_LEN);
}

void print_header(headerEntry *hdr)
{
printf(" char name[]: %s\n", hdr->name );
printf(" mode_t mode: 0%04o\n",hdr->mode );
printf(" uid_t uid: %d\n", (int)hdr->uid );
printf(" gid_t gid: %d\n", (int)hdr->gid );
printf(" size_t size: %d\n", (int)hdr->size );
printf(" time_t mtime: %d --- %s", (int)hdr->mtime, ctime(&hdr->mtime));
printf(" int chksum: %d\n", hdr->chksum );
printf(" char typeflag: %c\n", hdr->typeflag );
printf(" char linkname[]: %s\n", hdr->linkname );
printf(" char magic[]: %s\n", hdr->magic );
printf(" char version[]: %s\n", hdr->version );
printf(" char uname[]: %s\n", hdr->uname );
printf(" char gname[]: %s\n", hdr->gname );
printf(" int devmajor: %d\n", hdr->devmajor );
printf(" int devminor: %d\n", hdr->devminor );
printf(" char prefix[]: %s\n", hdr->prefix );

}



int main(int argc, char **argv)
{
    headerEntry header_entry;

    /*Test 1- name works
    get_name(argv[1], &header_entry);
    printf("pathname = : %s", header_entry.name);
    */

    get_stats("header.c", &header_entry);
    print_header(&header_entry);

    return 0;
}