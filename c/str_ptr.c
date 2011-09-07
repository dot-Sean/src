#include "str_ptr.h"

#include <stdlib.h>
#include <string.h>

char *
Str_new (
  const char * pszConst ) {
    return (strdup(pszConst));
}

void
Str_free (
  char * * ppsz ) {
    free((void *) (* ppsz));
}

#include <stdarg.h>
#include <stdio.h>

void
Str_appendf (
  char * * ppsz,
  const char * pszFormat,
  ... ) {
  va_list args;
  size_t sizeRequired;
    va_start(args, pszFormat);
    sizeRequired = vsnprintf((void *) 0, 0, pszFormat, args) + 1;
    (* ppsz) = (char *) realloc((void *) (* ppsz),
     strlen(* ppsz) + sizeRequired );
    vsnprintf((* ppsz) + strlen(* ppsz), sizeRequired, pszFormat, args);
}
