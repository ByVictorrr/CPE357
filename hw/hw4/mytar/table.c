#include "mytar.h"
#include "header.h"
#include "creat.h"

static unsigned int OctToInt(const char* str, unsigned int len) {
	unsigned int res = 0;
	unsigned int i;
	for (i = 0; i < len; i++) {
		char c = str[i];
		if (c){
            res *= 8;
		    res += c - '0';
        }
        else
        {
            break;
        }
	}
	return res;
}



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
void print_table(headerEntry header, int verbose){
	const mode_t mode = OctToInt (header -> mode, 7);
	const char str, ownergr[20];
	struct tm * time;
	time_t mtime;
	/*test*/
	mode = 777;
	str = { "-hlcbdp-"[entry -> typeflag? entry -> typeflag -'0':0],
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
	/* Writing Permission 10 Owner/Group 17 */
	strcpy(ownergr, entry -> uname);
	strcat(ownergr, entry-> gname);
	printf("%s %-17s", str, ownergr);	
	switch (entry -> type){
	case REGULAR: case NORMAL: case CONTIGUOUS:
		printf("%+8d",entry -> size);
		break;
	case HARDLINK: case SYMLINK: case DIRECTORY: case FIFO:
		printf("%+8d",entry -> size);
		break;
	case CHAR: case BLOCK:
		printf( "%d,%d", entry -> major, entry -> minor);
		break;
	default: 
		fprintf(stderr, "Error: failed to list archive in verbose mode");
	}

	mtime = OctToInt(entry -> mtime);
	time = localtime(&mtime);
	printf(" %4d-%02d-%02d %02d:%02d ", time -> tm_year + 1900, time -> tm_mon + 1, time -> tm_mday, time -> tm_hour, time -> tm_min);
	}

	fprintf(f, "%s", entry -> name);

	if (verbose){
		switch (entry -> type){
			case HARDLINK:
				printf(" link to %s", entry -> link_name);
				break;
			case SYMLINK:
				printf(" -> %s", entry -> link_name);
				break;
			break;
		}
	}
}
void list_archieve(char* pathname, int verbose){
	struct dirent *entry;
	struct headerEntry header;
	struct stat st;
	DIR *dp;
	
	if ((dp = opendir(pathname)) == NULL) {
    	perror("-t print: unable to open dir");
    	exit(EXIT_FAILURE);
    }
	chdir(pathname);
	while ((entry = readdir(dp)) != NULL) {
    	if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
        	continue;
    	} 
		else{
			if (lstat(entry->d_name), &st) == -1) {
					perror("traverse");
					exit(EXIT_FAILURE);
				}
				if (S_ISDIR(st.st_mode) == 0) {
					get_stats(entry->d_name, &header);
					print_table(header, verbose);
					strcat(pathname, "/");
					list_archieve(pathname, verbose);
				}
				else if (S_ISREG(curr.st_mode) == 0) {
					/*strcat(pathname, entry->d_name);*/
					/*print path name if verbose is used*/
					get_stats(pathname, &header);
					print_table(header, verbose);
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
                    list_archieve(char* pathname, int verbose)
                }
				else{
					fprintf(stderr, "Mytar: %s: Not found in archive\nMytar: Error exit delayed from previous errors.", argv[i]);
					/*can't find the path*/
				}
            }
        } 
		else {
            list_archieve(char* pathname, int verbose)
        }

        if (header.typeflag == REGTYPE) {
            if(!extractFile(archive, &header, "/dev/null")) {
                fprintf(stderr, "Error extracting %s\n", name);
                ret = 1;
            }
        }
    }
      
}
