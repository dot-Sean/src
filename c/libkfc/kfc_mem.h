/*
 * this file can be included repeatedly
 *
 * the following macros decide the behavior
 *   MemDebug: debug mode
 *   MemFast: fast mode without checks
 *   (none of above): safe mode with checks
 */

#ifndef KFC_MEM_H /* { */
#define KFC_MEM_H
#include <stdlib.h>

void * mallocSafe(size_t size);
char * strdupSafe(const char * psz);
void * reallocSafe(void * pv, size_t size);
void freeSafe(void * pv);
#endif /* } */

#undef Malloc
#undef StrDup
#undef Realloc
#undef Free

#if defined(MemDebug) /* { */
  #ifndef KFC_MEM_H_DEBUG /* { */
  #define KFC_MEM_H_DEBUG 
    void * mallocDebug(size_t size);
    char * strdupDebug(const char * psz);
    void * reallocDebug(void * pv, size_t size);
    void freeDebug(void * pv);
  #endif /* } */
  #define Malloc(size) mallocDebug(size)
  #define StrDup(str) strdupDebug(str)
  #define Realloc(ptr, size) reallocDebug(ptr, size)
  #define Free(ptr) freeDebug(ptr)
#elif defined(MemFast) /* } { */
  #define Malloc(size) malloc(size)
  #define StrDup(str) strdup(str)
  #define Realloc(ptr, size) realloc(ptr, size)
  #define Free(ptr) free(ptr)
#else /* } { */
  #define Malloc(size) mallocSafe(size)
  #define StrDup(str) strdupSafe(str)
  #define Realloc(ptr, size) reallocSafe(ptr, size)
  #define Free(ptr) freeSafe(ptr)
#endif  /* } */

#undef New
#undef Renew
#undef Delete

#define New(type, num) \
  ((type *) Malloc((sizeof (type)) * (num)))
#define Renew(type, num, old) \
  ((type *) Realloc((void *) (old), (sizeof (type)) * (num)))
#define Delete(ptr) \
  Free((void *) (ptr))

