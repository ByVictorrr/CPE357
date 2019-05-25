#include "header.h"

/*=================UTILITY FNS======================================*/
void print_err(char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

/*dec_to_oct_asciiString: convert value -> octal value stores that in buff[i]*/
void dec_to_oct_asciiString(uint64_t *buff, unsigned long value ,int LENGTH)
{
    int i, org_value = value;
    uint64_t copy[LENGTH];

    memset(buff, '\0', LENGTH);

    for(i = LENGTH-2 ; value != 0 && i> -1; i--, value /= OCTAL)
    {
        buff[i] = (value % OCTAL) + ASCII_OFFSET;
        if(value != 0 && i==0)
            insert_special_int(buff, LENGTH, org_value);
    }
}
uint64_t hash_fieldHeader(uint8_t *field, int LENGTH){
    int i;
    uint64_t res = 0;
    for (i = 0; i < LENGTH; i++)
        res += field[i];
    return res;    
}

/* For interoperability with GNU tar. GNU seems to
 * set the high–order bit of the first byte, then
 * treat the rest of the field as a binary integer
 * in network byte order.
 * Insert the given integer into the given field
 * using this technique. Returns 0 on success, nonzero * otherwise
 * */
int insert_special_int(char *where, size_t size, int32_t val) { 
    int err=0;
    if(val<0||(size<sizeof(val)) ){
        /* if it’s negative, bit 31 is set and we can’t use the flag
         * if len is too small, we can’t write it. * done.
         */
        err++;
    } 
    else {
        /* game on....*/
        memset(where, 0, size);
        *(int32_t *)(where+size-sizeof(val)) = htonl(val);
        *where |= 0x80; /* set that high–order bit */
    }
    return err; 
}
/*===================================================================*/

/*get_name : gets the name of the pathname with nothing in front
Assumption: PATHMAX > strlen(pathname)
*/
void get_name_prefix(char *pathname, headerEntry *header_entry)
{

    char name[NAME_LEN];
    char prefix[PREFIX_LEN];
    int i;
    char *token;

    /*Step -1 : initalize the arrays to null char*/
    memset(name, '\0', NAME_LEN);
    memset(prefix, '\0', PREFIX_LEN);

    /*Step 0 - throw error if strlen(path) > NAME_LEN+PREFIX_LEN*/
    if(strlen(pathname) > NAME_LEN + PREFIX_LEN)
        print_err("pathname is so long");

    /*Step 1 - check if pathname is shorter than then name_len*/
    if(strlen(pathname) <= NAME_LEN){
        strcpy(name, pathname);
    }
    /*Step 2 - what if the pathname is longer than the NAME_LEN*/
    else{
        /*in this case we have to break apart the pathname into two parts:
        1.)name
        2.)prefix
        */
       /*Step 2.0 - check if its not possible to fit the pathname into name + prefix field*/
       if(strlen(pathname) - NAME_LEN > PREFIX_LEN)
       {
           perror("prefix Length is to small\n");
           exit(EXIT_FAILURE);
       }
       /*Step 2.1 - copy the contents before reach NAME_LEN to prefix*/
       for(i = 0; i < strlen(pathname) - NAME_LEN; i++ )
       {
           prefix[i] = pathname[i];
       }
       /*2.2 - here i is where we start inputting pathname[i] to name*/
       printf("i = %d\n", i);
       strcpy(name, pathname+i);
    }
            
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
    checkSum += hdr->typeflag;
    checkSum += hash_fieldHeader(hdr->linkname , LINKNAME_LEN);
    checkSum += hash_fieldHeader(hdr->magic , MAGIC_LEN);
    checkSum += hash_fieldHeader(hdr->version , VERSION_LEN);
    checkSum += hash_fieldHeader(hdr->uname , UNAME_LEN);
    checkSum += hash_fieldHeader(hdr->gname , GNAME_LEN);
    checkSum += hash_fieldHeader(hdr->devmajor , DEVMAJOR_LEN);
    checkSum += hash_fieldHeader(hdr->devminor , DEVMINOR_LEN);
    checkSum += hash_fieldHeader(hdr->prefix , PREFIX_LEN);

    /*Encode checkSum into a ASCII octal number*/
    dec_to_oct_asciiString(hdr->chksum, checkSum, CHKSUM_LEN);
}

void get_linkname(char *pathname, headerEntry *header_entry)
{
    struct stat file_info;
    char c, buff[LINKNAME_LEN];
    int fd, i, n;
    
    memset(buff, '\0', LINKNAME_LEN);
    if(lstat(pathname, &buff) == -1)
        print_err("stat error in get_linkname");
    if((fd = open(pathname, O_RDONLY)) == -1)
        print_err("open err in get_linkname");
    /*Step 1 - read from the symlink the pathname of the link*/
    for(i = 0; (n=read(fd, &c, 1)) > 0 || i<= LINKNAME_LEN-1; i++)
    {
        buff[i] = c;
    }
    memcpy(header_entry->linkname, buff, LINKNAME_LEN);
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

void get_stats(const char *pathname, headerEntry *header_entry)
{
   struct stat file_info;
   struct passwd *pass;
   struct group *grp;

   if(lstat(pathname, &file_info) == -1)
       print_err("stat err, {in get_stats function");


    pass=getpwuid(file_info.st_uid);
    grp=getgrgid(file_info.st_gid);

   /*Setting each member in header struct to that of pathname attribute*/
   get_name_prefix(pathname, header_entry);

   dec_to_oct_asciiString(header_entry->mode,&file_info.st_mode, MODE_LEN);
   dec_to_oct_asciiString(header_entry->gid, &file_info.st_gid, GID_LEN);
   dec_to_oct_asciiString(header_entry->size, &file_info.st_size, SIZE_LEN);
   dec_to_oct_asciiString(header_entry->mtime, &file_info.st_mtime, MTIME_LEN);
   get_typeflags(pathname, header_entry);

   if(header_entry->typeflag == '2')
       get_linkname(pathname, header_entry);
   else
       memset(header_entry->linkname, '\0', LINKNAME_LEN);
    
    strncpy(header_entry->magic, "ustar", MAGIC_LEN);
    memset(header_entry->version, '\0', VERSION_LEN);
    strncat(header_entry->uname, pass->pw_name, UID_LEN);
    strncat(header_entry->gname, grp->gr_name, GID_LEN);

   dec_to_oct_asciiString(header_entry->devmajor, '\0', DEVMAJOR_LEN);
   dec_to_oct_asciiString(header_entry->devminor, '\0', DEVMINOR_LEN);

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
void reset_header_entry(headerEntry *hdr)
{
memset(hdr->name, '\0', NAME_LEN);
memset(hdr->mode , '\0', MODE_LEN);
memset(hdr->uid , '\0', UID_LEN);
memset(hdr->gid , '\0', GID_LEN);
memset(hdr->size , '\0', SIZE_LEN);
memset(hdr->mtime , '\0', MTIME_LEN);
memset(hdr->chksum , '\0', CHKSUM_LEN);
hdr->typeflag = -1;
memset(hdr->linkname , '\0', LINKNAME_LEN);
memset(hdr->magic , '\0', MAGIC_LEN);
memset(hdr->version , '\0', VERSION_LEN);
memset(hdr->uname , '\0', UNAME_LEN);
memset(hdr->gname , '\0', GNAME_LEN);
memset(hdr->devmajor , '\0', DEVMAJOR_LEN);
memset(hdr->devminor , '\0', DEVMINOR_LEN);
memset(hdr->prefix , '\0', PREFIX_LEN);
}


int main(int argc, char **argv)
{
    headerEntry header_entry;

    /*Test 1- name works*/
    char *pathname = "/victor/delaplaine/aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaakkkkkkkkkkkkkkkkkkkkkkkkkkkkk";
    get_name_prefix(pathname, &header_entry);
    printf("strlen(pathname) = %d\n", strlen(pathname));
    printf("strlen(name) = %d\n", strlen(header_entry.name));
    printf("strlen(prefix) = %d\n", strlen(header_entry.prefix));

    printf("name = : %s\n", header_entry.name);
    printf("prefix = : %s\n", header_entry.prefix);
/*
   char *pathname = "inputs/header/test1";
   int tarFd = open("outputs/header/test1.tar", O_RDONLY| O_TRUNC | O_WRONLY);
   struct stat buff;
    /*stat(pathname, &buff);/*
    get_stats(pathname, &header_entry);
    print_header(&header_entry);
    */
    return 0;

}
