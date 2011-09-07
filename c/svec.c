/* sorted vector example */
/* bsearch() */
#include <stdlib.h>
/* qsort() */
#include <stdlib.h>
/* printf() */
#include <stdio.h>
/* strlen() */
#include <string.h>
/* rtrim() */
#include "rtrim.h"
/* fgetsdup() */
#include "fgetsdup.h"

int
compare (
  const void * lhs,
  const void * rhs ) {
    return (strcmp(* ((const char * *) lhs), * ((const char * *) rhs)));
}

#define InitVectorSize 8

int
main (
  int argc,
  char * * argv ) {
  int rc = -1;
  char * psz = NULL;
  char * * ppsz = NULL;
  int i;
  int nNumElem;
  int nMax;
    if (! (ppsz =
     (char * *) malloc((sizeof (char *)) * (nMax = InitVectorSize)) )) {
        goto exception;
    }
    for (i = 0; (psz = fgetsdup(stdin)); free(psz)) {
        if (i >= nMax) {
            if (! (ppsz =
             (char * *) realloc(ppsz, (sizeof (char*)) * (nMax *= 2)) )) {
                goto exception;
            }
        }
        rtrim(psz);
        /* if the first or not found */
        if (i == 0 || (! bsearch((const void *) & psz,
         (const void *) ppsz, (size_t) i, sizeof (* ppsz), compare ))) {
            if (! (ppsz[i ++] = strdup(psz))) {
                goto exception;
            }
            qsort((void *) ppsz, (size_t) i, sizeof (* ppsz), compare);
        }
    }
    nNumElem = i;
    for (i = 0; i < nNumElem; ++ i) { printf("%d: %s\n", i, ppsz[i]); }
    rc = 0;
exception:
    if (psz) { free(psz); }
    for (i = 0; i < nNumElem; ++ i) { free(ppsz[i]); }
    if (ppsz) { free(ppsz); }
    return (rc);
}

/* -------------------------------------------------------------------
$ ./a.out 
hoge
hoge
fuga
fuga
hoge
fuga
HOGE
FUGA
0: FUGA
1: HOGE
2: fuga
3: hoge
------------------------------------------------------------------- */
