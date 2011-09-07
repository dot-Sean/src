#include <stdio.h>
#include <unistd.h>
#include <string.h>

#if defined(USE_CLONE)
    #include <sched.h>
    #define MyMutex int
    void
    initMutex (
      MyMutex * pmutex ) {
        (* pmutex) = 0;
    }
    #include <signal.h>
    int
    lockMutex (
      MyMutex * pmutex ) {
        while ((* pmutex) > 0) {
            usleep(10 * 1000);
        }
        (* pmutex) ++;
        return (0);
    }
    int
    unlockMutex (
      MyMutex * pmutex ) {
        (* pmutex) --;
        return (0);
    }
    #define doClone clone
    #define doWaitPid waitpid
#else /* Not defined USE_CLONE */
    # define CSIGNAL       0x000000ff
    # define CLONE_VM      0x00000100
    # define CLONE_FS      0x00000200
    # define CLONE_FILES   0x00000400
    # define CLONE_SIGHAND 0x00000800
    # define CLONE_PID     0x00001000
    # define CLONE_PTRACE  0x00002000
    # define CLONE_VFORK   0x00004000
    #include <pthread.h>
    #include <sys/types.h>
    #include <stdlib.h>
    typedef pthread_mutex_t MyMutex;
    #define initMutex(pmutex) \
     pthread_mutex_init(pmutex, (void *) 0)
    #define lockMutex pthread_mutex_lock
    #define unlockMutex pthread_mutex_unlock
    struct PthreadDat {
        int (* funcCloneCallback) (void *);
        void * pvCloneArg;
        int nCloneRet;
        pthread_t pthread;
        int nFlags;
    };
    static void *
    pthreadCallback (
      void * pv ) {
      struct PthreadDat * pdat;
        pdat = (struct PthreadDat *) pv;
        pdat->nCloneRet = \
         pdat->funcCloneCallback(pdat->pvCloneArg);
        return ((void *) pdat);
    }
    /* TODO: do fork() if necessary and return pid */
    int doClone(
      int (* funcCloneCallback) (void *),
      void * pvStackUnused,
      int nFlags,
      void * pvCloneArg ) {
      struct PthreadDat * pdat;
        if (nFlags & CLONE_VFORK) {
          pid_t pid;
            pid = vfork();
            if (pid == 0) {
                /* Why don't you stop till _exit(2)? */
                _exit(funcCloneCallback(pvCloneArg));
            }
            return (pid);
        } else if ((nFlags & CLONE_VM) == 0) {
          pid_t pid;
            pid = fork();
            if (pid == 0) {
                exit(funcCloneCallback(pvCloneArg));
            }
            return (pid);
        }
        pdat = \
         (struct PthreadDat *) malloc(sizeof (struct PthreadDat));
        pdat->funcCloneCallback = funcCloneCallback;
        pdat->pvCloneArg = pvCloneArg;
        pdat->nFlags = nFlags;
        pthread_create(& (pdat->pthread), (void *) 0, \
         pthreadCallback, (void *) pdat );
        return ((pid_t) pdat);
    }
    #include <sys/wait.h>
    int
    doWaitPid(pid_t pid, int *status, int options) {
      struct PthreadDat * pdat;
        /* TODO: ...? */
        if (pid < 65535) {
            return (waitpid(pid, status, options));
        }
        pdat = (struct PthreadDat *) pid;
        pthread_join(pdat->pthread, (void *) 0);
        /* Exit status is always 0 because termination of child */
        /* "thread" causes the parent to die */
        (* status) = 0;
        (* status) |= (pdat->nCloneRet & 0xff) << 8;
        free((void *) pdat);
        return (0);
    }
#endif

MyMutex mutexStdout_;

#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>

static int
doOneThing (
  void * pv ) {
  int i;
    for (i = 0; i < 6; i ++) {
        lockMutex(& mutexStdout_);
        fprintf(stdout, "Sub thread counts %d.\n", i);
        unlockMutex(& mutexStdout_);
        usleep(800 * 1000);
    }
    lockMutex(& mutexStdout_);
    fprintf(stdout, "Sub thread has finished its work.\n");
    unlockMutex(& mutexStdout_);
    return (123);
}

#define StackSize 4096

int
main (
  int argc,
  char * * argv ) {
  int i;
  pid_t pid;
  int iStatus;
  void * pvStack;
    initMutex(& mutexStdout_);
    pvStack = malloc(StackSize);
    pid = doClone(doOneThing,
      pvStack + StackSize - sizeof (void *),
     CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | SIGCHLD,
     (void *) 0 );
    for (i = 0; i < 3; i ++) {
        lockMutex(& mutexStdout_);
        fprintf(stdout, "Main thread counts %d.\n", i);
        unlockMutex(& mutexStdout_);
        usleep(1000 * 1000);
    }
    lockMutex(& mutexStdout_);
    fprintf(stdout, "Main thread has finished its work.\n");
    unlockMutex(& mutexStdout_);
    while (doWaitPid(pid, & iStatus, 0) >= 0) {
        if (WIFEXITED(iStatus)) {
            fprintf(stdout, "Child returned %d.\n",
             WEXITSTATUS(iStatus) );
            break;
        }
    }
    free(pvStack);
    lockMutex(& mutexStdout_);
    fprintf(stdout, "All done.\n");
    unlockMutex(& mutexStdout_);
    return (0);
}

