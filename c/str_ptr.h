#ifndef STR_PTR_H
#define STR_PTR_H

char * Str_new(const char * pszConst);
void Str_free(char * * ppsz);
void Str_appendf(char * * ppsz, const char * pszFormat, ...);

#endif /* STR_PTR_H */
