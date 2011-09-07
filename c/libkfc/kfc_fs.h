#ifndef KFC_FS_H /* { */
#define KFC_FS_H

#include "kfc.h"

Result isFile(const char * pszName);
Result isRegularFile(const char * pszName);
Result isChrDevFile(const char * pszName);
Result isBlkDevFile(const char * pszName);
Result isDirectory(const char * pszName);

struct DirImp;
typedef struct DirImp * Dir;

Dir Dir_new(const char * psz);
void Dir_delete(Dir self);
const char * Dir_getFirst(Dir self);
const char * Dir_getNext(Dir self);

void pushd(const char * pszPath);
void popd();

#endif /* } */
