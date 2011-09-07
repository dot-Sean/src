#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define BufSize 1024
#define MaxNumArgs 64
#define HostNameBufSize 64

int
minsh_main (
  int argc,
  char * argv[] ) {
  char szBuf[BufSize];
  char * apszBuf[MaxNumArgs];
  FILE * pfileCmdIn;
  FILE * pfileStdOut;
  FILE * pfileStdErr;
  int sCommandMode;
  char szHostName[HostNameBufSize];
    sCommandMode = 0;
    /* Interactive */
    if (argc == 1) {
        pfileCmdIn = stdin;
        pfileStdOut = stdout;
        pfileStdErr = stderr;
    /* Run command under shell */
    } else if (argc == 3 && strcmp(argv[1], "-c") == 0) {
        sCommandMode = 1;
        pfileCmdIn = NULL;
        pfileStdOut = stdout;
        pfileStdErr = stderr;
    /* Run shell script */
    } else if (argv[1]) {
        pfileCmdIn = fopen(argv[1], "rw");
        if (! pfileCmdIn) {
            return (1);
        }
        pfileStdOut = stdout;
        pfileStdErr = stderr;
    } else {
        return (1);
    }
    gethostname(szHostName, HostNameBufSize);
    while (1) {
      char * psz;
      char * * ppsz;
      int n;
        if (pfileCmdIn == stdin) {
            fprintf(pfileStdErr, "[ %s:%s ]\n$ ", szHostName, 
             getcwd(szBuf, BufSize) );
        }
        if (sCommandMode) {
            strcpy(szBuf, argv[2]);
        } else if (fgets(szBuf, BufSize, pfileCmdIn) == NULL) {
            if (pfileCmdIn == stdin) {
                fprintf(pfileStdErr, "\n");
            }
            return (0);
        }
        psz = szBuf;
        ppsz = apszBuf;
        n = 0;
        while ((* psz) != '\0') {
            while ((* psz) == ' ' || (* psz) == '\t' || (* psz) == '\n') {
                (* psz) = '\0';
                psz ++;
            }
            if ((* psz) == '\0') {
                break;
            }
            if ((* psz) != '#') {
                (* ppsz) = psz;
                ppsz ++;
                n ++;
            }
            while ((* psz) != ' ' && (* psz) != '\t' && (* psz) != '\n' &&
             (* psz) != '\0' ) {
                psz ++;
            }
        }
        (* ppsz) = NULL;
        if (n >= 1) {
            if ((strcmp(apszBuf[0], "cd") == 0) && apszBuf[1] != NULL) {
                chdir(apszBuf[1]);
            } else if (strcmp(apszBuf[0], "exit") == 0) {
                goto end;
            } else {
              int iPID;
              int nStatus;
                iPID = fork();
                if (iPID == 0) {
                    execvp(apszBuf[0], apszBuf);
                    fprintf(pfileStdErr, "%s: %s: command not found\n", 
                     argv[0], apszBuf[0] );
                    return (1);
                }
                while (wait(& nStatus) != iPID) {
                    ;
                }
            }
        }
        if (sCommandMode) {
            goto end;
        }
    }
end:
    if (pfileCmdIn && pfileCmdIn != stdin) {
        fclose(pfileCmdIn);
    }
    return (0);
}
