#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/kd.h>
#include <asm/timex.h>

#if 0

/* normal C99 */

#define putmsg(msg, ...) \
    do { \
        fprintf(stderr, msg " (%s:%s()): ", __FILE__, __func__); \
        fprintf(stderr, __VA_ARGS__); \
        fputs("\n", stderr); \
        fflush(stderr); \
    } while (0)

#endif

#if 0

/* C99 + GCC extension. "fmt" must be literal */

#define putmsg(msg, fmt, ...) \
    do { \
        fprintf(stderr, msg " (%s:%s()): " fmt "\n", __FILE__, \
         __func__, ## __VA_ARGS__ ); \
        fflush(stderr); \
    } while (0)

#else

/* only C99 (tricky). "fmt" must be literal */

#define putmsgsub(msg, fmt, ...) \
    do { \
        fprintf(stderr, msg " (%s:%s()): " fmt "%s\n", __FILE__, \
         __func__, __VA_ARGS__ ); \
        fflush(stderr); \
    } while (0)

#define putmsg(msg, ...) putmsgsub(msg, __VA_ARGS__, "")

#endif

#define iput(...) putmsg("Info", __VA_ARGS__)
#define wput(...) putmsg("Warning", __VA_ARGS__)
#define eput(...) putmsg("Error", __VA_ARGS__)

int
beep (
  float rFreq,
  int nLength,
  int nDelay ) {
  int rc = -1;
  int fd = -1;
    do {
        if ((fd = open("/dev/console", O_WRONLY)) < 0) {
            eput("Couldn't open console.");
            break;
        }
        if (ioctl(fd, KIOCSOUND, (int) (CLOCK_TICK_RATE / rFreq)) != 0) {
            eput("ioctl(2) failed.");
            break;
        }
        usleep(1000 * nLength);
        if (ioctl(fd, KIOCSOUND, (int) 0) != 0) {
            eput("ioctl(2) failed.");
            break;
        }
        usleep(1000 * nDelay);
        rc = 0;
    } while (0);
    if (fd >= 0) { close(fd); }
    return (rc);
}

int
main (
  int argc,
  char * * argv ) {
    //beep(261.6, 120, 0);
    beep(261.6, 50, 0);
    beep(220.0, 50, 0);
    sleep(2);
    beep(392.0, 50, 0);
    beep(523.3, 50, 0);
    return (0);
}
