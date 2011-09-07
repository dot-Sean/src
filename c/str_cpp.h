#ifndef STR_MACROS_DEFINED
#define STR_MACROS_DEFINED

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define Str_new(pszConst) strdup(pszConst)
#define Str_free(ppsz) { free((void *) (* ppsz)); (* ppsz) = (void *) 0; }
#define Str_appendf(ppsz, pszFormat, args...) \
  sprintf(((* (ppsz)) = (char *) realloc((void *) (* (ppsz)), \
   strlen(* (ppsz)) + snprintf((void *) 0, 0, (pszFormat), args) + 1 )) + \
   strlen(* (ppsz)), (pszFormat), args )

#define Str_appendf99(ppsz, pszFormat, ...) \
  sprintf(((* (ppsz)) = (char *) realloc((void *) (* (ppsz)), \
   strlen(* (ppsz)) + snprintf((void *) 0, 0, \
   (pszFormat), __VA_ARGS__) + 1 )) + \
   strlen(* (ppsz)), (pszFormat), __VA_ARGS__ )

#endif /* STR_MACROS_DEFINED */
