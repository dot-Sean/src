#include "mystr.h"

#include <stdlib.h>
#include <string.h>

@implementation MyStr

+ (id) newStr: (const char *) pszArg {
  id me = [ MyStr new ];
    [ me setStr:pszArg ];
    return (me);
}

- (void) setStr: (const char *) pszArg {
    psz = (char *) malloc(strlen(pszArg) + 1);
    strcpy(psz, pszArg);
}

- (void) print {
    printf(psz);
}

@end
