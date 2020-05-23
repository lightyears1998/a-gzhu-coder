#include <linux/kconfig.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#define PRINTK_TAG "task2_kmodule: "

static int __init kmodule_init(void)
{
    printk(KERN_INFO PRINTK_TAG "Hello World!\n");
    return 0;
}

static void __exit kmodule_exit(void)
{
    printk(KERN_INFO PRINTK_TAG "Goodbye!\n");
}

module_init(kmodule_init);
module_exit(kmodule_exit);
MODULE_LICENSE("GPL");
