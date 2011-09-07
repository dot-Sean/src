#ifndef SPLIT_H
#define SPLIT_H

int splitStrEx (const char * pszArg, int nMaxTok, char * pszBuf, const char * * ppszTokens, int (* isdelim) (int));
int splitStr (const char * pszArg, int nMaxTok, char * pszBuf, const char * * ppszTokens);

#endif /* SPLIT_H */
