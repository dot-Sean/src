#include <iostream>
#include <typeinfo>

class Base {
public:
    virtual ~Base() {}
};
class Sub1: public Base {
public:
    virtual void sub1_func () { std::cout << "sub1_func()" << std::endl; }
};
class Sub1_1: public Sub1 {
public:
    virtual void sub1_func () { std::cout << "sub1_1_func()" << std::endl; }
};
class Sub2: public Base {};

int main () {
    Base base_obj;
    Sub1 sub1_obj;
    Sub1_1 sub1_1_obj;
    Sub2 sub2_obj;

    // Enable one of followings
//    Base * p = & base_obj;
//    Base * p = & sub1_obj;
    Base * p = & sub1_1_obj;
//    Base * p = & sub2_obj;

    const std::type_info & info = typeid (* p); // get RTTI
    std::cout << "type name: " << info.name() << std::endl;
    //std::cout << "d1: " << info.raw_name() << std::endl;
    if (info == typeid (Base)) {
        std::cout << "Base" << std::endl;
    //} else if (info == typeid (Sub1)) {
    } else if ((typeid (Sub1)).before(info)) {
        std::cout << "Sub1" << std::endl;
        Sub1 * psub1 = dynamic_cast<Sub1 *>(p);
        psub1->sub1_func();
    } else if (info == typeid (Sub2)) {
        std::cout << "Sub2" << std::endl;
    }
    return 0;
}
