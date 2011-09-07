#include <stdio.h>
#include <unistd.h>

int foo(int x, int y) {
  int r;
    //while (1) {
    //    sleep(1);
    //}
    r = x + y;
    return (r);
}

int main (int argc, char * * argv) {
  int ret;
    ret = foo(2, 3);
    return (0);
}
