#ifndef STRDUPF_H
#define STRDUPF_H

#ifdef __USE_ISOC99

/* malloc() */
#include <stdlib.h>
/* *printf() */
#include <stdio.h>
/* va_start() */
#include <stdarg.h>

static inline char *
strdupf (
  const char * pszFmt,
  ... ) {
  va_list args;
  char * pszRet;
    va_start(args, pszFmt);
    if ((pszRet = (char *) malloc((sizeof (char)) *
     (vsnprintf(NULL, 0, pszFmt, args) + 1 ) ))) {
        vsprintf(pszRet, pszFmt, args);
    }
    return (pszRet);
}

#else

/* size_t */
#include <sys/types.h>
/* malloc() */
#include <stdlib.h>
/* snprintf() */
#include <stdio.h>
/* va_start() */
#include <stdarg.h>

#define StrdupfInitSize 16

static char *
strdupf (
  const char * pszFmt,
  ... ) {
  char * pszRet;
  size_t sizeReq;
  va_list args;
    va_start(args, pszFmt);
    if (! (pszRet = (char *) malloc((sizeof (char)) * StrdupfInitSize))) {
        return (NULL);
    }
    if ((sizeReq = vsnprintf(pszRet, StrdupfInitSize, pszFmt, args) + 1) <=
     StrdupfInitSize ) {
        return (pszRet);
    }
    free(pszRet);
    if ((pszRet = (char *) malloc((sizeof (char)) * sizeReq))) {
        vsprintf(pszRet, pszFmt, args);
    }
    return (pszRet);
}

#endif

#endif
