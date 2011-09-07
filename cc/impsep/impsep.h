#include <iostream>

// -------------------------------------------------------------------

class ImpSepImp;

class ImpSep {
private:
    ImpSepImp * pimp;
public:
    ImpSep(float, float);
    virtual ~ImpSep();
    friend std::ostream & operator<<(std::ostream &, const ImpSep &);
};

// -------------------------------------------------------------------

class Imp {
private:
    float fReal;
    float fImag;
public:
    Imp(float, float);
    friend std::ostream & operator<<(std::ostream &, const Imp &);
};
