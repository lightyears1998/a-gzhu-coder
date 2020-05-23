// proc_hello_world.c

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/uaccess.h>
#include <linux/proc_fs.h>

#define PRINTK_TAG KERN_INFO "proc_hello_world: "

static struct proc_dir_entry *proc_parent;
static const char *message = "Hello, world!\n";

static ssize_t proc_read(struct file *filp, char __user *buf, size_t count, loff_t *offp)
{
    ssize_t message_len = strlen(message);

    if (*offp >= message_len) {
        *offp = message_len;
        return 0;
    }
    if (*offp + count > message_len) {
        count = message_len - *offp;
    }

    copy_to_user(buf, message + *offp, count);
    *offp += count;
    return count;
}

static const struct file_operations proc_fops = {
    .read = proc_read
};

int proc_init(void)
{
    // Create a directory named "hello".
    proc_parent = proc_mkdir("hello", NULL);
    if (proc_parent == NULL)
    {
        printk(PRINTK_TAG "[%s] Error creating proc entry!\n", __func__);
        return -ENOMEM;
    }

    // Create a file named "world" and add read attribute to it.
    // With file mode 444, everyone can read this file.
    if (proc_create("world", 0444, proc_parent, &proc_fops) == NULL) {
        printk(PRINTK_TAG "[%s] Error creating proc file!\n", __func__);
        remove_proc_entry("hello", NULL);
        return -ENOMEM;
    }

    printk(PRINTK_TAG "[%s] Successfully initialized.\n", __func__);
    return 0;
}

void proc_cleanup(void)
{
    // Remove file "world" and its parent directory "world".
    remove_proc_entry("world", proc_parent);
    remove_proc_entry("hello", NULL);

    printk(PRINTK_TAG "[%s] Cleanup.\n", __func__);
}

MODULE_LICENSE("GPL");
module_init(proc_init);
module_exit(proc_cleanup);
