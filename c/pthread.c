#include <stdio.h>
#include <unistd.h>

#include <netdb.h>

static void *
doOneThing (
  void * pv ) {
  int i;
    for (i = 0; i < 10; i ++) {
      struct hostent ret;
      struct hostent * p;
      char sz[512];
      int n;
        printf("Sub thread %d counts %d.\n", * ((int *) pv), i);
        sleep(1);
        gethostbyname_r("www.yahoo.co.jp", & ret, sz, sizeof (sz),
         & p, & n );
        //if (i == 2) {
        //  int * pn;
        //    pn = NULL;
        //    //(* pn) = 256;
        //}
    }
    printf("Sub thread %d has finished.\n", * ((int *) pv));
    return ((void *) 0);
}

#include <pthread.h>

#define NumThreads 10

int
main (
  int argc,
  char * * argv ) {
  pthread_t apthread[NumThreads];
  int i;
  int j;
  int ai[NumThreads];

{
      struct hostent ret;
      struct hostent * p;
      char sz[512];
      int n;
        gethostbyname_r("www.yahoo.co.jp", & ret, sz, sizeof (sz),
         & p, & n );
}

    for (i = 0; i < NumThreads; i ++) {
      ai[i] = i;
      pthread_create(& apthread[i], (void *) 0, doOneThing, \
       (void *) & ai[i] ); 
    }
    for (i = 0; i < 5; i ++) {
        printf("Main thread counts %d.\n", i);
        //if (i == 3) {
        //  int * pn;
        //    pn = NULL;
        //    (* pn) = 256;
        //    for (j = (NumThreads / 2); j < NumThreads; j ++) {
        //        pthread_cancel(apthread[j]);
        //    }
        //}
        sleep(1);
    }
    printf("Main thread has finished.\n");
    for (i = 0; i < NumThreads; i ++) {
      pthread_join(apthread[i], (void *) 0);
    }
    printf("All done.\n");
    return (0);
}
