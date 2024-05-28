#include <linux/atomic.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/slab.h>

#define BUF_SIZE 256

typedef struct lnode {
    struct lnode *next;
    int value;
} lnode_t;

static dev_t first;
static struct cdev c_dev;
static struct class *cl;
static lnode_t *linked_list = NULL;

char ibuf[BUF_SIZE];

lnode_t *create_node(int value)
{
    pr_info("Creating node with value: %d", value);
    lnode_t *ans = kmalloc(sizeof(lnode_t), GFP_KERNEL);
    ans->value = value;
    return ans;
}

static int my_open(struct inode *i, struct file *f)
{
    printk(KERN_INFO "Driver: open()\n");
    return 0;
}

static int my_close(struct inode *i, struct file *f)
{
    printk(KERN_INFO "Driver: close()\n");
    return 0;
}

static ssize_t my_read(struct file *f, char __user *buf, size_t len,
                       loff_t *off)
{
    int count = strlen(ibuf);
    printk(KERN_INFO "Driver: read()\n");

    if (*off > 0 || len < count) {
        return 0;
    }

    lnode_t *now = linked_list;

    char output[256];
    output[0] = '\0';
    while (now != NULL) {
        char int_to_str[10];
        sprintf(int_to_str, "%d ", now->value);
        strncat(output, int_to_str, strlen(int_to_str));
        now = now->next;
    }
    strncat(output, "\n", 1);

    pr_info("Ans: %s", output);
    size_t output_len = strlen(output);
    if (copy_to_user(buf, output, output_len) != 0) {
        return -EFAULT;
    }

    *off = output_len;
    return output_len;
}

static ssize_t my_write(struct file *f, const char __user *buf, size_t len,
                        loff_t *off)
{
    printk(KERN_INFO "Driver: write()\n");

    if (len > BUF_SIZE)
        return 0;

    if (copy_from_user(ibuf, buf, len) != 0) {
        return -EFAULT;
    }
    if (len > 0) {
        ibuf[len - 1] = '\0';
    }

    printk(KERN_INFO "Len %d, Message: '%s'", len, ibuf);
    int readed_len = strlen(ibuf);

    int count_spaces = 0;
    int i = 0;
    for (i = 0; i < readed_len; i++) {
        if (ibuf[i] == ' ') {
            ++count_spaces;
        }
    }
    pr_info("Spaces: %d", count_spaces);

    if (linked_list == NULL) {
        linked_list = create_node(count_spaces);
        pr_info("Root node value: %d", linked_list->value);
    } else {
        lnode_t *now_node = linked_list;
        while (now_node->next != NULL) {
            now_node = now_node->next;
        }
        now_node->next = create_node(count_spaces);
    }

    return len;
}

static struct file_operations mychdev_fops = { .owner = THIS_MODULE,
                                               .open = my_open,
                                               .release = my_close,
                                               .read = my_read,
                                               .write = my_write };

static int __init ch_drv_init(void)
{
    printk(KERN_INFO "Hello!\n");
    if (alloc_chrdev_region(&first, 0, 1, "ch_dev") < 0) {
        return -1;
    }

    #if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 4, 0)
        cl = class_create("chardrv");
    #else
        cl = class_create(THIS_MODULE, "chardrv");
    #endif

    if (cl == NULL) {
        unregister_chrdev_region(first, 1);
        return -1;
    }

    if (device_create(cl, NULL, first, NULL, "var4") == NULL) {
        class_destroy(cl);
        unregister_chrdev_region(first, 1);
        return -1;
    }

    cdev_init(&c_dev, &mychdev_fops);
    if (cdev_add(&c_dev, first, 1) == -1) {
        device_destroy(cl, first);
        class_destroy(cl);
        unregister_chrdev_region(first, 1);
        return -1;
    }
    return 0;
}

static void __exit ch_drv_exit(void)
{
    lnode_t *now_node = linked_list;
    while (now_node != NULL) {
        lnode_t *next = now_node->next;
        kfree(now_node);
        now_node = next;
    }

    cdev_del(&c_dev);
    device_destroy(cl, first);
    class_destroy(cl);
    unregister_chrdev_region(first, 1);
    printk(KERN_INFO "Bye!!!\n");
}

module_init(ch_drv_init);
module_exit(ch_drv_exit);

MODULE_LICENSE("WTFPL");
MODULE_AUTHOR("VxDxK & Kyoto");
MODULE_DESCRIPTION("IO-LAB-1 (SYMBOL DRIVER)");
