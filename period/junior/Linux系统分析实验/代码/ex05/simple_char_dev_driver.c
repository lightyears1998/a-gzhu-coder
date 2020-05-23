// simple_char_dev_driver.c

#include <linux/kernel.h>
#include <linux/vmalloc.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/string.h>
#include <linux/uaccess.h>
#include <linux/init.h>
#include <linux/cdev.h>

#define DEVICE_NAME "simple_char_dev"
#define BUFFER_SIZE 4096
#define NEXT_INDEX(idx) ((idx + 1) % BUFFER_SIZE)
#define LOG(string) printk(DEVICE_NAME ": [%s] " string, __func__)
#define LOGF(format, ...) printk(DEVICE_NAME ": [%s] " format, __func__, __VA_ARGS__)

static dev_t dev;
static struct cdev *simple_cdev;
static signed count = 1;
static char *buffer;
static int write_index = 0;
static int read_index = 0;

static int simple_char_dev_open(struct inode *inode, struct file *file)
{
    int major = MAJOR(inode->i_rdev);
    int minor = MINOR(inode->i_rdev);

    LOGF("Device opened, major = %d, minor = %d\n", major, minor);
    return 0;
}

static ssize_t simple_char_dev_read(struct file *file, char __user *buf, size_t count, loff_t *offset)
{
    char *read_buffer;
    int read_count = 0;

    read_buffer = vmalloc(PAGE_SIZE);
    if (read_buffer == NULL) {
        return 0;
    }

    while (read_index != write_index) {
        read_buffer[read_count++] = buffer[read_index];
        read_index = NEXT_INDEX(read_index);
    }
    copy_to_user(buf, read_buffer, read_count);

    vfree(read_buffer);

    LOGF("%d bytes read.\n", read_count);
    return read_count;
}

static ssize_t simple_char_dev_write(struct file *file, const char __user *buf, size_t count, loff_t *offset)
{
    char *write_buffer;
    int write_count = 0;

    write_buffer = vmalloc(PAGE_SIZE);
    if (write_buffer == NULL) {
        return 0;
    }
    if (count > BUFFER_SIZE) {
        count = BUFFER_SIZE;
    }
    copy_from_user(write_buffer, buf, count);

    do {
        buffer[write_index] = write_buffer[write_count++];
        write_index = NEXT_INDEX(write_index);
    } while (--count > 0 && write_index != read_index);
    if (count > 0) {
        LOGF("%ld bytes from user is not written due to full buffer.\n", count);
    }

    vfree(write_buffer);

    LOGF("%d bytes written.\n", write_count);
    return write_count;
}

static const struct file_operations simple_char_dev_fops = {
    .owner = THIS_MODULE,
    .open = simple_char_dev_open,
    .read = simple_char_dev_read,
    .write = simple_char_dev_write,
};

static int __init simple_char_dev_init(void)
{
    int ret = 0;
    const char *welcome_message = "The simple char device is initialized.\n";

    buffer = vmalloc(BUFFER_SIZE);
    if (buffer == NULL) {
        ret = -ENOMEM;
        goto out;
    }
    strcpy(buffer, welcome_message);
    write_index += strlen(welcome_message) + 1;

    ret = alloc_chrdev_region(&dev, 0, count, DEVICE_NAME);
    if (ret)
    {
        LOG("Fail to allocate char device region.\n");
        goto out;
    }

    simple_cdev = cdev_alloc();
    if (!simple_cdev)
    {
        LOG("Fail to cedv_alloc().\n");
        goto unregister_chrdev;
    }

    cdev_init(simple_cdev, &simple_char_dev_fops);
    ret = cdev_add(simple_cdev, dev, count);
    if (ret)
    {
        LOG("Fail to cdev_add().\n");
        goto cdev_fail;
    }

    LOGF("Sucessfully register char device: %s.\n", DEVICE_NAME);
    LOGF("Major number = %d, Minor number = %d.\n", MAJOR(dev), MINOR(dev));
    goto out;

cdev_fail:
    cdev_del(simple_cdev);

unregister_chrdev:
    unregister_chrdev_region(dev, count);

out:
    return ret;
}

static void __exit simple_char_dev_exit(void)
{
    vfree(buffer);
    cdev_del(simple_cdev);
    unregister_chrdev_region(dev, count);

    LOG("Device removed.\n");
}

MODULE_LICENSE("GPL");
module_init(simple_char_dev_init);
module_exit(simple_char_dev_exit);
