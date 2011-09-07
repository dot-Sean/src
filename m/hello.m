// http://www.midi.co.jp/

#include <stdio.h>
#include "mystr.h"

int
main(
  int argc,
  char * * argv ) {
  id str;
    str = [ MyStr newStr: "Hello World\n" ];
    printf("d: %s\n", [ str name ]);
    [ str print ];
    return (0);
}
