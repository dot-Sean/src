#ifndef TEMPLATE_INHERIT_H
#define TEMPLATE_INHERIT_H

template <typename T>
class Vector {
private:
    void init(int nNumInitElem);
protected:
    int nNumElem;
    T * pt;
public:
    Vector(int nNumInitElem = 0);
    Vector(int nNumInitElem = 0, const T & tInitValue);
    virtual ~Vector();
};

template <typename T>
class GenericString : public Vector<T> {
public:
    GenericString();
    GenericString(const T *);
    virtual ~GenericString();
    const T * get();
};

typedef GenericString<char> String;
typedef GenericString<wchar_t> WString;

#endif // TEMPLATE_INHERIT_H

// -------------------------------------------------------------------

#include <iostream>

template <typename T>
void Vector<T>::init (
  int nNumInitElem ) {
    std::cout << __func__ << ": " << nNumInitElem << std::endl;
    this->nNumElem = nNumInitElem;
    this->pt = new T[this->nNumElem];
}

template <typename T>
Vector<T>::Vector (
  int nNumInitElem ) {
    std::cout << __func__ << std::endl;
    this->init(nNumInitElem);
}

template <typename T>
Vector<T>::Vector (
  int nNumInitElem,
  const T & tInitValue ) {
  int i;
    std::cout << __func__ << std::endl;
    this->init(nNumInitElem);
    for (i = 0; i < this->nNumElem; ++ i) {
        this->pt[i] = tInitValue;
    }
}

template <typename T>
Vector<T>::~Vector () {
    std::cout << __func__ << std::endl;
    delete [] this->pt;
}

// -------------------------------------------------------------------

#include <wchar.h>
#include <string.h>

template <typename T>
GenericString<T>::GenericString () {
    std::cout << __func__ << std::endl;
}

template <typename T>
GenericString<T>::GenericString (
  const T * psz ) :
  Vector<T>(wcslen(psz) + 1) {
    wcscpy(this->pt, psz);
    std::cout << __func__ << std::endl;
}

template <typename T>
GenericString<T>::~GenericString () {
    std::cout << __func__ << std::endl;
}

template <typename T>
const T *
GenericString<T>::get () {
    return (this->pt);
}

// -------------------------------------------------------------------

int
main (
  int argc,
  char * * argv ) {
  //std::auto_ptr< Vector<char> > pvec(new String("Hello"));
  char sz[100];
    WString str(L"Hello");
    std::wcout << str.get() << std::endl;
    wcstombs(sz, str.get(), (sizeof (sz)) - 1);
    sz[sizeof (sz)] = '\0';
    std::cout << sz << std::endl;
    return (0);
}
