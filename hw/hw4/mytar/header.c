#include <sys/stat.h>
#include <stdio.h>
#include
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
    uint8_t chksumf[CHKSUM_LEN];
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
    char *name = (char *)malloc(sizeof(char)strlen(pathname));

    /*Step 1- Next we shall go through and seperate the prefix and the actual name to be used in entry*/
    while((pathname = strtok(pathname, "/")) != NULL)
    {
        strcpy(name, pathname);
        printf("<<%s>>\n", pathname)
        pathname = NULL;
    }
    /*Step 2- if the length of the name is to big*/
    if(strlen(name) => NAME_LEN)
    {
        ;
    }
    strncpy(header_entry->name, name);
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
   else if(S_ISLINK(file_info.st_mode))
   {
       header_entry->typeflag = '5';
   }

}

void get_linkname(char *pathname, headerEntry *header_entry)
{
    struct stat buff;

    if(lstat(pathname, &buff) == -1)
        print_err("stat error in get_linkname");

    header_entry->linkname = buff.
}


void get_Stats(char *pathname, headerEntry *header_entry)
{
   struct stat file_info;

   if(lstat(pathname, &file_info) == -1)
       print_err("stat err in uid in get_uid_gid");


   /*Setting each member in header struct to that of pathname attribute*/
   get_name(pathname, header_entry);
   memcpy(header_entry->mode,file_info.st_mode, MODE_LEN);
   memcpy(header_entry->uid, file_info.st_uid, UID_LEN);
   memcpy(header_entry->gid, file_info.st_gid, GID_LEN);
   memcpy(header_entry->size, file_info.st_size, SIZE_LEN);
   memcpy(header_entry->mtime, file_info.st_mtime, MTIME_LEN);
   get_typeflags(pathname, header_entry);

   if(header_entry->typeflag = '5')
   {
       get_linkname();
   }


}








