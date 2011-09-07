/* puts() */
#include <stdio.h>

// -------------------------------------------------------------------

/* size_t */
#include <sys/types.h>
/* va_start() */
#include <stdarg.h>
/* malloc() */
#include <stdlib.h>
/* snprintf() */
#include <stdio.h>

static inline char *
strdup_printf(
  const char * pszFmt,
  ...) {
  size_t size;
  va_list args;
  char * pszRet;
    va_start(args, pszFmt);
    for (
     size = (1 << 4);
     size <= (1 << 10) &&
      (pszRet = (char *) malloc((sizeof (char)) * size)) &&
      vsnprintf(pszRet, size, pszFmt, args) >= size;
     size <<= 1 ) {
        free(pszRet);
        pszRet = NULL;
    }
    return (pszRet);
}

// -------------------------------------------------------------------

int
main (
  int argc,
  char * * argv ) {
  int rc = -1;
  char * psz = NULL;
    do {
        if ((psz = strdup_printf("%s - %s", "hoge", "fuga")) == NULL) {
            break;
        }
        puts(psz);
        rc = 0;
    } while (0);
    if (psz) { free(psz); }
    return (rc);
}
