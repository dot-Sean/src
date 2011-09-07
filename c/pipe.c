#include <stdio.h>
#include <unistd.h>

int
main (
  int argc,
  char * * argv ) {
  int inputs_for_parent[2];
  int outputs_for_parent[2];
  int input;
  int output;
    if (pipe(inputs_for_parent) != 0 || pipe(outputs_for_parent) != 0) {
        fprintf(stderr, "pipe failed\n");
        return (1);
    }
    // Child process
    if (fork() == 0) {
        input = outputs_for_parent[0];
        output = inputs_for_parent[1];
        close(inputs_for_parent[0]);
        close(outputs_for_parent[1]);
        dup2(input, 0);
        dup2(output, 1);
        dup2(output, 2);
        argv ++;
        execvp(argv[0], argv);
        fprintf(stderr, "exec failed\n");
        return (1);
    // Parent process
    } else {
      FILE * finput;
      FILE * foutput;
      char sz[256];
        input = inputs_for_parent[0];
        output = outputs_for_parent[1];
        close(inputs_for_parent[1]);
        close(outputs_for_parent[0]);
        finput = fdopen(input, "r");
        foutput = fdopen(output, "w");
        while (fgets(sz, sizeof (sz), finput)) {
            printf("p: %s", sz);
        }
    }
    return (0);
}

