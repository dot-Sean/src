#include "kfc_log.h"

#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

struct LogImp {
    FILE * pfile;
};

Log
Log_new (
  const char * pszFilename ) {
  Log self = New(struct LogImp, 1);
    if (pszFilename) {
        self->pfile = fopen(pszFilename, "w");
    } else {
        self->pfile = stderr;
    }
    Log_log(self, "Opened log");
    return (self);
}

void
Log_delete (
  Log self ) {
    Log_log(self, "Closing log");
    if (self->pfile && self->pfile != stderr) {
        fclose(self->pfile);
    }
    Delete(self);
}

int
Log_vprintf(
  Log self,
  const char * pszFormat,
  va_list args ) {
  int n;
    if (! self->pfile) {
        return (0);
    }
    n = vfprintf(self->pfile, pszFormat, args);
    fflush(self->pfile);
    return (n);
}

int
Log_printf(
  Log self,
  const char * pszFormat,
  ... ) {
  int n;
  va_list args;
    va_start(args, pszFormat);
    fprintf(self->pfile, "- ");
    n = Log_vprintf(self, pszFormat, args);
    va_end(args);
    return (n);
}

static void
Log_logSub (
  Log self,
  const char * pszFormat,
  va_list args ) {
    if (! self->pfile) {
        return;
    }
    fprintf(self->pfile, "- ");
    (void) vfprintf(self->pfile, pszFormat, args);
    fprintf(self->pfile, "\n");
    fflush(self->pfile);
}

void
Log_log (
  Log self,
  const char * pszFormat,
  ... ) {
  va_list args;
    va_start(args, pszFormat);
    Log_logSub(self, pszFormat, args);
    va_end(args);
}

static Log logDefault_ = (void *) 0;

Result
Log_new_ (
  const char * pszFilename ) {
    return ((logDefault_ = Log_new(pszFilename))? Success: Failure);
}

void
Log_delete_ () {
    if (! logDefault_) {
        return;
    }
    Log_delete(logDefault_);
    logDefault_ = (void *) 0;
}

void
Log_log_ (
  const char * pszFormat,
  ... ) {
  va_list args;
    if (! logDefault_) {
        return;
    }
    va_start(args, pszFormat);
    Log_logSub(logDefault_, pszFormat, args);
    va_end(args);
}

int
Log_printf_ (
  const char * pszFormat,
  ... ) {
  va_list args;
  int n;
    if (! logDefault_) {
        return (-1);
    }
    va_start(args, pszFormat);
    n = Log_vprintf(logDefault_, pszFormat, args);
    va_end(args);
    return (n);
}
