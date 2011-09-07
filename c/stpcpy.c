#include <stdio.h>
#include <string.h>

char *
stpncpy2 (
  char * pszDest,
  char * pszFrom,
  size_t size ) {
    return (strncpy(pszDest, pszFrom, size) + strlen(pszDest));
}

int
main (
  int argc,
  char * * argv ) {
  char * psz;
  char sz[256];
    psz = stpncpy(sz, "hoge", sizeof (sz));
    printf("%p %p\n", sz, psz);
    psz = stpncpy2(sz, "hoge", sizeof (sz));
    printf("%p %p\n", sz, psz);
    return (0);
}
