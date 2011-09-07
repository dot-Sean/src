#ifndef IPUT_H
#define IPUT_H

#include <stdio.h>

#define putmsg(msg, ...) \
    do { \
        fprintf(stderr, msg " (%s:%s()): ", __FILE__, __func__); \
        fprintf(stderr, __VA_ARGS__); \
        fflush(stderr); \
    } while (0)

#define iput(...) putmsg("Info", __VA_ARGS__)
#define wput(...) putmsg("Warning", __VA_ARGS__)
#define eput(...) putmsg("Error", __VA_ARGS__)

#endif
