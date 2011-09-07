#include <stdlib.h>

struct Splitter {
    char * pszBuf;
    char * * ppsz;
};

struct Splitter *
Splitter_new () {
  struct Splitter * self = \
   (struct Splitter *) malloc(sizeof (struct Splitter));
    self->pszBuf = NULL;
    self->ppsz = NULL;
    return (self);
}

void
Splitter_delete (
  struct Splitter * self ) {
    free(self);
}

int
Splitter_splitEx (
  struct Splitter self,
  const char * pszDelim,
  const char * pszSubject,
  int nMax ) {
    return (0);
}

int
Splitter_split (
  struct Splitter self,
  const char * pszDelim,
  const char * pszSubject ) {
    return (Splitter_splitEx(self, pszDelim, pszSubject, -1));
}

int
main (
  int argc,
  char * * argv ) {
  struct Splitter * psplitter = Splitter_new();
    //Splitter_split(psplitter, 
    if (psplitter) { Splitter_delete(psplitter); }
    return (0);
}
