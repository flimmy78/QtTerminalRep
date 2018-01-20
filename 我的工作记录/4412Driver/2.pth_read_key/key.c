#include <linux/init.h>
#include <linux/module.h>

#include <linux/kernel.h>
#include <linux/fs.h>
#include <mach/gpio.h>
#include <plat/gpio-cfg.h>
#include <linux/miscdevice.h>
#include <linux/platform_device.h>
#include <mach/regs-gpio.h>
#include <asm/io.h>
#include <linux/regulator/consumer.h>
#include <linux/delay.h>
#define MYDRIVERBUTTON "iButton"

static int major = 248;   
static dev_t devno;  
static struct class *cls;  
static struct device *test_device;
static unsigned long viraddr;
static unsigned long *GPX3CON;
static unsigned long *GPX3DAT;
//GPX3_3->0x1100_0000+0x0C60

static int iButtonOpen(struct inode *inode, struct file *file){
	*GPX3CON &= ~(0xF<<8); 
	return 0;
}

static ssize_t iButtonRead(struct file *file, char __user *user, size_t size, loff_t *leek){
	unsigned char key_vals[1]={0};
	int val;
	val = *GPX3DAT;
	key_vals[0] = val & (0x01 << 3) ? 1 : 0;
	copy_to_user(user,key_vals, sizeof(key_vals)); 
	return 0;
}

static int iButtonClose(struct inode *inode, struct file *file){
	printk("<0>""iButtonRelease unmap!\r\n");

	return 0;
}


static struct file_operations iButton_drv = {
	.open = iButtonOpen,
	.read = iButtonRead,
	.release = iButtonClose,
};

static int __init Button_Init(void ){
	int ret;
	devno = MKDEV(major,0); 
	ret = register_chrdev(major,MYDRIVERBUTTON,&iButton_drv); 
  
    cls = class_create(THIS_MODULE, "myclass");  
    if(IS_ERR(cls))  
    {  
        unregister_chrdev(major,MYDRIVERBUTTON);  
        return -EBUSY;  
    }  
    test_device = device_create(cls,NULL,devno,NULL,MYDRIVERBUTTON);
	if(IS_ERR(test_device))  
    {  
        class_destroy(cls);  
        unregister_chrdev(major,MYDRIVERBUTTON);  
        return -EBUSY;  
    }  

    viraddr = (unsigned long)ioremap(0x1100C60,0x10);
	GPX3CON = (unsigned long *)viraddr;
	GPX3DAT = GPX3CON+1;
	return 0;
}

static void __exit Button_Exit(void ){
	 iounmap((unsigned long *)viraddr);
	unregister_chrdev(major,MYDRIVERBUTTON); 
	device_destroy(cls, devno);
	class_destroy(cls); 
	
}

module_init(Button_Init);
module_exit(Button_Exit);
MODULE_LICENSE("Dual BSD/GPL");

