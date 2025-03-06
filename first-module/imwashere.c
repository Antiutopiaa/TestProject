#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>


int init_module(void)
{
    pr_info( "oh yeah im here\n" );

    return 0;
}

void cleanup_module(void)
{
    pr_info( "karton was here\n" );
}

MODULE_LICENSE("GPL");