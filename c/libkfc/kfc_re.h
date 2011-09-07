#ifndef KFC_RE_H /* { */
#define KFC_RE_H

#include "kfc.h"

#include <stdarg.h>

struct REImp;
typedef struct REImp * RE;

RE RE_new(const char * pszRE);
RE RE_vnewf(const char * pszFmt, va_list args);
RE RE_newf(const char * pszFmt, ...);

void RE_delete(RE self);

Result RE_match(RE self, const char * pszTarget);
const char * RE_getMatched(RE self);
const char * RE_getPrecStr(RE self);
const char * RE_getPostStr(RE self);
const char * RE_getSubStr(RE self, int i);

Result RE_match_(const char * pszRE, const char * psz);

#endif /* } */
