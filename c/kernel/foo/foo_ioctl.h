#ifndef _FOO_IOCTL_H
#define _FOO_IOCTL_H

#include <linux/ioctl.h>

struct foo_ioctl_arg {
    unsigned int reg;
    unsigned int offset;
    unsigned int val;
};

#define IOC_MAGIC 'f'

/* 3rd arg is to know iocarg size */
#define IOCTL_VALSET _IOW(IOC_MAGIC, 1, struct foo_ioctl_arg)
#define IOCTL_VALGET _IOR(IOC_MAGIC, 2, struct foo_ioctl_arg)

#endif
