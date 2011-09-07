#ifndef RTRIM_H
#define RTRIM_H

/* size_t */
#include <ctype.h>
/* strlen() */
#include <string.h>

static inline void
rtrim (
  char * psz ) {
  int i;
    if (! psz) { return; }
    while (psz[0] && isspace(psz[(i = (strlen(psz) - 1))])) {
        psz[i] = '\0';
    }
}

#endif
