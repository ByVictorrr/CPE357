#ifndef HEADER_H
#define HEADER_H
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <syscall.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
/*===================Header function and vars=====================================*/
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
    uint8_t chksum[CHKSUM_LEN];
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


void print_err(char *msg);

/*get_name : gets the name of the pathname with nothing in front*/
void get_name_prefix(char *pathname, headerEntry *header_entry);
    
void get_typeflags(char *pathname, headerEntry *header_entry);

void get_linkname(char *pathname, headerEntry *header_entry);

void get_stats(const char *pathname, headerEntry *header_entry);

void print_header(headerEntry *hdr);

void reset_header_entry(headerEntry *entry);

#endif
