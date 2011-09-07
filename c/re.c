#include <stdio.h>

/* malloc() */
#include <stdlib.h>
/* regcomp(), regexec(), ... */
#include <regex.h>
/* strncpy() */
#include <string.h>

#define SubStrMax 10

/* mtrace() */
#include <mcheck.h>

int
main (
  int argc,
  char * * argv ) {
  int rc = -1;
  regex_t regex;
  int rcRegcomp = -1;
  char * psz = NULL;
    mtrace();
    do {
      char szTgt[] = "xyz hoge000, fuga111 999";
      char szRe[] = "(hoge[0-9]+).*(fuga[0-9]+)";
      regmatch_t aregmatch[SubStrMax];
      int i;
        if ((rcRegcomp = regcomp(& regex, szRe, REG_EXTENDED)) != 0) {
            break;
        }
        if (regexec(& regex, szTgt, SubStrMax, aregmatch, 0) ==
         REG_NOMATCH ) {
            break;
        }
        for (i = 0; i < SubStrMax && aregmatch[i].rm_so >= 0; ++ i) {
          int iStart = aregmatch[i].rm_so;
          int iEnd = aregmatch[i].rm_eo;
          int nLength = iEnd - iStart;
            if (! (psz =
             (char *) malloc((sizeof (char)) * (nLength + 1)) )) {
                goto exception;
            }
            strncpy(psz, szTgt + iStart, nLength);
            psz[nLength] = '\0';
            printf("%d: %s\n", i, psz);
            free((void *) psz);
            psz = NULL;
        }
        rc = 0;
    } while (0);
exception:
    if (psz) { free(psz); }
    if (rcRegcomp == 0) { regfree(& regex); }
    muntrace();
    return (rc);
}

/* -------------------------------------------------------------------
$ ./a.out 
0: hoge000, fuga111
1: hoge000
2: fuga111
------------------------------------------------------------------- */
