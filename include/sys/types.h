#ifndef _TYPES_H_
#define _TYPES_H_

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned int size_t;
#endif

#ifndef _SSIZE_T
#define _SSIZE_T
typedef int ssize_t;
#endif

#ifndef _TIME_T
#define _TIME_T
typedef long time_t;		   /* time in sec since 1 Jan 1970 0000 GMT */
#endif

#ifndef _CLOCK_T
#define _CLOCK_T
typedef long clock_t;		   /* unit for system accounting */
#endif

#ifndef _SIGSET_T
#define _SIGSET_T
typedef unsigned long sigset_t;
#endif

#ifndef NULL
#define NULL	((void *) 0)
#endif


/* Types used in disk, inode, etc. data structures. */
typedef short          dev_t;	   /* holds (major|minor) device pair */
typedef char           gid_t;	   /* group id */
typedef unsigned short ino_t; 	   /* i-node number */
typedef unsigned short mode_t;	   /* file type and permissions bits */
typedef char         nlink_t;	   /* number of links to a file */
typedef unsigned long  off_t;	   /* offset within a file */
typedef int            pid_t;	   /* process id (must be signed) */
typedef short          uid_t;	   /* user id */
typedef unsigned long zone_t;	   /* zone number */
typedef unsigned long block_t;	   /* block number */
typedef unsigned long  bit_t;	   /* bit number in a bit map */
typedef unsigned short zone1_t;	   /* zone number for V1 file systems */
typedef unsigned short bitchunk_t; /* collection of bits in a bitmap */

typedef unsigned char   u8_t;	   /* 8 bit type */
typedef unsigned short u16_t;	   /* 16 bit type */
typedef unsigned long  u32_t;	   /* 32 bit type */

typedef char            i8_t;      /* 8 bit signed type */
typedef short          i16_t;      /* 16 bit signed type */
typedef long           i32_t;      /* 32 bit signed type */

#endif
