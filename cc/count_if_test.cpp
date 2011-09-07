#include <iostream>
#include <functional>
#include <algorithm>

using namespace std;

int
main (
  int argc,
  char * * argv ) {
  int an[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  size_t len = sizeof (an) / sizeof (int);
    cout <<
     count_if(& (an[0]), & (an[len]), bind2nd(less_equal<int>(), 5)) <<
     endl;
    return (0);
}
