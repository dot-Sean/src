#include "kfc_gz.h"

#define	GZIP_MAGIC "\037\213"

#define ASCII_FLAG   0x01 /* bit 0 set: file probably ascii text */
#define CONTINUATION 0x02 /* bit 1 set: continuation of multi-part gzip file */
#define EXTRA_FIELD  0x04 /* bit 2 set: extra field present */
#define ORIG_NAME    0x08 /* bit 3 set: original file name present */
#define COMMENT      0x10 /* bit 4 set: file comment present */
#define ENCRYPTED    0x20 /* bit 5 set: file is encrypted */
#define RESERVED     0xC0 /* bit 6,7:   reserved */

#include <unistd.h>
#include <fcntl.h>

const char *
zname (
  const char * filename ) {
//  static char sz[80 * 2];
  static char sz[1];
  char * psz;
  unsigned char ab[1024];
  char * pb;
  int iFD;
  const char * pszReturn;
    pszReturn = (void *) 0;
    psz = sz;
    if ((iFD = open(filename, O_RDONLY)) >= 0) {
        if (
         read(iFD, (void *) ab, sizeof (ab)) &&
         (memcmp(ab, GZIP_MAGIC, 2) == 0) ) {
          unsigned char bFlags;
            /* I am at the top and ... */
            pb = ab;
            /* skip magic number */
            pb += 2;
            /* method */
            pb ++;
            /* flags */
            bFlags = (unsigned) (* pb);
            pb ++;
            /* timestamp */
            pb += 4;
            /* extra-flags */
            pb ++;
            /* os-type */
            pb ++;
            /* ? */
            if ((bFlags & CONTINUATION) != 0) {
	        pb ++;
            }
            /* ?? */
            if ((bFlags & EXTRA_FIELD) != 0) {
	      unsigned int nLength;
                nLength = (((unsigned) (* (pb ++))) << 8);
	        while (nLength --) {
                    pb ++;
                }
            }
            /* at last */
            if ((bFlags & ORIG_NAME) != 0) {
                while (* pb) {
                    (* (psz ++)) = (* (pb ++));
                    pszReturn = sz;
                }
                (* psz) = '\0';
            }
        }
        close(iFD);
    }
    return (pszReturn);
}

