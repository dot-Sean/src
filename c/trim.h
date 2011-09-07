#ifndef TRIM_H
#define TRIM_H

/* size_t */
#include <ctype.h>
/* strlen(), memmove() */
#include <string.h>

static inline void
trim (
  char * psz ) {
  int i;
  const char * pszSrc;
    if (! psz) { return; }
    while (psz[0] && isspace(psz[(i = (strlen(psz) - 1))])) {
        psz[i] = '\0';
    }
    for (pszSrc = psz; isspace(pszSrc[0]); ++ pszSrc) { ; }
    if (psz != pszSrc) {
        memmove(psz, pszSrc, strlen(pszSrc) + 1);
    }
}

#endif
