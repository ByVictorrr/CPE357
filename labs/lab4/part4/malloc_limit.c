#include <stdio.h> 
#include <stdlib.h> 

#define SIZE 2000


int main(){
    
    char *c = (char *) malloc (SIZE * sizeof(char));
    if(!c){
        printf("malloc is failiing\n");
        exit(1);
    }
    free(c);
    return 0;
}
