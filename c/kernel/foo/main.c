/*

  todo:
    select/poll
    procfs
    seq_file
    other in ch6

 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/types.h> /* dev_t */
#include <linux/kdev_t.h> /* MKDEV() */
#include <linux/fs.h> /* alloc_chrdev_region() */
#include <linux/cdev.h>
#include <linux/device.h> /* class */
#include <asm/uaccess.h> /* copy_to_user */
#include <linux/string.h> /* memset() */

#include <linux/proc_fs.h>
#include <linux/seq_file.h>

#include "foo_ioctl.h"

MODULE_LICENSE("Dual BSD/GPL");

struct foo_data {
    rwlock_t lock;
    unsigned char val;
};

static int foo_major = 0; /* dynamic allocation */
static const int foo_minor_base = 3;
static const int foo_minor_num = 2;
static const char * driver_name = "foo";
static const char * proc_name = "foo";
static struct cdev foo_cdev; /* required to be global to be freed */
static struct class * foo_class = NULL;

extern void sub(void);

static int
foo_zero_open (
  struct inode * inode,
  struct file * file ) {
    printk("%s(): major: %d, minor: %d, pid %d\n",
     __func__,
     imajor(inode),
     iminor(inode),
     current->pid );
    return (0);
}

static int
foo_close (
  struct inode * inode,
  struct file * filp ) {
  struct foo_data * datp = (struct foo_data *) filp->private_data;
    if (datp) {
        kfree(datp);
    }
    return (0);
}

static int
foo_zero_close (
  struct inode * inode,
  struct file * filp ) {
    printk("%s(): major: %d, minor: %d, pid %d\n",
     __func__,
     imajor(inode),
     iminor(inode),
     current->pid );
    (void) foo_close(inode, filp);
    return (0);
}

static ssize_t
foo_zero_read (
  struct file * filp,
  char __user * buf,
  size_t count,
  loff_t * filepos ) {
  struct foo_data * datp = (struct foo_data *) filp->private_data;
  int i;
  unsigned char val;
  int retval;
    /* printk("%s() called\n", __func__); */
    read_lock(& (datp->lock));
    val = datp->val;
    read_unlock(& (datp->lock));
    for (i = 0; i < count; i ++) {
        if (copy_to_user(& buf[i], & val, 1)) {
            retval = -EFAULT;
            goto out;
        }
    }
    retval = count;
out:
    return (retval);
}

static ssize_t
foo_zero_write (
  struct file * filp,
  const char __user * buf,
  size_t count,
  loff_t * filepos ) {
    printk("%s() called\n", __func__);
    return (0);
}

static int
foo_ioctl (
  struct inode * inode,
  struct file * filp,
  unsigned int cmd,
  unsigned long argp ) {
  int retval = -1;
  struct foo_data * datp = (struct foo_data *) filp->private_data;
  struct foo_ioctl_arg iocarg;
    memset(& iocarg, 0, sizeof (iocarg));
    switch (cmd) {
        case IOCTL_VALSET:
            if (capable(CAP_SYS_ADMIN) == 0) {
                retval = -EPERM;
                goto error;
            }
            /* command ID contains interface information including
               size of data */
            if (access_ok(VERIFY_READ, (void __user *) argp,
             _IOC_SIZE(cmd) ) == 0) {
                retval = -EFAULT;
                goto error;
            }
            if (copy_from_user(& iocarg, (int __user *) argp,
             sizeof (iocarg) ) != 0) {
                retval = -EFAULT;
                goto error;
            }
            write_lock(& datp->lock);
            datp->val = iocarg.val;
            write_unlock(& datp->lock);
            printk("%s(): datp->val: %u\n", __func__, datp->val);
            break;
        case IOCTL_VALGET:
            if (access_ok(VERIFY_READ, (void __user *) argp,
             _IOC_SIZE(cmd) ) == 0) {
                retval = -EFAULT;
                goto error;
            }
            read_lock(& datp->lock);
            iocarg.val = datp->val;
            read_unlock(& datp->lock);
            if (copy_to_user((int __user *) argp, & iocarg,
             sizeof (iocarg) ) != 0) {
                printk("cp1\n");
                retval = -EFAULT;
                goto error;
            }
            break;
        default:
            retval = -ENOTTY;
            goto error;
            break;
    }
    retval = 0;
    goto done;
error:
done:
    return (retval);
}

static struct file_operations foo_zero_fops = {
    .open = foo_zero_open,
    .release = foo_zero_close,
    .read = foo_zero_read,
    .write = foo_zero_write,
    .ioctl = foo_ioctl,
};

static int
foo_one_open (
  struct inode * inode,
  struct file * file ) {
    printk("%s(): major: %d, minor: %d, pid %d\n",
     __func__,
     imajor(inode),
     iminor(inode),
     current->pid );
    return (0);
}

static int
foo_one_close (
  struct inode * inode,
  struct file * filp ) {
    printk("%s(): major: %d, minor: %d, pid %d\n",
     __func__,
     imajor(inode),
     iminor(inode),
     current->pid );
    (void) foo_close(inode, filp);
    return (0);
}

static ssize_t
foo_one_read (
  struct file * filp,
  char __user * buf,
  size_t count,
  loff_t * filepos ) {
  int i;
  unsigned char val = 0xFE;
  int retval;
    /* printk("%s() called\n", __func__); */
    for (i = 0; i < count; i ++) {
        if (copy_to_user(& buf[i], & val, 1)) {
            retval = -EFAULT;
            goto out;
        }
    }
    retval = count;
out:
    return (retval);
}

static ssize_t
foo_one_write (
  struct file * filp,
  const char __user * buf,
  size_t count,
  loff_t * filepos ) {
    printk("%s() called\n", __func__);
    return (0);
}

static struct file_operations foo_one_fops = {
    .open = foo_one_open,
    .release = foo_one_close,
    .read = foo_one_read,
    .write = foo_one_write,
    .ioctl = foo_ioctl,
};

static int
foo_open (
  struct inode * inode,
  struct file * filp ) {
  struct foo_data * datp = NULL;
  int retval = -1;
    printk("%s(): major: %d, minor: %d, pid %d\n",
     __func__,
     imajor(inode),
     iminor(inode),
     current->pid );
    datp = kmalloc(sizeof (struct foo_data), GFP_KERNEL);
    if (datp == NULL) {
        retval = -1;
        goto error;
    }
    rwlock_init(& datp->lock);
    datp->val = 0xFF;
    filp->private_data = (void *) datp;
    switch (iminor(inode)) {
        case foo_minor_base + 0:
            filp->f_op = & foo_zero_fops;
            break;
        case foo_minor_base + 1:
            filp->f_op = & foo_one_fops;
            break;
        default:
            retval = -1;
            goto error;
    }
    if (filp->f_op && filp->f_op->open) {
        return (filp->f_op->open(inode, filp));
    }
    retval = 0;
    goto done;
error:
    if (datp) {
        kfree(datp);
    }
done:
    return (retval);
}

static struct file_operations foo_fops = {
    .open = foo_open,
};

static char * apsz[] = {
    "foo",
    "bar",
    "buzz",
    NULL,
};

static void *
as_start (
  struct seq_file * m,
  loff_t * poffset ) {
  loff_t offset = (* poffset);
  int idx;
    if (offset == 0) { /* top of the top */
        seq_printf(m, "### Header ###\n");
    }
    for (idx = 0; apsz[idx]; idx ++) {
        offset --;
        if (offset < 0) {
            return ((void *) (idx + 1));
        }
    }
    /* No more data now (-> as_stop() and finish) */
    return (0);
}

static void *
as_next (
  struct seq_file * m,
  void * pv,
  loff_t * poffset ) {
  int idx = (int) pv;
    (* poffset) ++;
    if (apsz[idx]) {
        return ((void *) (idx + 1));
    }
    /* No more data now (-> as_stop() -> as_start() again) */
    return (0);
}

static void
as_stop (
  struct seq_file * m,
  void * pv ) {
  int idx = (int) pv;
    seq_printf(m, "### Footer ###\n");
    printk("%s(%d): \n", __func__, idx);
}

static int
as_show (
  struct seq_file * m,
  void * pv ) {
  int idx = ((int) pv) - 1;
    seq_printf(m, "[%d] %s\n", idx, apsz[idx]);
    return (0);
}

static struct seq_operations foo_seq_ops = {
    .start = as_start,
    .next = as_next,
    .stop = as_stop,
    .show = as_show,
};

static int
foo_proc_open (
  struct inode * inode,
  struct file * filp ) {
    return (seq_open(filp, & foo_seq_ops));
}

static struct file_operations foo_proc_operations = {
    .open = foo_proc_open,
    .read = seq_read,
    .llseek = seq_lseek,
    .release = seq_release,
};

static int
foo_init (void) {
  dev_t foo_dev = MKDEV(foo_major, foo_minor_base);
  int alloc_chrdev_region_error = -1;
  int cdev_add_error = -1;
  int class_create_error = -1;
  struct proc_dir_entry * proc_entry;
  int i;
    alloc_chrdev_region_error = alloc_chrdev_region(
     & foo_dev, /* dev_t * dev */
     foo_minor_base, /* unsigned baseminor */
     foo_minor_num, /* unsigned count */
     driver_name ); /* const char * name */
    if (alloc_chrdev_region_error != 0) {
        goto error;
    }
    foo_major = MAJOR(foo_dev);
    cdev_init(& foo_cdev, & foo_fops);
    foo_cdev.owner = THIS_MODULE; /* struct module * */
    cdev_add_error = cdev_add(& foo_cdev, foo_dev, foo_minor_num);
    if (cdev_add_error != 0) {
        goto error;
    }
    /* class registration */
    foo_class = class_create(THIS_MODULE, "foo");
    class_create_error = IS_ERR(foo_class);
    if (class_create_error) {
        goto error;
    }
    for (i = 0; i < foo_minor_num; i ++) {
      dev_t foo_dev_tmp = MKDEV(foo_major, foo_minor_base + i);
        class_device_create(
         foo_class,
         NULL,
         foo_dev_tmp,
         NULL,
         "foo%d",
         foo_minor_base + i );
    }
    proc_entry = create_proc_entry(proc_name, S_IRUGO | S_IWUGO, NULL);
    if (proc_entry) {
        proc_entry->proc_fops = & foo_proc_operations;
    }
    printk(KERN_ALERT "driver %s (major: %d) installed.\n",
     driver_name, foo_major );
    return (0);
error:
    if (class_create_error == 0) {
        for (i = 0; i < foo_minor_num; i ++) {
          dev_t foo_dev_tmp = MKDEV(foo_major, foo_minor_base + i);
            class_device_destroy(foo_class, foo_dev_tmp);
        }
        class_destroy(foo_class);
    }
    if (cdev_add_error == 0) {
        cdev_del(& foo_cdev);
    }
    if (alloc_chrdev_region_error == 0) {
        unregister_chrdev_region(foo_dev, foo_minor_num);
    }
    return (-1);
}

static void
foo_exit (void) {
  dev_t foo_dev = MKDEV(foo_major, foo_minor_base);
  int i;
    remove_proc_entry(proc_name, NULL);
    for (i = 0; i < foo_minor_num; i ++) {
      dev_t foo_dev_tmp;
        foo_dev_tmp = MKDEV(foo_major, foo_minor_base + i);
        class_device_destroy(foo_class, foo_dev);
    }
    class_destroy(foo_class);
    cdev_del(& foo_cdev);
    unregister_chrdev_region(foo_dev, foo_minor_num);
    printk(KERN_ALERT "driver %s removed.\n", driver_name);
}

module_init(foo_init);
module_exit(foo_exit);
