#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CHUNK 300
#define SIZE 100
char *readlongline(FILE *);
int main(int argc, char *argv[]) {
    FILE *fp = fopen(argv[1], "r");
    char *line;
    if(argc <= 1){
        /*take in lines on terminal */
        fprintf(stderr, "uniq: can't open\n");
        exit(2);
    }
    else{
        if(fp  == NULL){
            fprintf(stderr, "uniq: can't open %s\n", argv[0]);
            exit(1);
        }
        else{
            /* tests the end-of-file indicator for the given stream.
            return non zero if EOF */
            line = readlongline(fp);
            printf("%s",line);
            free(line);
        }
    }
    fclose(fp);
    return 0;
}


char *readlongline(FILE *where) {
/* Read a string from given stream. Returns the string, or NULL if
* EOF is encoutered. Approach: allocate a buffer of size CHUNK,
* and as the string grows expand the buffer as necessary.
* returns NULL on EOF;
*/
    char *buff;
    char *cur = NULL, *prev = NULL;
    int sofar, len;
    /* get an initial buffer, and make it a well–formed string */
    if (NULL == (buff = (char *) malloc( sizeof(char) *CHUNK))) {
        perror("malloc");
        exit(1);
    }
    buff[0] = '\0';
    sofar = 0; /* we don’t have anything yet */
    /* now, read the string, expanding as necessary. Loop until
    * we either hit a newline of EOF
    */
    while (fgets(buff + sofar, CHUNK, where)) {
        len = strlen(buff + sofar);
        if(cur){
          free(cur);
          cur = NULL;
        }
        cur = (char *)malloc((len + 1)*sizeof(char));
        strcpy(cur, buff + sofar);
        if(prev!= NULL && !strcmp(prev, cur)){
          /*same string as previous, clear up the everything*/
          free(cur);
          cur = NULL;
          len = 0;
        }
        else{
          if(prev){
            free(prev);
            prev = NULL;
          }
          prev = (char *)malloc((len + 1)*sizeof(char));
          /*different string -update prev*/
          strcpy(prev, cur);
        }
        /*initialize prev string - first row*/
        /* now, we either have a whole line or not. Check. */
        sofar += len; /* add in the new part of the string */

        if (buff[sofar] == '\n'){
            break; /* it’s a newline, so we’re done. */
            /* if we got here, it’s not a newline, so we’re both
            * not done and out of buffer. Reallocate and go ’round again.
            */
        }
        buff = (char*)realloc(buff, sizeof(char) *(sofar+CHUNK));
        if ( NULL == buff ) { /* realloc failed. */
            perror("realloc");
            exit(2);
        }

    }
    /* Now we have the whole string, but we might have allocated too
    * much memory. If it’s empty we hit EOF, free it and return
    * NULL. If not, trim it down to size.
    */

    if ( sofar == 0 ) { /* EOF */
        free(buff);
        buff = NULL;
    }
    else { /* trim to size */
        buff = realloc(buff, sofar + 1);
        if ( NULL == buff ) { /* realloc failed. */
        perror("realloc");
        exit(2);
        }
    }

    if(prev){
      free(prev);
      prev = NULL;
    }
    if(cur){
      free(cur);
      cur = NULL;
    }

    return buff;
}
