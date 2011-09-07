#include <iostream>
#include <boost/thread.hpp>
//using namespace std;
 
const int kCount =  100000000;
const int kInterval = 1000000;
 
void PrintHello() {
    for(int i = 0; i != kCount; ++i)
        if (!(i % kInterval)) std::cout << "Hello ";
}
 
void PrintWorld() {
    for(int i = 0; i != kCount; ++i)
        if (!(i % kInterval)) std::cout << "World! ";
}
 
int main() {
    boost::thread thread_hello(PrintHello);
    boost::thread thread_world(PrintWorld);
    thread_hello.join();
    thread_world.join();
    return 0;
}
