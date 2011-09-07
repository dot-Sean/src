#include "kfc_cfg.h"

#if 1
#define MemDebug
#endif
#include "kfc_mem.h"

struct CfgImp {
    Dic dic;    
};

Cfg
Cfg_new () {
  Cfg self;
    self = New(struct CfgImp, 1);
    self->dic = Dic_new();
    return (self);
}

void
Cfg_delete (
  Cfg self ) {
  const char * pszKey;
    for (
     pszKey = Dic_getFirstKey(self->dic);
     pszKey;
     pszKey = Dic_getNextKey(self->dic) ) {
        Delete((const char *) Dic_refer(self->dic, pszKey));
    }
    Dic_delete(self->dic);
    Delete(self);
}

#include <stdio.h>

Result
Cfg_load (
  Cfg self,
  const char * pszFile ) {
  FILE * pfile = (void *) 0;
  Str str = Str_new("");
  RE reCmt = RE_new("^#");
  RE re = RE_new("^([^:]+): *(.+) *$");
  Result r = Failure;
  char sz[100];
    pfile = fopen(pszFile, "r");
    if (! pfile) {
        goto Cfg_load_end;
    }
    Str_assign(str, "");
    while (fgets(sz, sizeof (sz), pfile)) {
        if (
         (strlen(sz) == ((sizeof (sz)) - 1)) &&
         (sz[strlen(sz) - 1] != '\n') ) {
            Str_append(str, sz);
            continue;
        }
        if (sz[strlen(sz) - 1] == '\n') {
            sz[strlen(sz) - 1] = '\0';
        }
        Str_append(str, sz);
        if (RE_match(reCmt, Str_get(str))) {
            ;
        } else if (RE_match(re, Str_get(str))) {
            Dic_add(self->dic, RE_getSubStr(re, 1),
             StrDup(RE_getSubStr(re, 2)) );
        }
        Str_assign(str, "");
    }
    r = Success;
Cfg_load_end:
    if (pfile) {
        fclose(pfile);
    }
    Str_delete(str);
    RE_delete(re);
    RE_delete(reCmt);
    return (r);
}

const char *
Cfg_get (
  Cfg self,
  const char * pszKey ) {
    return (Dic_refer(self->dic, pszKey));
}

Result
Cfg_save (
  Cfg self,
  const char * pszFile ) {
  Result r = Failure;
  const char * pszKey = (void *) 0;
  FILE * pfile = (void *) 0;
    pfile = fopen(pszFile, "w");
    if (! pfile) {
        goto Cfg_save_end;
    }
    for (
     pszKey = Dic_getFirstKey(self->dic);
     pszKey;
     pszKey = Dic_getNextKey(self->dic) ) {
        fprintf(pfile, "%s: %s\n", pszKey,
         (const char *) Dic_refer(self->dic, pszKey));
    }
    r = Success;
Cfg_save_end:
    if (pfile) {
        fclose(pfile);
    }
    return (r);
}

void
Cfg_set (
  Cfg self,
  const char * pszKey,
  const char * pszValue ) {
    Dic_add(self->dic, pszKey, StrDup(pszValue));
}

