// map_driver.c

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/string.h>
#include <linux/errno.h>
#include <linux/mm.h>
#include <linux/vmalloc.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/io.h>
#include <linux/mman.h>

#define MAP_PAGE_COUNT 10
#define MAPLEN (PAGE_SIZE * MAP_PAGE_COUNT)
#define MAP_DEV_MAJOR 280
#define MAP_DEV_NAME "mapnopage"
#define PRINTK_TAG KERN_INFO MAP_DEV_NAME ": "

void map_vopen(struct vm_area_struct *vma);
void map_vclose(struct vm_area_struct *vma);

static int mapdrv_mmap(struct file *file, struct vm_area_struct *vma);
static int mapdrv_open(struct inode *inode, struct file *file);

static vm_fault_t map_fault(struct vm_fault *vmf);

static struct file_operations mapdrvo_fops = {
    .owner = THIS_MODULE,
    .mmap = mapdrv_mmap,
    .open = mapdrv_open,
};

static struct vm_operations_struct map_vm_ops = {
    .open = map_vopen,
    .close = map_vclose,
    .fault = map_fault,
};

static char *vmalloc_area = NULL;

static int __init mapdrv_init(void)
{
    int result;
    unsigned long virt_addr;
    int i = 1;

    result = register_chrdev(MAP_DEV_MAJOR, MAP_DEV_NAME, &mapdrvo_fops);
    if (result < 0)
    {
        return result;
    }

    vmalloc_area = vmalloc(MAPLEN);
    virt_addr = (unsigned long)vmalloc_area;

    for (virt_addr = (unsigned long)vmalloc_area;
         virt_addr < (unsigned long)vmalloc_area + MAPLEN;
         virt_addr += PAGE_SIZE)
    {
        SetPageReserved(vmalloc_to_page((void *)virt_addr));
        sprintf((char *)virt_addr, "Test %d", i++);
    }

    printk(PRINTK_TAG "[%s] vmalloc_area apply completely!\n", __func__);
    return 0;
}

static void __exit mapdrv_exit(void)
{
    unsigned long virt_addr;

    // Unreserve all pages.
    for (virt_addr = (unsigned long)vmalloc_area;
         virt_addr < (unsigned long)vmalloc_area + MAPLEN;
         virt_addr += PAGE_SIZE)
    {
        ClearPageReserved(vmalloc_to_page((void *)virt_addr));
    }

    // Free vmalloc_area and unregister char device.
    if (vmalloc_area)
        vfree(vmalloc_area);
    unregister_chrdev(MAP_DEV_MAJOR, MAP_DEV_NAME);
}

static int mapdrv_mmap(struct file *file, struct vm_area_struct *vma)
{
    unsigned long offset = vma->vm_pgoff << PAGE_SHIFT;
    unsigned long size = vma->vm_end - vma->vm_start;
    if (size > MAPLEN)
    {
        printk(PRINTK_TAG "[%s] size too big.\n", __func__);
        return ENXIO;
    }

    // Support shared mapping only.
    if ((vma->vm_flags & VM_WRITE) && !(vma->vm_flags & VM_SHARED))
    {
        printk(PRINTK_TAG "[%s] writeable mappings must be shared, rejecting.\n", __func__);
        return -EINVAL;
    }

    // Lock area to avoid it swapping out.
    vma->vm_flags |= VM_LOCKONFAULT;
    if (offset == 0)
        vma->vm_ops = &map_vm_ops;
    else
    {
        printk(PRINTK_TAG "[%s] offset out of range.\n", __func__);
        return -ENXIO;
    }

    return 0;
}

static int mapdrv_open(struct inode *inoe, struct file *file)
{
    printk(PRINTK_TAG "[%s] process: %s(%d)\n", __func__, current->comm, current->pid);
    return 0;
}

void map_vopen(struct vm_area_struct *vma)
{
    printk(PRINTK_TAG "[%s] mapping vma is opened.\n", __func__);
}

void map_vclose(struct vm_area_struct *vma)
{
    printk(PRINTK_TAG "[%s] mapping vma is closed.\n", __func__);
}

// PageFault handler
static vm_fault_t map_fault(struct vm_fault *vmf)
{
    struct page *page;
    void *page_ptr;
    unsigned long offset = vmf->address - vmf->vma->vm_start;
    unsigned long pfn_start;
    unsigned long virt_start = (unsigned long)vmalloc_area + (unsigned long)(vmf->pgoff << PAGE_SHIFT);
    page_ptr = NULL;

    if ((vmf->vma == NULL) || (vmalloc_area == NULL))
    {
        printk(PRINTK_TAG "[%s] return VM_FAULT_SIGBUS!\n", __func__);
        return VM_FAULT_SIGBUS;
    }
    if (offset >= MAPLEN)
    {
        printk(PRINTK_TAG "[%s] return VM_FAULT_SIGBUS!\n", __func__);
        return VM_FAULT_SIGBUS;
    }

    page_ptr = vmalloc_area + offset;
    page = vmalloc_to_page(page_ptr);
    pfn_start = vmalloc_to_pfn(page_ptr);
    get_page(page);
    vmf->page = page;

    printk(PRINTK_TAG "[%s] map 0x%lx(0x%016lx) to 0x%lx, size: 0x%lx, page: %ld.\n",
           __func__, virt_start, pfn_start << PAGE_SHIFT, vmf->address, PAGE_SIZE, vmf->pgoff);
    return 0;
}

MODULE_LICENSE("GPL");
module_init(mapdrv_init);
module_exit(mapdrv_exit);
