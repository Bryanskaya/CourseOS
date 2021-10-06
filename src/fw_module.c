#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h> 
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/cdev.h> 
#include <linux/device.h>
#include <linux/types.h>

#include <linux/netfilter_ipv4.h>
#include <linux/netfilter.h>
#include <linux/in.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/udp.h>

#include <linux/fcntl.h>
#include <linux/delay.h>
#include <linux/syscalls.h>

#include <linux/miscdevice.h>
#include <linux/stat.h>

#include <linux/string.h>

#include "fw.h"


#define DEVICE_MAJOR_NUMBER     100
#define BUF_LEN                 200

/*#define IPPROTO_TCP             6
#define IPPROTO_UDP             17*/


#define IP_POS(ip, pos) (ip >> ((8 * (3 - pos))) & 0xFF)


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Bryanskaya Ekaterina <bryanskayakatya@yandex.ru>");

static char *buffer;

struct list_head in_list;
struct list_head out_list;

struct rule_item {
    struct fw_rule rule;
    struct list_head list;    
};


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

    if (rule->in == IN)
        count_bytes += snprintf(res, 10, "IN \t ");
    else if (rule->in == OUT)
        count_bytes += snprintf(res, 10, "OUT \t ");

    if (rule->src_ip != NOT_STATED)
        count_bytes = snprintf(res, 30, "scp_ip: %u.%u.%u.%u \t ", 
                                        IP_POS(rule->src_ip, 3), 
                                        IP_POS(rule->src_ip, 2),
                                        IP_POS(rule->src_ip, 1),
                                        IP_POS(rule->src_ip, 0));

    if (rule->src_port != NOT_STATED)
        count_bytes += snprintf(res + count_bytes, 20, "src_port: %u \t ", ntohs(rule->src_port));

    if (rule->dest_ip != NOT_STATED)
        count_bytes += snprintf(res + count_bytes, 30, "dest_ip: %u.%u.%u.%u \t ",
                                IP_POS(rule->dest_ip, 3),
                                IP_POS(rule->dest_ip, 2),
                                IP_POS(rule->dest_ip, 1),
                                IP_POS(rule->dest_ip, 0));

    if (rule->dest_port != NOT_STATED)
        count_bytes += snprintf(res + count_bytes, 20, "dest_port: %u \t ", ntohs(rule->dest_port));

    if (rule->protocol != NOT_STATED)
    {
        if (rule->protocol == IPPROTO_TCP)
            snprintf(res + count_bytes, 20, "protocol: TCP");
        else if (rule->protocol == IPPROTO_UDP)
            snprintf(res + count_bytes, 20, "protocol: UDP");
    }

    return res;
}


static void add_rule(struct fw_rule *rule)
{
    printk(KERN_INFO ">>> FIREWALL: func add rule was called");

    struct rule_item *node = (struct rule_item *)kmalloc(sizeof(struct rule_item), GFP_KERNEL);
    if (node == NULL)
    {
        printk(KERN_INFO ">>> FIREWALL: addition a new rule was failed");
        return;
    }

    node->rule = *rule;

    if (node->rule.in == IN)
        list_add_tail(&node->list, &in_list);
    else
        list_add_tail(&node->list, &out_list);

    printk(KERN_INFO ">>> FIREWALL: new rule was added. Rule: %s", str_rule(&(node->rule)));
}

static void del_rule(struct fw_rule *rule)
{
    struct list_head *lst;
    struct rule_item *node;

    printk(KERN_INFO ">>> Delete rule was called");

    /*if (rule->in == IN)
        lst = &in_list;
    else
        lst = &out_list;

    for (list_head *temp = lst; temp->next != lst; temp = temp->next)
    {
        node = list_entry(temp->next, struct rule_item, list);
    }*/

    // TODO
}


ssize_t fw_read(struct file *filp, char __user *buff, size_t count, loff_t *f_pos)
{
    static struct list_head *in_lst = &in_list;
	static struct list_head *out_lst = &out_list;
    struct rule_item *node;
    char *read_ptr;

    printk(KERN_INFO ">>> FIREWALL: func read was called");

    if (in_lst->next != &in_list)
    {
        node = list_entry(in_lst->next, struct rule_item, list);
        read_ptr = (char *)&node->rule;
        in_lst = in_lst->next;
    }
    else if (out_lst->next != &out_list)
    {
        node = list_entry(out_lst->next, struct rule_item, list);
        read_ptr = (char *)&node->rule;
        out_lst = out_lst->next;
    }
    else
    {
        in_lst = &in_list;
        out_lst = &out_list;
        
        return 0;
    }
    
    if (copy_to_user(buff, read_ptr, count))
    {
        printk(KERN_INFO ">>> FIREWALL: copy_to_user error");
        return -EFAULT;
    }

    return count;
}

ssize_t fw_write(struct file *filp, const char __user *buff, size_t count, loff_t *f_pos)
{
    struct fw_comm rule_full;

    printk(KERN_INFO ">>> FIREWALL: func write was called");

    if (count < sizeof(struct fw_comm))
    {
        printk(KERN_INFO ">>> FIREWALL: incorrect rule");
        return -EFAULT;
    }

    if (copy_from_user(&rule_full, buff, count))
    {
        printk(KERN_INFO ">>> FIREWALL: copy_from_user error");
        return -EFAULT;
    }

    switch (rule_full.action)
    {
    case ADD:
        add_rule(&rule_full.rule);
        break;
    case DELETE:
        del_rule(&rule_full.rule);
        break;
    
    default:
        printk(KERN_INFO ">>> FIREWALL: unknown command");
        break;
    }

    return 0;
}

/*
static unsigned int filter(void *priv, struct sk_buff *skb, const struct nf_hook_state *state)
{


    return 1;
}*/
/*
* struct sk_buff *skb - socket buffer
*/
static unsigned int fw_in_filter(void *priv, struct sk_buff *skb, const struct nf_hook_state *state)
{
    return 1;
    //return filter(priv, skb, state, &in_list);
}

static unsigned int fw_out_filter(void *priv, struct sk_buff *skb, const struct nf_hook_state *state)
{
    return 1;
    //return filter(priv, skb, state, &out_list);
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

struct nf_hook_ops fw_in_hook_ops = 
{
    .hook = fw_in_filter,
    .pf = PF_INET,
    .hooknum = NF_INET_PRE_ROUTING,
    .priority = NF_IP_PRI_FIRST
};

struct nf_hook_ops fw_out_hook_ops = 
{
    .hook = fw_out_filter,
    .pf = PF_INET,
    .hooknum = NF_INET_LOCAL_OUT,
    .priority = NF_IP_PRI_FIRST
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

    buffer = (char *)kmalloc(sizeof(struct fw_comm*), GFP_KERNEL);
    if (buffer == NULL)
    {
        printk(KERN_INFO ">>> FIREWALL: kmalloc error");
        return -EFAULT;
    }

    INIT_LIST_HEAD(&in_list);
    INIT_LIST_HEAD(&out_list);

    printk(KERN_INFO ">>> FIREWALL was loaded. Major number of char device %s is 10, minor is %d",
            DEVICE_FNAME, dev.minor);

    return res;
}


static void __exit fw_exit(void)
{
    struct rule_item *node;
    struct rule_item *node_temp;

    kfree(buffer);

    list_for_each_entry_safe(node, node_temp, &in_list, list)
    {
        list_del(&node->list);
        kfree(node);
    }

    list_for_each_entry_safe(node, node_temp, &out_list, list)
    {
        list_del(&node->list);
        kfree(node);
    }

    misc_deregister(&dev);

    printk(KERN_INFO ">>> FIREWALL unloaded!\n");
}


module_init(fw_init);
module_exit(fw_exit);