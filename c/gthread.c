#include <stdio.h>

#include <glib.h>

static void *
doOneThing (
  void * pv ) {
  int i;
    for (i = 0; i < 10; i ++) {
        printf("Sub thread counts %d.\n", i);
        sleep(1);
    }
    printf("Sub thread has finished.\n");
    return ((void *) 0);
}

int
main (
  int argc,
  char * * argv ) {
    if (! g_thread_supported()) {
        g_thread_init((void *) 0);
    }
    if (g_thread_supported()) {
        printf("gthread is supported\n");
    } else {
        printf("gthread is not supported\n");
    }

    return (0);

//    pthread_create(& pthread, (void *) 0, doOneThing, (void *) 0); 
//    for (i = 0; i < 5; i ++) {
//        printf("Main thread counts %d.\n", i);
//        sleep(1);
//    }
//    printf("Main thread has finished.\n");
//    pthread_join(pthread, (void *) 0);
//    printf("All done.\n");
//    return (0);
//}

}
