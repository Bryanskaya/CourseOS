#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h> 


#define DEVICE_MAJOR_NUMBER     100
#define DEVICE_FNAME            "fw_file"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Bryanskaya Ekaterina <bryanskayakatya@yandex.ru>");


ssize_t fw_read(struct file *filp, char __user *buff, size_t count, loff_t *f_pos)
{
    return 0;
}

ssize_t fw_write(struct file *filp, const char __user *buff, size_t count, 
    loff_t *f_pos)
{
    return 0;
}

int fw_open(struct inode *inode, struct file *file)
{
    return 0;
}

int fw_release(struct inode *inode, struct file *file)
{
    return 0;
}







struct file_operations fw_fops = {
    .owner = THIS_MODULE,
    .read = fw_read,
    .write = fw_write,
    .open = fw_open,
    .release = fw_release,
};

static int __init fw_init(void)
{
    int res;

    res = register_chrdev(DEVICE_MAJOR_NUMBER, DEVICE_FNAME, &fw_fops);
    if (res < 0)
    {
        printk(KERN_INFO ">>> FIREWALL: registration was failed");
        return res;
    }




    printk(KERN_INFO ">>> FIREWALL was loaded. Major number of char device %s is %d",
            DEVICE_FNAME, DEVICE_MAJOR_NUMBER);

    return 0;
}


static void __exit fw_exit(void)
{
    unregister_chrdev(DEVICE_MAJOR_NUMBER, DEVICE_FNAME);

    printk(KERN_INFO ">>> FIREWALL unloaded!\n");
}


module_init(fw_init);
module_exit(fw_exit);