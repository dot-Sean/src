#ifndef KFC_ERR_H
#define KFC_ERR_H

extern const char * Err_pszFile__;
extern int Err_iLine__;

#include <stdarg.h>

const char * getErrMsg();

void clearErrMsg ();
int editErrMsg(const char * pszFormat, ...);

/*
 * the do - while loop seemed to be meaningless is useful when used
 * with "if" without braces (though I do not use)
 */
#define EditErrMsg(l) ( \
  Err_pszFile__ = __FILE__, \
  Err_iLine__ = __LINE__, \
  editErrMsg l )

int KFC_die(const char * pszFormat, ...);

#define Die(l) ( \
  Err_pszFile__ = __FILE__, \
  Err_iLine__ = __LINE__, \
  KFC_die l )

int messageFatal(const char * psz);
int messageError(const char * psz);

#endif
