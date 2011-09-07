#include "tclass.h"

template <class T> Hoge<T>::Hoge(T aArg, T bArg) {
    a = aArg;
    b = bArg;
}

template <class T> T Hoge<T>::get(void) {
    return (a + b);
}

template class Hoge<int>;
