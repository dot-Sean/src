#ifndef _H_LOG
#define _H_LOG

#include <stdarg.h>

struct LogImp;
typedef struct LogImp * Log;

/* constructor. pszOwner can be null */
Log Log_new(const char * pszFilename);
/* destructor */
void Log_delete(Log self);
/* prints owner, messages and newline */
void Log_log(Log self, const char * pszFormat, ...);
/* same as printf() */
int Log_printf(Log self, const char * pszFormat, ...);
int Log_vprintf(Log self, const char * pszFormat, va_list args);

#include "kfc.h"

Result Log_new_(const char * pszFilename);
void Log_delete_();
int Log_printf_(const char * pszFormat, ...);
void Log_log_(const char * pszFormat, ... );

#endif
