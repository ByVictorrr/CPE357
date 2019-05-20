#include "mytar.h"
#include "header.h"

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

void Table(int* flags, int argc, char **argv){
/* ** if V is set, give expended info about each file ** */
	FILE *file;
	headerEntry header; 
	file = fopen(argv[2], "rb");
	if(file == NULL){
		fprintf(stderr, "Error opening %s\n", argv[2]);
		exit(1);
	}
	/* read a binary file 
	an unfortunate newline-translation won't mess the data.*/
 	while (fread(&header, BLOCKSIZE, 1, file) != 0) {


		if (strcmp(MAGIC, header.magic)) {
			fprintf(stderr, "Header reading error - Magic\n");
			exit(2);
		}


		if (argc > MIN_ARGS) {
            for (i = MIN_ARGS; i < argc; i++) {
                if (topStrContains(&name, argv[i]) == 0) {
                    __listArchive(&name, &header, verbose);
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
