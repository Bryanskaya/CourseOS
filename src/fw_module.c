#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h> 
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/cdev.h> 
#include <linux/device.h>
#include <linux/types.h>


#include <linux/fcntl.h>
#include <linux/delay.h>
#include <linux/syscalls.h>

#include <linux/miscdevice.h>
#include <linux/stat.h>

#include <linux/string.h>

#include "fw.h"


#define DEVICE_MAJOR_NUMBER     100
#define BUF_LEN                 200

#define IPPROTO_TCP             6
#define IPPROTO_UDP             17


#define IP_POS(ip, pos) (ip >> ((8 * (3 - pos))) & 0xFF)


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Bryanskaya Ekaterina <bryanskayakatya@yandex.ru>");

int major;
struct class *memory_class;

struct list_head in_list;
struct list_head out_list;

struct rule_item {
    struct fw_rule rule;
    struct list_head list;    
};



ssize_t fw_read(struct file *filp, char __user *buff, size_t count, loff_t *f_pos)
{
    return 0;
}

ssize_t fw_write(struct file *filp, const char __user *buff, size_t count, 
    loff_t *f_pos)
{
    printk(KERN_INFO ">>> FIREWALL: func write was called");

    return 0;
}

int fw_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO ">>> FIREWALL: associated char device was opened");

    return 0;
}

int fw_release(struct inode *inode, struct file *file)
{
    printk(KERN_INFO ">>> FIREWALL: associated char device was closed");

    return 0;
}

char* str_rule(struct fw_rule *rule)
{
    int count_bytes = 0;

    char *res = kmalloc(BUF_LEN, GFP_KERNEL);
    if (!res)
    {
        printk(KERN_INFO "FIREWALL: error in formating rule");
        return NULL;
    }

    if (rule->src_ip != NOT_STATED)
    {
        count_bytes = snprintf(res, 30, "scp_ip: %u.%u.%u.%u \t ", IP_POS(rule->src_ip, 3), 
                                          IP_POS(rule->src_ip, 2),
                                          IP_POS(rule->src_ip, 1),
                                          IP_POS(rule->src_ip, 0));

        /*strcat(res, "scp_ip: ");
        strcat(res, IP_POS(rule->src_ip, 3));
        strcat(res, ".");
        strcat(res, str(IP_POS(rule->src_ip, 2)));
        strcat(res, ".");
        strcat(res, str(IP_POS(rule->src_ip, 1)));
        strcat(res, ".");
        strcat(res, str(IP_POS(rule->src_ip, 0)));
        strcat(res, " ");*/
    }

    if (rule->src_port != NOT_STATED)
    {
        count_bytes += snprintf(res + count_bytes, 20, "src_port: %u \t ", rule->src_port);

        /*strcat(res, "src_port: ");
        strcat(res, rule->src_port);
        strcat(res, " ");*/
    }

    if (rule->dest_ip != NOT_STATED)
    {
        count_bytes += snprintf(res + count_bytes, 30, "dest_ip: %u.%u.%u.%u \t ",
                                IP_POS(rule->dest_ip, 3),
                                IP_POS(rule->dest_ip, 2),
                                IP_POS(rule->dest_ip, 1),
                                IP_POS(rule->dest_ip, 0));

        /*strcat(res, "dest_ip: ");
        strcat(res, str(IP_POS(rule->dest_ip, 3)));
        strcat(res, ".");
        strcat(res, str(IP_POS(rule->dest_ip, 2)));
        strcat(res, ".");
        strcat(res, str(IP_POS(rule->dest_ip, 1)));
        strcat(res, ".");
        strcat(res, str(IP_POS(rule->dest_ip, 0)));
        strcat(res, " ");*/
    }

    if (rule->dest_port != NOT_STATED)
    {
        count_bytes += snprintf(res + count_bytes, 20, "dest_port: %u \t ", rule->dest_port);


        /*strcat(res, "dest_port: ");
        strcat(res, rule->dest_port);
        strcat(res, " ");*/
    }

    if (rule->protocol != NOT_STATED)
    {
        if (rule->protocol == IPPROTO_TCP)
            snprintf(res + count_bytes, 20, "protocol: TCP");
        else if (rule->protocol == IPPROTO_UDP)
            snprintf(res + count_bytes, 20, "protocol: UDP");

        /*strcat(res, "protocol: ");
        strcat(res, rule->protocol);*/
    }

    return res;
}

static void add_rule(struct fw_rule *rule)
{
    struct rule_item *node = (struct rule_item *)kmalloc(sizeof(struct rule_item), GFP_KERNEL);
    if (node == NULL)
    {
        printk(KERN_INFO ">>> FIREWALL: addition a new rule was failed");
        return;
    }

    node->rule = *rule;

    if (node->rule.in == IN)
    {
        list_add_tail(&node->list, &in_list);
        printk(KERN_INFO ">>> FIREWALL: new rule (in) was added");
    }
    else
    {
        list_add_tail(&node->list, &out_list);
        printk(KERN_INFO ">>> FIREWALL: new rule (out) was added");
    }

    printk(KERN_INFO ">>> FIREWALL: new rule was added. Rule: %s", str_rule(&(node->rule)));
}

static void del_rule(struct fw_rule *rule)
{
    printk(KERN_INFO ">>> Delete rule was called");
}


static struct file_operations fw_fops = {
    .owner = THIS_MODULE,
    .read = fw_read,
    .write = fw_write,
    .open = fw_open,
    .release = fw_release,
};

struct miscdevice dev = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = DEVICE_FNAME,
    .fops = &fw_fops,
    .mode = S_IRWXU | S_IWGRP | S_IWOTH | S_IROTH,
};

static int __init fw_init(void)
{
    int res = 0;

    res = misc_register(&dev);
    if (res)
    {
        printk(KERN_INFO ">>> FIREWALL: registration was failed");
        return res;
    }

    INIT_LIST_HEAD(&in_list);
    INIT_LIST_HEAD(&out_list);

    printk(KERN_INFO ">>> FIREWALL was loaded. Major number of char device %s is 10, minor is %d",
            DEVICE_FNAME, dev.minor);

    return res;
}


static void __exit fw_exit(void)
{
    misc_deregister(&dev);

    printk(KERN_INFO ">>> FIREWALL unloaded!\n");
}


module_init(fw_init);
module_exit(fw_exit);