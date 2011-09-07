#include "str.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

struct StrImp {
    char * psz;
};

Str Str_new (const char * psz) {
  Str self = (Str) malloc(sizeof (struct StrImp));
    self->psz = strdup(psz);
    return (self);
}

void Str_free (Str self) {
    free((void *) (self->psz));
    free((void *) self);
}

const char * Str_get (Str self) {
    return (self->psz);
}

void Str_appendf (Str self, const char * pszFormat, ...) {
  va_list args;
  size_t sizeRequired;
    va_start(args, pszFormat);
    sizeRequired = vsnprintf((void *) 0, 0, pszFormat, args) + 1;
    self->psz = (char *) realloc((void *) (self->psz),
     strlen(self->psz) + sizeRequired );
    vsnprintf((self->psz) + strlen(self->psz), sizeRequired,
     pszFormat, args );
}
