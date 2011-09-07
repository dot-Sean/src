#ifndef CCPROG_H
#define CCPROG_H

#ifdef SWIG
%{
#include "ccprog.h"
%}
#endif /* SWIG */

class MyStr {
private:
    char * psz;
public:
    MyStr (const char * pszArg);
    virtual ~MyStr ();
    const char * get ();
};

#endif /* CCPROG_H */
