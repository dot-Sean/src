#include <stdio.h>

#define DebugPrintf(fmt, args...) printf("%s: " fmt, __FUNCTION__, ## args)

int
main () {
  DebugPrintf("d: %s\n", "hoge");
  return (0);
}


