#include "kfc_cmd.h"

#include "kfc.h"

#include <stdio.h>

struct CmdImp {
    FILE * pfileInput;
    FILE * pfileOutput;
    char * pszBuf;
    int nBufSize;
};

#include <stdlib.h>

#include <unistd.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static Boolean Cmd_fDryRun_;

void
Cmd_setDryRun (
  Boolean fDryRun ) {
    Cmd_fDryRun_ = fDryRun;
}

Cmd
Cmd_new (
  const char * pszCmd ) {
  Cmd self;
  /* "input" for parent. reversal for child */
  int pipeInput[2];
  int pipeOutput[2];
    #define ForRead 0
    #define ForWrite 1
    self = New(struct CmdImp, 1);
    pipe(pipeInput);
    pipe(pipeOutput);
    if (fork() == 0) {
        close(pipeInput[ForRead]);
        close(pipeOutput[ForWrite]);
        close(0);
        close(1);
        close(2);
        dup2(pipeOutput[ForRead], 0);
        dup2(pipeInput[ForWrite], 1);
        dup2(open("/dev/null", O_RDWR), 2);
        Log_printf_("Executing \"%s\"\n", pszCmd);
        execlp("/bin/sh", "/bin/sh", "-c", pszCmd, (void *) 0);
        exit(1);
    }
    self->pfileInput = fdopen(pipeInput[ForRead], "r");
    close(pipeInput[ForWrite]);
    close(pipeOutput[ForRead]);
    self->pfileOutput = fdopen(pipeOutput[ForWrite], "w");
    self->nBufSize = 80 * 2;
    self->pszBuf = (char *) Malloc(sizeof (char) * self->nBufSize);
    strcpy(self->pszBuf, "Dead Beaf");
    return (self);
}

static void
Cmd_closeWrite (
  Cmd self ) {
    if (self->pfileOutput) {
        fclose(self->pfileOutput);
        self->pfileOutput = (void *) 0;
    }
}

void
Cmd_delete (
  Cmd self ) {
    Cmd_closeWrite(self);
    (void) (self->pfileInput && fclose(self->pfileInput));
    (void) (self->pfileOutput && fclose(self->pfileOutput));
    /* should I close file descriptors? */
    Free((void *) self->pszBuf);
    Free((void *) self);
}

#include <string.h>

const char *
Cmd_read (
  Cmd self ) {
  char * psz;
    if (self->pfileOutput) {
        Cmd_closeWrite(self);
    }
    psz = fgets(self->pszBuf, self->nBufSize, self->pfileInput);
    if (psz && strlen(self->pszBuf) >= 1 &&
     self->pszBuf[strlen(self->pszBuf) - 1] == '\n') {
        self->pszBuf[strlen(self->pszBuf) - 1] = '\0';
    }
    return (psz);
}

void
Cmd_write (
  Cmd self,
  const char * psz ) {
    fputs(psz, self->pfileOutput);
}

int
Cmd_vwritef (
  Cmd self,
  const char * pszFmt,
  va_list args ) {
  int n;
    if (! self->pfileOutput) {
        return (0);
    }
    n = vfprintf(self->pfileOutput, pszFmt, args);
    fflush(self->pfileOutput);
    return (n);
}

int
Cmd_writef (
  Cmd self,
  const char * pszFmt,
  ... ) {
  int n;
  va_list args;
    va_start(args, pszFmt);
    n = Cmd_vwritef(self, pszFmt, args);
    va_end(args);
    return (n);
}

Cmd
Cmd_vnewf (
  const char * pszFmt,
  va_list args ) {
  Cmd self;
  Str str;
    str = Str_new("");
    Str_vappendf(str, pszFmt, args);
    self = Cmd_new(Str_get(str));
    Str_delete(str);
    return (self);
}

Cmd
Cmd_newf (
  const char * pszFmt,
  ... ) {
  Cmd self;
  va_list args;
    va_start(args, pszFmt);
    self = Cmd_vnewf(pszFmt, args);
    va_end(args);
    return (self);
}

int
vsystemf (
  const char * pszFmt,
  va_list args ) {
  Str str;
  int iRet;
    str = Str_new("");
    Str_vappendf(str, pszFmt, args);
    if (Cmd_fDryRun_) {
        Log_printf_("Dry-running: system(\"%s\")\n", Str_get(str));
        iRet = 0;
    } else {
        iRet = system(Str_get(str));
    }
    Str_delete(str);
    return (iRet);
}

int
systemf (
  const char * pszFmt,
  ... ) {
  int iRet;
  va_list args;
    va_start(args, pszFmt);
    iRet = vsystemf(pszFmt, args);
    va_end(args);
    return (iRet);
}


