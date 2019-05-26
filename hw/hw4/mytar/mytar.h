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

#define MAX_FLAG 6   /* maximum number of option flags */
#define MIN_ARGS 3   /* mim number of args needed to run program */
#define FILE_INDX 2  /* path starts from the 3rd argument */


/* Two formats: TAR format and USTAR format (extensive) */
/* POSIX header- tar archive has at least block - 512bytes */



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
