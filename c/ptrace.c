static char * asz_[250] = { (void *) 0 };

static void
initTable () {
 int i;
    for (i = 0; i < sizeof (asz_) / sizeof (char *) ; i ++) {
        asz_[i] = "Unknown";
    }
    #include "numtbl.h"
}

static const char *
idToSyscall (
  int i ) {
    if (! asz_[0]) {
        initTable();
    }
    if (sizeof (asz_) / sizeof (char *) <= i) {
        return ("Invalid");
    }
    return (asz_[i]);
}

#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/user.h>
#include <sys/syscall.h>

int
main (
  int argc,
  char * * argv ) {
  pid_t pid;
    if ((pid = fork()) == 0) {
        ptrace(PTRACE_TRACEME, (pid_t) 0, (void *) 0, (void *) 0);
        /* exec(2) causes this process stop with SIGTRAP */
	execvp(argv[1], argv + 1);
        return (-1);
    }
    {
      int iStat = 0;
      int fReturn = 1;
        while (wait(& iStat) >= 0) {
            if (WIFEXITED(iStat)) {
                break;
            } else if (WIFSTOPPED(iStat)) {
              struct user_regs_struct regs;
                ptrace(PTRACE_GETREGS, pid, (void *) 0, (void *) & regs);
                if (fReturn) {
                    fprintf(stderr, "%s() = %ld\n", \
                     idToSyscall(regs.orig_eax), regs.eax );
                } else if (regs.orig_eax == __NR_exit) {
                    fprintf(stderr, "%s() = ?\n", \
                     idToSyscall(regs.orig_eax) );
                }
                fflush(stdout);
                ptrace(PTRACE_SYSCALL, pid, (void *) 0, (void *) 0);
                fReturn = ! fReturn;
            }
        }
    }
    return (0);
}

    
