#include <ruby.h>

int
main (
  int argc,
  char * * argv ) {
    ruby_init();
    rb_eval_string("print 'Hello World\n'");
    return (0);
}

