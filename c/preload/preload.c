#include <stdlib.h>

static ssize_t (* writeOriginal) (int fd, const void * buf, size_t count) =
 NULL;

static int (* fputsOriginal) (const char * s, void * stream) = NULL;
//static int (* fwriteOriginal) (const char * s, void * stream) = NULL;
static int (* putsOriginal) (const char * s) = NULL;

#define __USE_GNU
#include <dlfcn.h>

__attribute__((constructor)) void
_saveOriginalFunctions () {
    writeOriginal = 
     (ssize_t (*) (int, const void *, size_t)) dlsym(RTLD_NEXT, "write");
}

#include <string.h>

const char * pszWrite = "*** write ***: ";

ssize_t
write(
  int fd,
  const void * buf,
  size_t count ) {
    writeOriginal(fd, pszWrite, strlen(pszWrite));
    return (writeOriginal(fd, buf, count));
}

const char * pszFputs = "*** fputs ***: ";

int
fputs (
  const char * s,
  void * stream ) {
    if (! fputsOriginal) {
        fputsOriginal = 
         (int (*) (const char *, void *)) dlsym(RTLD_NEXT, "fputs");
    }
    fputsOriginal(pszFputs, stream);
    return (fputsOriginal(s, stream));
}

// fwrite() is a built-in. Unable to hook
#if 0
const char * pszFwrite = "*** fwrite ***: ";

int
fwrite (
  const char * s,
  void * stream ) {
    if (! fwriteOriginal) {
        fwriteOriginal = 
         (int (*) (const char *, void *)) dlsym(RTLD_NEXT, "fwrite");
    }
    fwriteOriginal(pszFwrite, stream);
    return (fwriteOriginal(s, stream));
}
#endif

const char * pszPuts = "*** puts ***: ";

int
puts (
  const char * s ) {
    if (! putsOriginal) {
        putsOriginal = 
         (int (*) (const char *)) dlsym(RTLD_NEXT, "puts");
    }
    writeOriginal(2, pszPuts, strlen(pszPuts));
    return (putsOriginal(s));
}
