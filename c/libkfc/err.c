#include "kfc_err.h"

const char * Err_pszFile__;
int Err_iLine__;

#define ErrMsgBufSize (80 * 2)

static char Err_sz_[ErrMsgBufSize] = "";
static char * Err_psz_ = (void *) 0;

#include <stdarg.h>
#include <stdio.h>

void
clearErrMsg () {
    Err_psz_ = (void *) 0;
}

const char *
getErrMsg () {
    return (Err_psz_);
}

int
KFC_die (
  const char * pszFormat,
  ... ) {
  va_list args;
    va_start(args, pszFormat);
    fprintf(stderr, "%s(%d): ", Err_pszFile__, Err_iLine__);
    vfprintf(stderr, pszFormat, args);
    fprintf(stderr, "\n");
    va_end(args);
    exit (1);
    return (0xDEAD);
}
    
int
editErrMsg (
  const char * pszFormat,
  ... ) {
  int n;
  va_list args;
    Err_psz_ = Err_sz_;
    va_start(args, pszFormat);
    n = snprintf(Err_psz_, ErrMsgBufSize, "%s(%d): ",
     Err_pszFile__, Err_iLine__);
    n = vsnprintf(Err_psz_ + n, ErrMsgBufSize - n,
     pszFormat, args);
    va_end(args);
    return (n);
}

#include <stdio.h> /* fprintf() */
#include <stdlib.h> /* abort() */

int
messageFatal (
  const char * psz ) {
    fprintf(stderr, "Fatal: %s\n", psz);
    abort();
    /* this does not have meaning. some situations requires return values */
    return (12345);
}

int
messageError (
  const char * psz ) {
    fprintf(stderr, "Error: %s\n", psz);
    abort();
    /* this does not have meaning. some situations requires return values */
    return (12345);
}

