#include <stdio.h>

/* ---------------------------------------------------------------- */

#include <stdlib.h>
#include <string.h>

#define strnew(pszArg) ( \
    { \
      char * strnew_psz; \
        strnew_psz = \
         (char *) malloc((sizeof (char)) * (strlen(pszArg) + 1)); \
        strcpy(strnew_psz, pszArg); \
        strnew_psz; \
    } \
)

#define strfree(pszSelf) free((void *) pszSelf)

#define strnappend(pszSelf, pszArg, nChar) ( \
    { \
      char * strappend_psz; \
        strappend_psz = (char *) malloc((sizeof (char)) * \
         (strlen(pszSelf) + strlen(pszArg) + 1) ); \
        strcpy(strappend_psz, pszSelf); \
        strncat(strappend_psz, pszArg, nChar); \
        strfree(pszSelf); \
        pszSelf = strappend_psz; \
        strappend_psz; \
    } \
)

#define strappend(pszSelf, pszArg) \
    strnappend(pszSelf, pszArg, strlen(pszArg))

/* ---------------------------------------------------------------- */

char *
makeCmdLine (char * * argv) {
  char * pszBuf = strnew("");
    for (; * argv; argv ++) {
      char * psz = (void *) 0;
      const char * pszArg = * argv;
      int nLen = strlen(pszArg);
        if (nLen != 0 && ! (psz = strpbrk(pszArg, " \t\n\r\""))) {
            strappend(pszBuf, pszArg);
        } else {
            strappend(pszBuf, "\"");
            for (; psz; pszArg = psz, psz = strchr(psz, '"')) {
                psz ++;
                strnappend(pszBuf, pszArg, psz - pszArg);
                if (psz[-1] == '"') {
                    strappend(pszBuf, "\"");
                }
            }
            if (* pszArg) {
                strappend(pszBuf, pszArg);
            }
            strappend(pszBuf, "\"");
        }
        strappend(pszBuf, " ");
    }
    return (pszBuf);
}

static int fForkDebug = 0;
static int fNewWindow = 1;

#include <windows.h>

int
main (
  int argc,
  char * * argv ) {
  char * pszCmdLine;
  DWORD dwFlags;
  STARTUPINFO si;
  PROCESS_INFORMATION pi;
  BOOL fRet;
    pszCmdLine = makeCmdLine(argv + 1);
    printf("d0: %s\n", pszCmdLine);
    dwFlags = (fForkDebug) ? 0 : DEBUG_ONLY_THIS_PROCESS;
    //dwFlags |= CREATE_DEFAULT_ERROR_MODE | DEBUG_PROCESS;
    dwFlags |= ((fNewWindow) ? \
     CREATE_NEW_CONSOLE | CREATE_NEW_PROCESS_GROUP : 0 );
	memset(& si, 0, sizeof (si));
	si.cb = sizeof (si);
	si.wShowWindow = SW_SHOWNORMAL;
#if 1
    fRet = CreateProcess(
     (void *) 0, /* Program Name */
     pszCmdLine, /* Command Line */
     (void *) 0, /* Security */
     (void *) 0, /* Thread */
     FALSE,      /* Inherit Handles */
     dwFlags,    /* Start Flags */
     (void *) 0, /* Current Directory */
     (void *) 0,
	 & si, & pi );
#else
	WinExec(pszCmdLine, SW_SHOWNORMAL);
#endif
	printf("d1: %d\n", fRet);
	while (1) {
		;
	}
	return (0);
}

