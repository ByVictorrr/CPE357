#include <sys/stat.h>
#include <stdint.h>
#include "header.h"


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

   /*Step 3 - file type check what path is */
   if (S_ISDIR(info_file.st_mode)) {
      /*where does pathname come from*/
      add_entry(pathname, pathname, outfd, 2, flags);

      traverse(pathname, outfd, flags);
   }
   else if (S_ISREG(curr.st_mode)) {
      add_entry(pathname, pathname, outfd, 0, flags);
   }

   else if (S_ISLNK(curr.st_mode)) {
      add_entry(pathname, pathname, outfd, 1, flags);
   }
}

/*transverse_dir: if path is a directory its used to transverse it and its subdirectories*/
void traverse_dir(char **argv, int options) {
   struct dirent *entry;
   struct stat curr_file_info;
   DIR *dp;

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


