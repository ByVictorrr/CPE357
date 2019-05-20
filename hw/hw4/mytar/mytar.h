#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/stat.h> 
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define MAX_FLAG 5   /* maximum number of option flags */
#define MIN_ARGS 3   /* mim number of args needed to run program */
#define FILE_INDX 2  /* path starts from the 3rd argument */
#define C 0     /* C flag index*/
#define T 1     /* T flag index*/
#define X 2     /* X flag index*/
#define V 3     /* V flag index*/
#define S 4     /* S flag index*/




/* Two formats: TAR format and USTAR format (extensive) */
/* POSIX header- tar archive has at least block - 512bytes */

struct Header {              /* byte offset */
  char name[100];               /*   0 */
  char mode[8];                 /* 100 */
  char uid[8];                  /* 108 */
  char gid[8];                  /* 116 */
  char size[12];                /* 124 */
  char mtime[12];               /* 136 */
  char chksum[8];       `       /* 148 */
  /* convOctalStr(header->chksum);*/
  char typeflag;                /* 156 */
  char linkname[100];           /* 157 */
  char magic[6];                /* 257 */
  char version[2];              /* 263 */
  char uname[32];               /* 265 */
  char gname[32];               /* 297 */
  char devmajor[8];             /* 329 */
  char devminor[8];             /* 337 */
  char prefix[155];             /* 345 */
  char padding[12];             /* 500 */
};


#define BLOCKSIZE 512
#define TNAMESIZE 100
#define TPREFIXSIZE 155
#define TCHECKSUMSIZE 8
#define MAGIC   "ustar"      /* ustar and a null */
#define TMAGLEN  6
#define TVERSION "00"           /* 00 and no null */
#define TVERSLEN 2

/* Values used in typeflag field.  */
#define NORMALFILE  '0'            /* regular file */
#define AREGTYPE '\0'           /* regular file */
#define LNKTYPE  '1'            /* hard link */
#define SYMTYPE  '2'            /* symbolic link */
#define CHRTYPE  '3'            /* character special */
#define BLKTYPE  '4'            /* block special */
#define DIRTYPE  '5'            /* directory */
#define FIFOTYPE '6'            /* FIFO special */
#define CONTTYPE '7'            /* reserved */


#endif