/* -*- coding: utf-8 */
/*
 *  コードを読んでいて、「ここで止めたい」と思っても、起動経路が込み入っ
 *  ていて gdb を仕掛けづらいことも多い。そこで、gdb が attach をかけられ
 *  ることを利用。
 */
#include <stdio.h>
#include <stdlib.h>

// -------------------------------------------------------------------

#include <sys/types.h> // for getpid()
#include <unistd.h> // for sleep(), getpid()

static void settrace () {
  int i; int loop = 1;
    fprintf(stderr,
     "Sleeping. Execute the following in 60 seconds.\n"
     "--\ngdb --pid=%d\nup\nup\nset loop = 0\n"
     "finish\n--\n", (int) getpid() );
    for (i = 0; i < 60 && loop; i ++) { sleep(1); }
}

// -------------------------------------------------------------------

static void
foo () {
  int nPositive = -1;
    if (nPositive < 0) {
        fprintf(stderr, "Some error occured.\n");
//{ int i; int loop = 1; fprintf(stderr, "Sleeping. Execute the following in 60 seconds.\n--\ngdb --pid=%d\nup\nup\nset loop = 0\nnext\nnext\n--\n", (int) getpid(),  ); for (i = 0; i < 60 && loop; i ++) { sleep(1); } }
        settrace();
        fprintf(stderr, "Exiting.\n");
        exit(0);
    }
}

int
main (
  int argc,
  char * * argv ) {
    foo();
    return (0);
}
