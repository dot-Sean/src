#include "kfc_mem.h"

static int MemDeb_n_;
#include <stdio.h> /* fprintf() */
void *
mallocDebug (
  size_t size ) {
    MemDeb_n_ ++;
    fprintf(stderr, "malloc() -> %d\n", MemDeb_n_);
    return (mallocSafe(size));
}
char *
strdupDebug (
  const char * psz ) {
    MemDeb_n_ ++;
    fprintf(stderr, "strdup() -> %d\n", MemDeb_n_);
    return(strdupSafe(psz));
}
void *
reallocDebug (
  void * pv,
  size_t size ) {
    fprintf(stderr, "realloc() -> %d\n", MemDeb_n_);
    return (reallocSafe(pv, size));
}
void
freeDebug (
  void * pv ) {
    MemDeb_n_ --;
    fprintf(stderr, "free() -> %d\n", MemDeb_n_);
    freeSafe(pv);
}

#include "kfc_err.h"
#include <stdlib.h> /* malloc(), etc ... */
#include <string.h> /* strdup(), memset() */
void *
mallocSafe (
  size_t size ) {
  void * pv = malloc(size);
    if (! pv) {
        Die(("mallocSafe() failed"));
    }
    memset(pv, 0, size);
    return (pv);
}
char *
strdupSafe (
  const char * psz ) {
  char * pszNew = strdup(psz);
    if (! psz) {
        Die(("strdupSafe() failed"));
    }
    return (pszNew);
}
void *
reallocSafe (
  void * pv,
  size_t size ) {
  void * pvNew = realloc(pv, size);
    if (! pvNew) {
        Die(("reallocSafe() failed"));
    }
    return (pvNew);
}
void
freeSafe (
  void * pv ) {
    if (pv) {
        free(pv);
    }
}

