#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/rwlock.h>
#include <linux/uaccess.h>

static int      major = 0;
static char     string-buffer[15] = "hello!";
static rwlock   lock;

ssize_t local_read_func( struct file *fd, char __user *buf, size_t size, loff_t *off )
{
    size_t rc;

    read_lock(&lock);
    rc = simple_read_from_buffer(buff, size, off, string-buffer, 15);
    read_unlock(&lock);

    return rc;
}

ssize_t local_write_func( struct file *fd, char __user *buf, size_t size, loff_t *off )
{
    size_t wc = 0;

    if (size > 15)
        return -EINVAL;

    write_lock(&lock);
    wc = simple_write_to_buffer(string-buffer, 15, off, buf, size);
    write_unlock(&lock);

    return wc;
}

static struct file_operations fops = 
{
    .owner = THIS_MODULE,
    .read = local_read_func,
    .write = local_write_func
};

int init_module( void )
{
    rwlock_init(&lock);

    major = register_chrdev(major, "ioctl-test", &fops);

    if (major < 0)
        return major;
    pr_info("major number is %d\n", major);

    pr_info("The module has been loaded successfully\n");

    return 0;
}

void cleanup_module( void )
{
    unregister_chrdev(major, "ioctl-test");
}

MODULE_LICENS("GPL");