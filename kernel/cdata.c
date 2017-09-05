#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/fs.h>
#include <linux/wait.h>
#include <asm/io.h>
#include <asm/uaccess.h>

int my_init_module(void)
{
	return printk(KERN_ALERT "cdata module: registered.\n");
}

void my_cleanup_module(void)
{
	printk(KERN_ALERT "cdata module: unregisterd.\n");
}

module_init(my_init_module);
module_exit(my_cleanup_module);

MODULE_LICENSE("GPL");
