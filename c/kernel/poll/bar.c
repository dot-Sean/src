#include <linux/module.h>
#include <linux/init.h>
#include <linux/types.h> /* dev_t */
#include <linux/kdev_t.h> /* MKDEV() */
#include <linux/fs.h> /* alloc_chrdev_region() */
#include <linux/cdev.h>
#include <linux/device.h> /* class */
#include <asm/uaccess.h> /* copy_to_user */
#include <linux/string.h> /* memset() */
#include <linux/poll.h>
#include <linux/spinlock.h>

MODULE_LICENSE("Dual BSD/GPL");

static unsigned int timeout_value = 10;
module_param(timeout_value, uint, 0);

static int bar_major = 0; /* dynamic allocation */
static const int bar_minor_base = 0;
static const int bar_minor_num = 1;
static const char * driver_name = "bar";
static struct cdev bar_cdev; /* required to be global to be freed */
static struct class * bar_class = NULL;

struct bar_data {
    struct timer_list timeout; /* Should be driver global? */
    spinlock_t lock; /* Should be driver global? */
    int timeout_done; /* Should be driver global? */
    wait_queue_head_t read_wait; /* for poll() */
    struct semaphore sem; /* for resource exclusive mgmt. Shoud be
     driver global? */
};

static int
bar_close (
  struct inode * inode,
  struct file * filp ) {
  struct bar_data * datp = (struct bar_data *) filp->private_data;
    del_timer_sync(& (datp->timeout));
    kfree(datp);
    return (0);
}

static unsigned int
bar_poll (
  struct file * filp,
  poll_table * wait ) {
  struct bar_data * datp = (struct bar_data *) filp->private_data;
  unsigned int retval = POLLOUT | POLLWRNORM;
    if (datp == NULL) {
        retval = -EBADFD; /* signed ? */
        goto error;
    }
    down(& (datp->sem)); /* why not interruptible? */
    poll_wait(filp, & (datp->read_wait), wait); /* ? */
    if (datp->timeout_done == 1) {
        retval |= POLLIN | POLLRDNORM;
    }
    up(& (datp->sem));
    goto done;
error:
done:
    return (retval);
}

static ssize_t
bar_read (
  struct file * filp,
  char __user * buf,
  size_t count,
  loff_t * filepos ) {
  struct bar_data * datp = (struct bar_data *) filp->private_data;
  int i;
  unsigned char val;
  int retval;
    /* Starts to read the resource of the device. Fails if interrupted
       while waiting for semaphore */
    /* This is to see datp->timeout_done here. Which designates
       whether there is data to be read or not */
    if (down_interruptible(& (datp->sem)) != 0) {
        retval = -ERESTARTSYS;
        goto error;
    }
    if (datp->timeout_done == 0) { /* no data */
        up(& (datp->sem)); /* Release the resource */
        if (filp->f_flags & O_NONBLOCK) {
            retval = -EAGAIN;
            goto error;
        }
        do {
            /* the 2nd arg is the condition which means there is data
               to be read */
            retval = wait_event_interruptible_timeout(
             datp->read_wait, datp->timeout_done == 1, 1 * HZ );
            if (retval == -ERESTARTSYS) {
                goto error;
            }
            if (retval != 0) {
                goto error;
            }
        } while (retval == 0);
        /* There is data. I will restart to read */
        if (down_interruptible(& (datp->sem))) {
            retval = -ERESTARTSYS;
            goto error;
        }
    }
    val = 0xFF;
    for (i = 0; i < count; i ++) {
        if (copy_to_user(& buf[i], & val, 1)) {
            retval = -EFAULT;
            break; /* Not error */
        }
    }
    /* No data now */
    datp->timeout_done = 0;
    mod_timer(& (datp->timeout), jiffies + timeout_value * HZ);
    /* Done */
    up(& (datp->sem));
    retval = count;
    goto done;
error:
done:
    return (retval);
}

static ssize_t
bar_write (
  struct file * filp,
  const char __user * buf,
  size_t count,
  loff_t * filepos ) {
    return (-EFAULT);
}

/* This would be interrupt (IRQ) function for real driver */
/* You cannot use semaphore because which is bound to a process. Use
   spin_lock_irqsave() to disable CPU interruption while locked */
static void
bar_timeout (
  unsigned long arg ) {
  struct bar_data * datp = (struct bar_data *) arg;
  unsigned long flags; /* Stores IRQ state before lock */
    printk("%s() called\n", __func__);
    spin_lock_irqsave(& (datp->lock), flags);
    datp->timeout_done = 1;
    wake_up_interruptible(& (datp->read_wait));
    spin_unlock_irqrestore(& (datp->lock), flags);
    printk("%s() done\n", __func__);
}

static int
bar_open (
  struct inode * inode,
  struct file * filp ) {
  struct bar_data * datp = NULL;
  int retval = -1;
    printk("%s(): major: %d, minor: %d, pid %d\n",
     __func__,
     imajor(inode),
     iminor(inode),
     current->pid );
    datp = kmalloc(sizeof (struct bar_data), GFP_KERNEL);
    if (datp == NULL) {
        retval = -1;
        goto error;
    }
    /* Initialize */
    memset(datp, 0 ,sizeof (struct bar_data));
    spin_lock_init(& (datp->lock));
    init_waitqueue_head(& (datp->read_wait));
    init_MUTEX(& (datp->sem));
    init_timer(& (datp->timeout));
    datp->timeout.function = bar_timeout;
    datp->timeout.data = (unsigned long) datp;
    filp->private_data = datp;
    /* Start timer */
    datp->timeout_done = 0;
    mod_timer(& (datp->timeout), jiffies + timeout_value * HZ);
    retval = 0;
    goto done;
error:
    if (datp) {
        del_timer_sync(& (datp->timeout));
        kfree(datp);
    }
done:
    return (retval);
}

static struct file_operations bar_fops = {
    .owner = THIS_MODULE,
    .open = bar_open,
    .release = bar_close,
    .read = bar_read,
    .write = bar_write,
    .poll = bar_poll,
};

static int
bar_init (void) {
  dev_t bar_dev = MKDEV(bar_major, bar_minor_base);
  int alloc_chrdev_region_error = -1;
  int cdev_add_error = -1;
  int class_create_error = -1;
  int i;
    alloc_chrdev_region_error = alloc_chrdev_region(
     & bar_dev, /* dev_t * dev */
     bar_minor_base, /* unsigned baseminor */
     bar_minor_num, /* unsigned count */
     driver_name ); /* const char * name */
    if (alloc_chrdev_region_error != 0) {
        goto error;
    }
    bar_major = MAJOR(bar_dev);
    cdev_init(& bar_cdev, & bar_fops);
    bar_cdev.owner = THIS_MODULE; /* struct module * */
    cdev_add_error = cdev_add(& bar_cdev, bar_dev, bar_minor_num);
    if (cdev_add_error != 0) {
        goto error;
    }
    /* class registration */
    bar_class = class_create(THIS_MODULE, "bar");
    class_create_error = IS_ERR(bar_class);
    if (class_create_error) {
        goto error;
    }
    for (i = 0; i < bar_minor_num; i ++) {
      dev_t bar_dev_tmp = MKDEV(bar_major, bar_minor_base + i);
        class_device_create(
         bar_class,
         NULL,
         bar_dev_tmp,
         NULL,
         "bar%d",
         bar_minor_base + i );
    }
    printk(KERN_ALERT "driver %s (major: %d) installed.\n",
     driver_name, bar_major );
    return (0);
error:
    if (class_create_error == 0) {
        for (i = 0; i < bar_minor_num; i ++) {
          dev_t bar_dev_tmp = MKDEV(bar_major, bar_minor_base + i);
            class_device_destroy(bar_class, bar_dev_tmp);
        }
        class_destroy(bar_class);
    }
    if (cdev_add_error == 0) {
        cdev_del(& bar_cdev);
    }
    if (alloc_chrdev_region_error == 0) {
        unregister_chrdev_region(bar_dev, bar_minor_num);
    }
    return (-1);
}

static void
bar_exit (void) {
  dev_t bar_dev = MKDEV(bar_major, bar_minor_base);
  int i;
    for (i = 0; i < bar_minor_num; i ++) {
      dev_t bar_dev_tmp;
        bar_dev_tmp = MKDEV(bar_major, bar_minor_base + i);
        class_device_destroy(bar_class, bar_dev);
    }
    class_destroy(bar_class);
    cdev_del(& bar_cdev);
    unregister_chrdev_region(bar_dev, bar_minor_num);
    printk(KERN_ALERT "driver %s removed.\n", driver_name);
}

module_init(bar_init);
module_exit(bar_exit);
