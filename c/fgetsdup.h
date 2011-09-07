#ifndef FGETSDUP_H
#define FGETSDUP_H

/* FILE */
#include <stdio.h>
/* malloc() */
#include <stdlib.h>
/* strlen() */
#include <string.h>

/* must be ge 2 */
#define FgetsdupInitSize 8

static char *
fgetsdup (
  FILE * pfile ) {
  char * pszRet = NULL;
  char * pszHead = NULL;
  size_t size;
  size_t sizeAll;
  size_t sizeStrlen;
  char * psz;
    if (! pfile || feof(pfile)) {
        goto exception;
    }
    if (! (psz = pszHead = (char *) malloc((sizeof (char)) *
     (size = sizeAll = FgetsdupInitSize) ))) {
        goto exception;
    }
    sizeStrlen = 0;
    while (1) {
        if (! fgets(psz, size, pfile)) {
            /* if just size buffer at eof, feof() returns 0 */
            if (sizeStrlen > 0) {
                break;
            }
            goto exception;
        }
        if (pszHead[(sizeStrlen += strlen(psz)) - 1] == '\n' ||
         feof(pfile) ) {
            break;
        }
        if (! (pszHead = realloc(pszHead, sizeAll *= 2))) {
            goto exception;
        }
        psz = pszHead + sizeStrlen;
        size = sizeAll - sizeStrlen;
    }
    pszRet = pszHead;
    pszHead = NULL;
exception:
    if (pszHead) { free(pszHead); }
    return (pszRet);
}

#endif
