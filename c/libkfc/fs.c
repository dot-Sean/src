#include "kfc_fs.h"

#include <stdlib.h>
#include <sys/dir.h>
#include <sys/stat.h>

/* note: lstat() doesn-t follow sym-links */
#define DefineIs(Type, Checker) \
Result \
is ## Type ( \
  const char * pszName ) { \
  struct stat stat1; \
    return ((stat(pszName, & stat1) == 0 && Checker(stat1.st_mode))? \
     True: False); \
}

#define S_ISFILE(m) (! S_ISDIR(m))
#define S_ISDEV(m) (S_ISCHR(m) || S_ISBLK(m))

DefineIs(File, S_ISFILE)
DefineIs(RegularFile, S_ISREG)
DefineIs(ChrDevFile, S_ISCHR)
DefineIs(BlkDevFile, S_ISBLK)
DefineIs(DevFile, S_ISDEV)
DefineIs(Directory, S_ISDIR)

/* ---------------------------------------------------------------- */
/* directory class */

struct DirImp {
    DIR * pdir;
    Str str;
    const char * pszDir;
};

#include <string.h>

static void
collectSlash (
  char * psz ) {
  char * pszSrc;
  char * pszDest;
    /* collect multiple slashes into one */
    for (
     pszSrc = psz, pszDest = psz;
     * pszSrc;
     pszDest ++ ) {
        (* pszDest) = (* (pszSrc ++));
        if ((* pszDest) == '/') {
            while ((* pszSrc) == '/') {
                pszSrc ++;
            }
        }
    }
    /* cut off trailing slash */
    if ((* (pszDest - 1)) == '/') {
        (* (pszDest - 1)) = '\0';
    } else {
        (* pszDest) = '\0';
    }
}

Dir
Dir_new (
  const char * psz ) {
  Dir self = New(struct DirImp, 1);
    self->pdir = opendir(psz);
    if (self->pdir == (void *) 0) {
        Delete(self);
        return ((void *) 0);
    }
    self->str = Str_new("");
    self->pszDir = StrDup(psz);
    collectSlash((char *) self->pszDir);
    return (self);
}

void
Dir_delete (
  Dir self ) {
    closedir(self->pdir);
    Delete(self->pszDir);
    Delete(self->str);
    Delete(self);
}

const char *
Dir_getNext (
  Dir self ) {
  struct direct * pdirect;
    while ((pdirect = readdir(self->pdir))) {
        if (pdirect->d_ino == 0) {
            continue;
        }
        if (
         strcmp(pdirect->d_name, ".") == 0 ||
         strcmp(pdirect->d_name, "..") == 0 ) {
            continue;
        }
        Str_assign(self->str, "");
        Str_appendf(self->str, "%s/%s", self->pszDir, pdirect->d_name);
        return (Str_get(self->str));
    }
    return ((void *) 0);
}

const char *
Dir_getFirst (
  Dir self ) {
    rewinddir(self->pdir);
    return (Dir_getNext(self));
}

static Vec vecPath = (void *) 0;

static void createPathVec() {
    if (! vecPath) {
        vecPath = Vec_new();
    }
}

#include <unistd.h>

void pushd(const char * pszPath) {
  char sz[80];
    createPathVec();
    getcwd(sz, sizeof (sz));
    Vec_add(vecPath, (void *) StrDup(sz));
    chdir(pszPath);
}

void popd() {
  const char * psz;
    createPathVec();
    psz = (const char *) Vec_chop(vecPath);
    chdir(psz);
    Delete(psz);
}
