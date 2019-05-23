#include "mytar.h"
#include "header.h"
#include "creat.h"

int topStrContains(char *base, char *key) {
    int keyLen = strlen(key);
    char _base[keyLen + 1];
    char _key[keyLen + 1];
    int ret;

    memset(_base, '\0', keyLen + 1);
    memset(_key, '\0', keyLen + 1);
    strcpy(_key, key);
    strncpy(_base, base, keyLen);
    ret = strcmp(_base, _key);
    return ret;
}
void print_verbose(headerEntry header){
	const mode_t mode = oct2uint (header -> mode, 7);
	const char str
	/*test*/
	mode = 777;
	mode = { "-hlcbdp-"[entry -> typeflag? entry -> typeflag -'0':0],
						mode & S_IRUSR?'r': '-',
						mode & S_IWUSR?'w':'-',
						mode & S_IXUSR?'x':'-',
						mode & S_IRGRP?'r':'-',
						mode & S_IWGRP?'w':'-',
						mode & S_IXGRP?'x':'-',
						mode & S_IROTH?'r':'-',
						mode & S_IWOTH?'w':'-',
						mode & S_IXOTH?'x':'-',
						' ',
						'\0'};

	 printf("%s", str);	
}
void print_table(char* pathname, int verbose){
	struct dirent *entry;
	struct headerEntry header;
	struct stat curr_file_info;
	DIR *dp;
	
	if ((dp = opendir(pathname)) == NULL) {
    	perror("-t print: unable to open dir");
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

			get_stats(pathname, &header)
			if(verbose){
				print_verbose(header);
			}
			
        	printf("%s\n", pathname);
        

			strcat(pathname, "/");
			
			print_table(entry->d_name, verbose);
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

void Table(int* flags, int argc, char **argv){
/* ** if V is set, give expended info about each file ** */
	FILE *file;
	headerEntry header; 

	if(argc = MIN_ARGS){
		

		if (strcmp(MAGIC, header.magic)) {
			fprintf(stderr, "Header reading error - Magic\n");
			exit(2);
		}
		
		/* if path is given, go to that path*/
		if (argc > MIN_ARGS) {
            for (i = MIN_ARGS; i < argc; i++) {
                if (topStrContains(&name, argv[i]) == 0) {
                    __listArchive(&name, &header, verbose);
                }
				else{
					fprintf(stderr, "Mytar: %s: Not found in archive\nMytar: Error exit delayed from previous errors.", argv[i]);
					/*can't find the path*/
				}
            }
        } 
		else {
            __listArchive(&name, &header, verbose);
        }

        if (header.typeflag == REGTYPE) {
            if(!extractFile(archive, &header, "/dev/null")) {
                fprintf(stderr, "Error extracting %s\n", name);
                ret = 1;
            }
        }
    }
      
	
if(flags[V]){
    struct stat info;
    if (stat(fp, &) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    
	/*User*/
	if (S_IRUSR & info.st_mode)
		access[1] = 'r';
	else
		access[1] = '-';

	if (S_IWUSR & info.st_mode)
		access[2] = 'w';
	else
		access[2] = '-';

	if (S_IXUSR & info.st_mode)
		access[3] = 'x';
	else
		access[3] = '-';


	/*group*/
	if(S_IRGRP & info.st_mode )
		access[4] = 'r';
	else
		access[4] = '-';

	if (S_IWGRP & info.st_mode )
		access[5] = 'w';
	else
		access[5] = '-';

	if(S_IXGRP & info.st_mode )
		access[6] = 'x';
	else
		access[6] = '-';

	/*owner*/
	if(S_IROTH & info.st_mode )
		access[7] = 'r';
	else
		access[7] = '-';
	if(S_IWOTH & info.st_mode )
		access[8] = 'w';
	else
		access[8] = '-';
	if(S_IXOTH & info.st_mode )
		access[9] = 'x';
	else
		access[9] = '-';
	
}
