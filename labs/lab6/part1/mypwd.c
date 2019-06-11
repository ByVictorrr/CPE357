#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

#define MAX 4096

void checkDir(DIR **directory);

int setInoDev(struct stat *buf, ino_t* ino, dev_t* dev);

void lookForDir(DIR** directory, struct dirent** dir, 
char (*path)[MAX], ino_t* ino, dev_t* dev);

void strChange(char (*str1)[MAX], char (*str2)[256]);

void printPath(char *path);

int main(){

   struct stat buf;
   struct dirent* dir;
   DIR* directory = NULL;
   char path[MAX];
   dev_t dev;
   ino_t ino;
   ino = dev = 0;

   while(1){

      if(setInoDev(&buf, &ino, &dev)){
         printPath(path);
         return EXIT_SUCCESS;
      }

      checkDir(&directory);

      lookForDir(&directory, &dir, &path, &ino, &dev);

   }

   return EXIT_SUCCESS;
}

int setInoDev(struct stat *buf, ino_t* ino, dev_t* dev){
   ino_t oldIno = *ino; 
   dev_t oldDev = *dev;

   if(stat(".", buf) < 0){
      perror(NULL);
      exit(EXIT_FAILURE);
   }

   if((oldIno == buf->st_ino) && (oldDev == buf->st_dev))
      return 1;
   
   *ino = buf->st_ino;
   *dev = buf->st_dev;

   return 0;
}

void checkDir(DIR **directory){
   if(chdir("..") < 0){
      perror(NULL);
      exit(EXIT_FAILURE);
   }

   if((*directory = opendir(".")) == NULL){
      perror(NULL);
      exit(EXIT_FAILURE);
   }
}

void lookForDir(DIR** directory, struct dirent** dir, 
   char (*path)[MAX], ino_t* ino, dev_t* dev){
   
   struct stat temp;
   
   while((*dir = readdir(*directory)) != NULL){
      stat((*dir)->d_name, &temp);
      if(temp.st_dev == (*dev) && temp.st_ino == (*ino))
         strChange(path, &((*dir)->d_name));
   }

   closedir(*directory);
}

void strChange(char (*str1)[MAX], char (*str2)[256]){
   char buffer[MAX];
   int i, len1, len2;
   len1 = strlen(*str1);
   len2 = strlen(*str2);

   buffer[0] = '/';

   for(i = 1; i < len2 + 1; i++)
      buffer[i] = (*str2)[i-1];

   len2++;

   for(i = len1; i >= 0; i--)
      (*str1)[i + len2] = (*str1)[i];

   for(i = 0; i < len2; i++)
      (*str1)[i] = buffer[i]; 
}

void printPath(char *path){
   int i;
   for(i = 5; i < strlen(path); i++)
      printf("%c", path[i]);
   
   printf("\n");
}

