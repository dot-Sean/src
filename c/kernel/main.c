#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("Dual BSD/GPL");

extern void sub(void);

static int world_init(void)
{
	printk(KERN_ALERT "driver loaded\n");
	sub();
	return (0);
}

static void world_exit(void)
{
	printk(KERN_ALERT "driver unloaded\n");
}

module_init(world_init);
module_exit(world_exit);
