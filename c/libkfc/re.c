#include "kfc_re.h"

#include "kfc.h"

#if 0
#define MemDebug
#endif
#include "kfc_mem.h"

/* regex requires ... */
#include <stdlib.h>
#include <regex.h>

#include <string.h>

#define RE_MaxNumSubStr 10

struct REImp {
    regex_t regex;
    regmatch_t aregmatch[RE_MaxNumSubStr];
    Str astr[RE_MaxNumSubStr];
    char * pszPrevTarget;
    char * pszTmp;
};

#include <stdio.h>

static RE
RE_assign (
  RE self,
  const char * pszRE ) {
    if (self->pszPrevTarget) {
        Free((void *) self->pszPrevTarget);
        self->pszPrevTarget = (void *) 0;
    }
    if (self->pszTmp) {
        Free((void *) self->pszTmp);
        self->pszTmp = (void *) 0;
    }
    regcomp(& self->regex, pszRE, REG_EXTENDED);
    {
      int i;
        for (i = 0; i < RE_MaxNumSubStr; i ++) {
            self->astr[i] = Str_new("");
        }
    }
    return (self);
}

RE
RE_new (
  const char * pszRE ) {
  RE self;
    self = New(struct REImp, 1);
    RE_assign(self, pszRE);
    return (self);
}

void
RE_delete(
  RE self ) {
    regfree(& self->regex);
    if (self->pszPrevTarget) {
        Free((void *) self->pszPrevTarget);
    }
    if (self->pszTmp) {
        Free((void *) self->pszTmp);
    }
    {
      int i;
        for (i = 0; i < RE_MaxNumSubStr; i ++) {
            Str_delete(self->astr[i]);
        }
    }
    Free((void *) self);
}

Result
RE_match_ ( 
  const char * pszRE,
  const char * psz ) {
  RE re;
  Result rReturn;
    re = RE_new(pszRE);
    rReturn = RE_match(re, psz);
    RE_delete(re);
    return (rReturn);
}

Result
RE_match (
  RE self,
  const char * pszTarget ) {
  Result nRetCode = Failure;
    if (self->pszPrevTarget) {
        Free((void *) self->pszPrevTarget);
        self->pszPrevTarget = (void *) 0;
    }
    if (regexec(& self->regex, pszTarget, RE_MaxNumSubStr, self->aregmatch,
     0 ) != REG_NOMATCH ) {
        self->pszPrevTarget = StrDup(pszTarget);
        nRetCode = Success;
    }
    return (nRetCode);
}

const char *
RE_getSubStr (
  RE self,
  int i ) {
    if (i < 0 || RE_MaxNumSubStr <= i || self->aregmatch[i].rm_so < 0) {
        return ((void *) 0);
    }
    if (self->pszTmp) {
        Free((void *) self->pszTmp);
        self->pszTmp = (void *) 0;
    }
    self->pszTmp = StrDup(self->pszPrevTarget);
    self->pszTmp[self->aregmatch[i].rm_eo] = '\0';
    Str_assign(self->astr[i], self->pszTmp + self->aregmatch[i].rm_so);
    return (Str_get(self->astr[i]));
}

const char *
RE_getPrecStr (
  RE self ) {
    if (self->aregmatch[0].rm_so < 0) {
        return ((void *) 0);
    }
    if (self->pszTmp) {
        Free((void *) self->pszTmp);
        self->pszTmp = (void *) 0;
    }
    self->pszTmp = StrDup(self->pszPrevTarget);
    self->pszTmp[self->aregmatch[0].rm_so] = '\0';
    return (self->pszTmp);
}

const char *
RE_getPostStr (
  RE self ) {
    if (self->aregmatch[0].rm_so < 0) {
        return ((void *) 0);
    }
    if (self->pszTmp) {
        Free((void *) self->pszTmp);
        self->pszTmp = (void *) 0;
    }
    self->pszTmp = StrDup(self->pszPrevTarget);
    return (self->pszTmp + self->aregmatch[0].rm_eo);
}

const char *
RE_getMatched (
  RE self ) {
    return (RE_getSubStr(self, 0));
}

RE
RE_vnewf (
  const char * pszFmt,
  va_list args ) {
  RE self;
  Str str;
    str = Str_new("");
    Str_vappendf(str, pszFmt, args);
    self = RE_new(Str_get(str));
    Str_delete(str);
    return (self);
}

RE
RE_newf (
  const char * pszFmt,
  ... ) {
  RE self;
  va_list args;
    va_start(args, pszFmt);
    self = RE_vnewf(pszFmt, args);
    va_end(args);
    return (self);
}
