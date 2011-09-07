#include "str_cpp.h"

#include <stdio.h>

int main (int argc, char * * argv) {
  char * psz;
  int i;
  char * pszDelim;
    psz = Str_new("argv: ");
    pszDelim = "";
    for (i = 0; i < argc; i ++) {
        Str_appendf99(& psz, "%s%s", pszDelim, argv[i]);
        pszDelim = ", ";
    }
    printf("%s\n", psz);
    Str_free(& psz);
    return (0);
}
