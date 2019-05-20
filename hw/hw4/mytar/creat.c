#include <sys/stat.h>
#include <stdint.h>

/* HEADER FIELD LENGTHS */
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


/*creat_achieve: called when the main gets option c
 * followed by:  f || f and v
 *
 * */
void creat_archive(char **argv, int options) {
   int i = 0;
   char c;
   struct stat info_file;

   /*Step 1 - get info about the file/directory to be compresed (path) */
   if (lstat(argv[3], &info_file) == -1)
       print_err("lstat: error in creat_archieve");


   /*Step 2 - use conditional glags to print if verbosity*/
   if (flags == 0 || flags == 1) {
      c = *pathname;
      while(i < strlen(pathname)) {
         if (c != '/' && c != '\0') {
            printf("%c", c);
            c = pathname[i + 1];
         }
         i++;
      }
      printf("\n");
   }

   if (S_ISDIR(curr.st_mode)) {
      add_archive_entry(pathname, pathname, outfd, 2, flags);
      traverse(pathname, outfd, flags);
   }
   else if (S_ISREG(curr.st_mode)) {
      add_archive_entry(pathname, pathname, outfd, 0, flags);
   }

   else if (S_ISLNK(curr.st_mode)) {
      add_archive_entry(pathname, pathname, outfd, 1, flags);
   }
}

void traverse(char *pathname, int outfd, int flags) {
   struct dirent *entry;
   struct stat curr;
   DIR *dp;
   char *end;

   /*printf("pathname: %s\n", pathname);*/
   /*printf("flags: %d\n", flags);*/
   /*printf("dab\n");*/
   if ((dp = opendir(pathname)) == NULL) {
      perror("traverse dir");
      exit(EXIT_FAILURE);
   }

   while ((entry = readdir(dp)) != NULL) {
      if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
         continue;
      } 

      if (lstat(strcat(pathname, entry->d_name), &curr) == -1) {
         perror("traverse");
         exit(EXIT_FAILURE);
      }

      if (S_ISDIR(curr.st_mode)) {
         /*printf("HELLO\n");*/
         /*strcat(pathname, entry->d_name);*/
         /*print path name if verbose is used*/
         if (flags == 0 || flags == 1) {
            printf("%s\n", pathname);
         }

         strcat(pathname, "/");
         add_archive_entry(pathname, entry->d_name, outfd, 2, flags);

         traverse(pathname, outfd, flags);

         end = pathname + strlen(pathname) - (strlen(entry->d_name) + 1);
         *end = '\0';
      }
      else if (S_ISREG(curr.st_mode)) {
         /*strcat(pathname, entry->d_name);*/
         /*print path name if verbose is used*/
         if (flags == 0 || flags == 1) {
            printf("%s\n", pathname);
         }

         add_archive_entry(pathname, entry->d_name, outfd, 0, flags);
         end = pathname + strlen(pathname) - (strlen(entry->d_name));
         *end = '\0';
      }
      else if (S_ISLNK(curr.st_mode)) {
         /*strcat(pathname, entry->d_name);*/
         /*print path name if verbose is used*/
         if (flags == 0 || flags == 1) {
            printf("%s\n", pathname);
         }

         add_archive_entry(pathname, entry->d_name, outfd, 1, flags);
         end = pathname + strlen(pathname) - (strlen(entry->d_name));
         *end = '\0';
      }
   }
}




char *creat_name(uint8_t *pathname){
    uint8_t *token, *name;
    int i; 
    if((name = malloc(sizeof(uint8_t)*strlen(pathname))) == NULL)
    {
        perror("stat err");
        exit(EXIT_FAILURE);
    }
    /*Step 1 - seperate the pathname and the actual file/dir name*/

    /*first token*/
    token = strtok(pathname, "/"); 
    while(token != NULL){
        printf("string tokenizing : %s", token);
        token = strcpy(NULL, "/");
    }
    /*step 2 - check if name is bigger than the name FIELD max*/
    if(NAME_SIZE < strlen(name))
    {
        /*just put as much of the name as possible in there*/
        strncpy(name, name, NAME_SIZE);
    }else{
        strcpy(name,pathname);
    }
    return name;
}

uint8_t *creatPrefix(uint8_t *pathname)
{
    uint8_t *prefix, *name;
    uint8_t *token;


    if((name = malloc(sizeof(uint8_t)*strlen(pathname))) == NULL)
    {
        perror("stat err");
        exit(EXIT_FAILURE);
    }
}

void creat_header(uint8_t *pathname)
{
    struct stat file_info;
    /*Step 1 - init header to all zeros*/
    if(!memset(header, 0, BLOCK_SIZE))
    {
        perror("memset err");
        exit(EXIT_FAILURE);
    }
    /*
    if(!lstat(pathname, &file_info))
    {
        perror("stat err");
        exit(EXIT_FAILURE);
    }
    */
    /*Step 3.1 - write the name to header array*/
    strncpy(header,creat_name(pathname),NAME);
}
