#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/select.h>
#include <signal.h>

int
childJob () {
  int i;
    for (i = 0; i < 10; i ++) {
        printf("child: %d\n", i);
        fflush(stdout);
        sleep(1);
    }
    printf("child: Done\n");
    return (0);
}

#define Sentinel "5"

int
main (
  int argc,
  char * * argv ) {
  int iProcess;
  int aiInputsForParent[2];
  int aiOutputsForParent[2];
  int iInput;
  int iOutput;
    if (pipe(aiInputsForParent) != 0 || pipe(aiOutputsForParent) != 0) {
        fprintf(stderr, "pipe failed\n");
        return (1);
    }
    if ((iProcess = fork()) == 0) {
        iInput = aiOutputsForParent[0];
        iOutput = aiInputsForParent[1];
        close(aiInputsForParent[0]);
        close(aiOutputsForParent[1]);
        dup2(iInput, 0);
        dup2(iOutput, 1);
        dup2(iOutput, 2);
        return (childJob());
    } else {
      FILE * pfileInput;
      FILE * pfileOutput;
      char sz[256];
      int nStatus;
      fd_set fdset;
      struct timeval tv;
        iInput = aiInputsForParent[0];
        iOutput = aiOutputsForParent[1];
        close(aiInputsForParent[1]);
        close(aiOutputsForParent[0]);
        pfileInput = fdopen(iInput, "r");
        pfileOutput = fdopen(iOutput, "w");
        printf("parent: Waiting for " Sentinel "\n");
        tv.tv_sec = 0;
        tv.tv_usec = 0;
        while (1) {
            FD_ZERO(& fdset);
            FD_SET(iInput, & fdset);
            if (select(iInput + 1, & fdset, (void *) 0, (void *) 0, & tv)) {
                fgets(sz, sizeof (sz), pfileInput);
                printf("parent: %s", sz);
                if (strstr(sz, "child: " Sentinel)) {
                    printf("parent: Got " Sentinel " and killing\n");
                    kill(iProcess, SIGKILL);
                }
            }
            if (waitpid(iProcess, & nStatus, WNOHANG) == iProcess) {
                break;
            }
            usleep(300 * 1000);
            printf("parent: Waiting\n");
            fflush(stdout);
        }
        printf("parent: Done\n");
    }
    return (0);
}
