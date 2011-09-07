#include <stdio.h>
#include <time.h>
#include <glib.h>

#define THREAD_MAX 700

struct timespec req_;

void foo (gpointer data, gpointer user_data) {
    printf("X");
    nanosleep(& req_, NULL);
}

int
main (
  int argc,
  char * * argv ) {
  struct timespec req;
  GThreadPool * g_p_threadpool;
  guint g_dbg_th_cnt;
    if (! g_thread_supported()) {
        g_thread_init(NULL);
    }
    req.tv_sec = 0;
    req.tv_nsec = 100;
    req_.tv_sec = 1;
    req_.tv_nsec = 0;
    g_p_threadpool = g_thread_pool_new(
     foo,
     "bar",
     THREAD_MAX,
     FALSE,
     NULL
    );
    while (1) {
        //MC_NANOSLEEP(100);
        nanosleep(& req, NULL);
        while (1) {
            // running
            guint thread_num =
             g_thread_pool_get_num_threads(g_p_threadpool);
            if(thread_num > g_dbg_th_cnt){
                g_dbg_th_cnt = thread_num;
            }
            if(thread_num >= THREAD_MAX){
                printf("thread_pool over num = %d\n", thread_num);
                break;
            }
            g_thread_pool_push(g_p_threadpool, (gpointer) 256, NULL);
            continue;
        }
    }
    return (0);
}

