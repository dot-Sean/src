#if 0

http://www.linuxassembly.org/linasm.html

AT&T 文法

%: レジスタのプレフィクス
$: 即値のプレフィクス
(): メモリ参照

intel: segreg:[base+index*scale+disp]
 AT&T: %segreg:disp(base,index,scale)

  scale: デフォ 1

#endif

static char *
mystrcat(
  char * dest,
  const char * src ) {
  int d0;
  int d1;
  int d2;
  int d3;
    __asm__ __volatile__(
      "repne\n\t" // repeat while not equal string operation
      "scasb\n\t" // scan string data in byte unit
      "decl %1\n"
      "1:\tlodsb\n\t"
      "stosb\n\t"
      "testb %%al,%%al\n\t"
      "jne 1b"
      : "=&S" (d0), "=&D" (d1), "=&a" (d2), "=&c" (d3)
      : "0" (src), "1" (dest), "2" (0), "3" (0xffffffff)
      : "memory"
    );
    return (dest);
}

#include <stdio.h>

int
main (
  int argc,
  char * * argv ) {
  char sz[256] = "Hello";
    mystrcat(sz, ", World!");
    printf("d: %s\n", sz);
    __asm__(
      "movl $1, %eax\n\t" // _exit(2)
      "movl $100, %ebx\n\t"
      "int  $0x80\n\t"
    );
    return (0);
}

//static 
//.section .text.lock
//.previous
