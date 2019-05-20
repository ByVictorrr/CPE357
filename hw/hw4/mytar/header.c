#include "header.h"

void print_error(uint8_t *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
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



void freeHeaderEntry(he)
{
    if(name != NULL)
        free(name);
    if(mode != NULL)
        free(mode);
    if(uid != NULL)
        free(uid);
    if(gid != NULL)
        free(gid);
    if(size != NULL)
        free(size);
    if(mtime != NULL)
        free(mtime);
    if(chksum != NULL)
        free(chksum);
    if(linkname != NULL)
        free(linkname);
    if(magic != NULL)
        free(magic);
    if(version != NULL)
        free(version);
    if(name != NULL)
        free(name);
    if(name != NULL)
        free(name);
    if(devmajor != NULL)
        free(devmajor);
    if(devminor != NULL)
        free(devminor);
    if(prefix != NULL)
        free(prefix);
}

int main(int argc, char *argv[])
{
    
    creat_header(argv[1]);

    printf("header: %s", header);


    return 0;
}

