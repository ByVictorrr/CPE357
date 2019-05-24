#include "header.h"


void print_err(char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}


/*get_name : gets the name of the pathname with nothing in front

Assumption: PATHMAX > strlen(pathname)


*/

void get_name_prefix(char *pathname, headerEntry *header_entry)
{

    char name[NAME_LEN];
    char prefix[PREFIX_LEN];
    char arr_pathname[strlen(pathname)+1];
    char *removal;
    char *token;


    memset(name, '\0', NAME_LEN);
    memset(arr_pathname, '\0',strlen(pathname)+1);
    memset(prefix, '\0', PREFIX_LEN);
    strcpy(arr_pathname, pathname);

    /*Step 0 - throw error if strlen(path) > NAME_LEN+PREFIX_LEN*/
    if(strlen(pathname) > NAME_LEN+PREFIX_LEN)
        print_err("pathname is so long");


    /*Step 1- Next we shall go through and seperate the prefix and the actual name to be used in entry*/
    for(token=strtok(arr_pathname, "/"); token;
     token = strtok(NULL, "/"), 
     prefix = strcat(prefix, "/"), prefix = strcat(prefix, token)){
        {
            strcpy(name, token);
            
        }
    }
    /*Step 2- see if NAME_LEN < strlen(name)
    -> if so then lets put some of name in prefix 
    */
    if(strlen(name) > NAME_LEN)
    {
        int over_size = strlen(name)  - NAME_LEN;
        char *oversize_ptr = name+NAME_LEN;
        char *name_overflow;


        removal = strstr(prefix, name);
        memset(removal-1,'\0', strlen(removal));
    }else
        memset(prefix,'\0', PREFIX_LEN);


    /*Step 2- if the length of the name is to big*/
    if(strlen(name) >= NAME_LEN)
        ;
    strncpy(header_entry->name, name, NAME_LEN);
    strncpy(header_entry->prefix, prefix, PREFIX_LEN);


}
    
/*get_checkSum: -like a hashcode function but adds up all characters in header block, 
                stored as ASCII string terminated by one or more nll chars
                - treat chksum as if it were filled up with spaces
                
                */
void get_chksum(headerEntry *hdr)
{
    uint8_t init_chkSum[CHKSUM_LEN] = {' '};
    uint64_t checkSum = 0;

    checkSum = hash_fieldHeader(init_chkSum, CHKSUM_LEN);
    checkSum += hash_fieldHeader(hdr->name, NAME_LEN);
    checkSum += hash_fieldHeader(hdr->mode, MODE_LEN);
    checkSum += hash_fieldHeader(hdr->uid, UID_LEN );
    checkSum += hash_fieldHeader(hdr->gid , GID_LEN);
    checkSum += hash_fieldHeader(hdr->size , SIZE_LEN);
    checkSum += hash_fieldHeader(hdr->mtime, MTIME_LEN);
    checkSum += hash_fieldHeader(hdr->chksum , CHKSUM_LEN);
    checkSum += hash_fieldHeader(hdr->typeflag , TYPEFLAG_LEN);
    checkSum += hash_fieldHeader(hdr->linkname , LINKNAME_LEN);
    checkSum += hash_fieldHeader(hdr->magic , MAGIC_LEN);
    checkSum += hash_fieldHeader(hdr->version , VERSION_LEN);
    checkSum += hash_fieldHeader(hdr->uname , UNAME_LEN);
    checkSum += hash_fieldHeader(hdr->gname , GNAME_LEN);
    checkSum += hash_fieldHeader(hdr->devmajor , DEVMAJOR_LEN);
    checkSum += hash_fieldHeader(hdr->devminor , DEVMINOR_LEN);
    checkSum += hash_fieldHeader(hdr->prefix , PREFIX_LEN);

    memset(hdr->chksum,checkSum,CHKSUM_LEN);
}


uint64_t hash_fieldHeader(char *feild, int LENGTH){
    int i;
    uint64_t res = 0;
    for (i = 0; i < LENGTH; i++)
        res += feild[i];
    return res;    
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
   get_name_prefix(pathname, header_entry);
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

    get_chksum(&header_entry);
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
/*
void reset_header_entry(headerEntry *entry)
{
memset(hdr->name, '\0', NAME_LEN);
memset(hdr->mode , '\0', MODE_LEN);
memset(hdr->uid , '\0', UID_LEN)

memset(hdr->gid , '\0', GID_LEN)

memset(hdr->size , '\0', SIZE_LE

memset(hdr->mtime , '\0', MTIME_

memset(hdr->chksum , '\0', CHKSU

hdr->typeflag = -1;
memset(hdr->linkname , '\0', LIN

memset(hdr->magic , '\0', MAGIC_

memset(hdr->version , '\0', VERS

memset(hdr->uname , '\0', UNAME_

memset(hdr->gname , '\0', GNAME_

memset(hdr->devmajor , '\0', DEV

memset(hdr->devminor , '\0', DEV

memset(hdr->prefix , '\0', PREFI

}
*/




int main(int argc, char **argv)
{
    headerEntry header_entry;

    /*Test 1- name works*/
    get_name_prefix("/home/victor/file.asm", &header_entry);
    printf("name = : %s", header_entry.name);
    printf("prefix = : %s", header_entry.prefix);


   /*char *pathname = "inputs/test1";
   int tarFd = open("outputs/test1.tar", O_RDONLY| O_TRUNC | O_WRONLY);
   /*Test 2- header work, expcept for gid , uname
    get_stats(pathname, &header_entry);
    print_header(&header_entry);

*/
    return 0;

}
