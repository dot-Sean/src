#ifndef STR_H
#define STR_H

#include <stdarg.h>

struct StrImp;
typedef struct StrImp * Str;

Str Str_new(const char * psz);
void Str_free(Str self);
void Str_appendf(Str self, const char * pszFormat, ...);
const char * Str_get(Str self);

#endif /* STR_H */
