#ifndef MYSTR_H
#define MYSTR_H

#include "objc/Object.h"

@interface MyStr: Object

{
    char * psz;
}

+ (id) newStr: (const char *) pszArg;

- (void) setStr: (const char *) pszArg;
- (void) print;

@end

#endif /* MYSTR_H */
