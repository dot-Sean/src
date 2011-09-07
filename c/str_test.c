#include "str.h"

#include <stdio.h>

int main (int argc, char * * argv) {
  Str str;
  int i;
  char * pszDelim;
    str = Str_new("argv: ");
    pszDelim = "";
    for (i = 0; i < argc; i ++) {
        Str_appendf(str, "%s%s", pszDelim, argv[i]);
        pszDelim = ", ";
    }
    printf("%s\n", Str_get(str));
    Str_free(str);
    return (0);
}
