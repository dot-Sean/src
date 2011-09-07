#include <stdio.h>

#include <unistd.h>
#include <linux/unistd.h>
_syscall3(int, syslog, int, type, char *, bufp, int, len);

#include <string.h>

int
main (
  int argc,
  char * * argv ) {
  int n;
  char szAll[4096 + 1];
  char * pszAll;
  const char * psz;
    if ((n = syslog(3, szAll, sizeof (szAll)))) {
        szAll[n] = '\0';
    }
    pszAll = szAll;
    while ((psz = strtok(pszAll, "\n"))) {
        pszAll = (void *) 0;
        printf("- %s\n", psz);
    }
    return (0);
}
