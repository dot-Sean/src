#ifndef CPROG_H
#define CPROG_H

#ifdef SWIG

%{
#include "cprog.h"
%}

/* http://swig.sourceforge.net/Doc1.3/Customization.html */
/* http://swig-jp.dyndns.org/doc1319/Customization.html */
%newobject get_time;

#endif /* SWIG */

const char * get_time ();

#endif /* CPROG_H */
