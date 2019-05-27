#ifndef ENTRY_H
#define ENTRY_H

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "header.h"
#define BLOCK_SIZE 512


void write_header(int tarFd , headerEntry header);
void add_entry(char *pathname, int tarFd);


#endif