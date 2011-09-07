#include "impsep.h"

// -------------------------------------------------------------------

#undef i
#define i(member) pimp->member

class ImpSepImp {
public:
    ImpSepImp(float, float);
    float fReal;
    float fImag;
};

ImpSepImp::ImpSepImp (
  float fRealArg,
  float fImagArg ) : fReal(fRealArg), fImag(fImagArg) {
    ;
}

ImpSep::ImpSep (
  float fRealArg,
  float fImagArg ) : pimp(new struct ImpSepImp(fRealArg, fImagArg)) {
    ;
}

ImpSep::~ImpSep () {
    delete this->pimp;
}

std::ostream &
operator<< (std::ostream & out, const ImpSep & impsep) {
    out << impsep.i(fReal) << " + " << impsep.i(fImag) << " i";
    return (out);
}

// -------------------------------------------------------------------

#undef i
#define i(member) member

Imp::Imp (
  float fRealArg,
  float fImagArg ) : i(fReal)(fRealArg), i(fImag)(fImagArg) {
    ;
}

std::ostream &
operator<< (std::ostream & out, const Imp & imp) {
    out << imp.i(fReal) << " + " << imp.i(fImag) << " i";
    return (out);
}

// -------------------------------------------------------------------

#include <iostream>

int
main (
  int argc,
  char * * argv ) {
  ImpSep impsep(7.3, 9.8);
  Imp imp(2.3, 3.5);
    std::cout << impsep << std::endl;
    std::cout << imp << std::endl;
    return (0);
}
