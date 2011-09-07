#include "kfc.h"

#if 0
  #define MemDebug
#endif
#include "kfc_mem.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h> /* vsnprintf() */
#include <stdarg.h>

struct StrImp {
    char * psz;
};

Str 
Str_new (
  const char * psz ) {
  Str self = New(struct StrImp, 1);
    self->psz = (void *) 0;
    Str_assign(self, psz);
    return (self);
}

void
Str_delete (
  Str self ) {
    if (self->psz) {
        Delete(self->psz);
    }
    Delete(self);
}

const char *
Str_get (
  Str self ) {
    return ((self->psz)? self->psz: "");
}

Str
Str_assign (
  Str self,
  const char * psz ) {
    if (self->psz) {
        Free((void *) self->psz);
    }
    if (psz) {
        self->psz = New(char, strlen(psz) + 1);
        strcpy(self->psz, psz);
    }
    return (self);
}

Str 
Str_append (
  Str self, 
  const char * psz ) {
    if (! self->psz) {
        Str_assign(self, "");
    }
    if (psz) {
        self->psz =
         Renew(char, strlen(self->psz) + strlen(psz) + 1, self->psz);
        strcat(self->psz, psz);
    }
    return (self);
}

int
Str_compare (
  Str self,
  const char * psz ) {
    return (strcmp(Str_get(self), psz));
}

int 
Str_length (
  Str self ) {
    return (strlen(self->psz));
}

int
Str_vappendf (
  Str self,
  const char * pszFormat,
  va_list args ) {
  int n;
  int nAllocSize = 80;
  char * psz = (void *) 0;
    while (True) {
        if (psz) {
            Delete(psz);
        }
        psz = New(char, nAllocSize);
        n = vsnprintf(psz, nAllocSize, pszFormat, args);
        if (n == -1 || n + 1 > nAllocSize) {
            /* glibc <= 2.0.6 */
            if (n == -1) {
                nAllocSize *= 2;
            } else {
                nAllocSize = n + 1;
            }
        } else {
            Str_append(self, psz);
            break;
        }
    }
    Delete(psz);
    return (n);
}

int
Str_appendf (
  Str self,
  const char * pszFormat,
  ... ) {
  int n;
  va_list args;
    va_start(args, pszFormat);
    n = Str_vappendf(self, pszFormat, args);
    va_end(args);
    return (n);
}

Str
Str_vnewf (
  const char * pszFmt,
  va_list args ) {
  Str self;
  Str str;
    str = Str_new("");
    Str_vappendf(str, pszFmt, args);
    self = Str_new(Str_get(str));
    Str_delete(str);
    return (self);
}

Str
Str_newf (
  const char * pszFmt,
  ... ) {
  Str self;
  va_list args;
    va_start(args, pszFmt);
    self = Str_vnewf(pszFmt, args);
    va_end(args);
    return (self);
}

int
Str_vassignf (
  Str self,
  const char * pszFormat,
  va_list args ) {
  int n;
    Str_assign(self, "");
    n = Str_vappendf(self, pszFormat, args);
    return (n);
}

int
Str_assignf (
  Str self,
  const char * pszFormat,
  ... ) {
  int n;
  va_list args;
    va_start(args, pszFormat);
    n = Str_vassignf(self, pszFormat, args);
    va_end(args);
    return (n);
}
