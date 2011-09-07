#ifndef K_STR_H /* { */
#define K_STR_H

#include <stdarg.h>

struct StrImp;
typedef struct StrImp * Str;

Str Str_new(const char * psz);
Str Str_vnewf(const char * pszFmt, va_list args);
Str Str_newf(const char * pszFmt, ...);

void Str_delete(Str self);

Str Str_assign(Str self, const char * pszArg);
int Str_vassignf(Str self, const char * pszFormat, va_list args);
int Str_assignf(Str self, const char * pszFormat, ...);

Str Str_append(Str self, const char * pszArg);
int Str_vappendf(Str self, const char * pszFormat, va_list args);
int Str_appendf(Str self, const char * pszFormat, ...);

const char * Str_get(Str self);

int Str_length(Str self);
int Str_compare(Str self, const char * psz);

#endif /* } */
