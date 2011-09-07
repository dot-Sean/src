/*
 * KFC (Kiichiro's Foundation Classes :-)
 *
 * Copyright: LGPL
 * Author: Kiichiro Kyle NAKA <knaka@turbolinux.co.jp>
 */

#ifndef COMMON_ALL_H /* { */
#define COMMON_ALL_H

#define LineBufSize (80 * 2)
#define FileBufSize (1024)

typedef enum {
    Success = 1,
    Failure = 0,
    Result_NA = -1,
} Result;

typedef enum {
    True = 1,
    False = 0,
    Boolean_NA = -1,
} Boolean;

#define Null ((void *) 0)

typedef long long int Int64;

#include "kfc_log.h"
#include "kfc_re.h"
#include "kfc_str.h"
#include "kfc_mem.h"
#include "kfc_err.h"
#include "kfc_cmd.h"
#include "kfc_fs.h"
//#include "kfc_stk.h"
#include "kfc_vec.h"
#include "kfc_dic.h"
#include "kfc_tree.h"
#include "kfc_gz.h"

#include <locale.h>
#include <libintl.h>
#define _(s) gettext(s)
#define __(s) (s)
#define N_(s) (s)

#define NoLang "LANG= LANGUAGE= LC_ALL= "

#if 0
#include <stdio.h>
#include <stdlib.h>

#define appendf(ppsz, args...) \
do { \
  char * pszBuf = (void *) 0; \
  int nReq = 0; \
  int nAlloc = 32; \
    while (1) { \
        pszBuf = (char *) malloc((sizeof (char)) * nAlloc); \
        nReq = snprintf(pszBuf, nAlloc, args); \
        if (nReq == -1 || nReq + 1 > nAlloc) { \
            if (nReq == -1) { \
                nAlloc *= 2; \
            } else { \
                nAlloc = nReq + 1; \
            } \
            free((void *) pszBuf); \
        } else { \
            break; \
        } \
    } \
    if (* ppsz) { \
        (* ppsz) = (char *) realloc((void *) (* ppsz), \
         (sizeof (char)) * (strlen(* ppsz) + strlen(pszBuf) + 1) ); \
    } else { \
        (* ppsz) = (char *) malloc((sizeof (char)) * \
         (strlen(pszBuf) + 1) ); \
        (* ppsz)[0] = '\0'; \
    } \
    strcat(* ppsz, pszBuf); \
    free((void *) pszBuf); \
} while (0)
#endif

#endif /* } */

