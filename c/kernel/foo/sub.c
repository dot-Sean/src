#include <linux/module.h>
#include <linux/init.h>

void
sub () {
  atomic_t int n = 0;
    n ++;
    printk("%s: sub() called\n", __func__);
}
