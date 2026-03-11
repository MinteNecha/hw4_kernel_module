#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/kernel.h>

MODULE_AUTHOR("MZN");
MODULE_DESCRIPTION("Simple LKM");
MODULE_LICENSE("Dual MIT/GPL");

int intOne = 0;
int intTwo = 0;
static int intArray[2] = {0,0};
//static int argc = 0;
static char msg[256] = {0};
static char *cmd_arg = "Default";


module_param(cmd_arg, charp, S_IRUGO);
#define DEVICE_NAME "charDevice"

static int Major;

module_param(intOne, int, 0);
module_param(intTwo, int, 0);
//module_param_array(intArray, int, &argc, 0000);

static ssize_t dev_read(struct file *fileptr, char __user *buffer, size_t len, loff_t *offset){
	char out[512];
	int size = sprintf(out, "LKM Merge: %s + %s\n", cmd_arg, msg);
	if(*offset >= size) return 0;
	if(copy_to_user(buffer, out, size)) return -EFAULT;
	*offset += size;
	return size;
}

static ssize_t dev_write(struct file *fileptr, const char __user *buffer, size_t len, loff_t *offset){
	int size = (len < 256) ? len : 255;
	if(copy_from_user(msg, buffer, size)) return -EFAULT;
	msg[size] = '\0';
	return len;
}

static struct file_operations fops = {
        .read = dev_read,
        .write = dev_write
};


MODULE_PARM_DESC(intOne, "First description");
MODULE_PARM_DESC(intOne, "First description");

static int __init lkm_init(void){
	Major = register_chrdev(0, DEVICE_NAME, &fops);
        if(Major<0){
                printk("Failed to register char device");
                return Major;
        }
        printk("Welcome Major number: %i \n", Major);
        return 0;
}

static void __exit lkm_exit(void){
	unregister_chrdev(Major, DEVICE_NAME);
        printk("Goodbye \n");
}

module_init(lkm_init);
module_exit(lkm_exit);


