#include "cprog.h"

#include <time.h>

const char *
get_time () {
  char * psz = (char *) malloc((sizeof (char)) * (26 + 1));
  time_t time1;
    time(& time1);
    if (! ctime_r(& time1, psz)) {
        free(psz);
        return ((void *) 0);
    }
    psz[strlen(psz) - 1] = '\0';
    return (psz);
}
