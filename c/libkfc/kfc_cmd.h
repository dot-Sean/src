#ifndef KFC_CMD_H
#define KFC_CMD_H

#include <stdarg.h>

#include "kfc.h"

struct CmdImp;
typedef struct CmdImp * Cmd;

Cmd Cmd_new(const char * pszCmd);
Cmd Cmd_vnewf(const char * pszFmt, va_list args);
Cmd Cmd_newf(const char * pszFmt, ...);

void Cmd_delete(Cmd self);

void Cmd_write(Cmd self, const char * psz);
int Cmd_vwritef(Cmd self, const char * pszFmt, va_list args);
int Cmd_writef(Cmd self, const char * pszFmt, ...);

const char * Cmd_read(Cmd self);

int vsystemf(const char * pszFmt, va_list args);
int systemf(const char * pszFmt, ...);

void cmd_setDryRun(Boolean fDryRun);

#endif
