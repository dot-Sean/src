#include "ccprog.h"

#include <string.h>

MyStr::MyStr (const char * pszArg) {
    psz = new char[strlen(pszArg) + 1];
    strcpy(psz, pszArg);
}

MyStr::~MyStr (void) {
    delete [] psz;
}

const char * MyStr::get (void) {
    return psz;
}
