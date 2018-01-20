#include<linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h> 
#include <linux/interrupt.h>
#include <linux/irq.h> 
#include <mach/gpio.h>
#include <plat/gpio-cfg.h>
#include <linux/miscdevice.h>
#include <linux/platform_device.h>
#include <mach/regs-gpio.h>
#include <asm/io.h>
#include <mach/gpio-exynos4.h>


#include <linux/regulator/consumer.h>
#include <linux/delay.h>


static unsigned int major = 248;
#define MYDEVICENAME	"iKey"
static dev_t devno;  
static struct class *cls;  
static struct device *test_device;  



static irqreturn_t buttons_irq(int irq, void *dev_id)
{	
	printk("buttons_irq.");
	
	return IRQ_RETVAL(IRQ_HANDLED);

}/*platform_get_resource	IORESOURCE_IRQ*/

static int KeyIrqOpen(struct inode * inode, struct file *file){
		return 0;
}
static ssize_t KeyIrqRead(struct file *file, char __user *user, size_t size, loff_t *loff){


	return 0;
}

static int KeyIrqClose(struct inode *inode, struct file *file){

	//free_irq(IRQ_EINT9, 1);
	return 0;
}

static struct file_operations KeyIrqOpr = {
	.owner	 = THIS_MODULE,
	.open 	 = KeyIrqOpen, 
	.read    = KeyIrqRead,
	.release = KeyIrqClose,
};

static int __init KeyIrqInit(void){
	int ret;
	devno = MKDEV(major,0); 
	ret = register_chrdev(major,MYDEVICENAME,&KeyIrqOpr);
	cls = class_create(THIS_MODULE, "iKeyInit");  //创建设备类 platform_device_register
	if(IS_ERR(cls))  {  
			unregister_chrdev(major,MYDEVICENAME);  
			return -EBUSY;	
	}  

	test_device = device_create(cls,NULL,devno,NULL,MYDEVICENAME);//创建设备节点 mknod /dev/hello  
	if(IS_ERR(test_device)){  
			class_destroy(cls);  
			unregister_chrdev(major,MYDEVICENAME);  
			return -EBUSY;	
	}  
	/*gpio_request(EXYNOS4_GPX1(1),"EINT9");
	s3c_gpio_cfgpin(EXYNOS4_GPX1(1),S3C_GPIO_SFN(0xF));
	s3c_gpio_setpull(EXYNOS4_GPX1(1),S3C_GPIO_PULL_UP);
	gpio_free(EXYNOS4_GPX1(1));

	gpio_request(EXYNOS4_GPX1(2),"EINT10");
	s3c_gpio_cfgpin(EXYNOS4_GPX1(2),S3C_GPIO_SFN(0xF));
	s3c_gpio_setpull(EXYNOS4_GPX1(2),S3C_GPIO_PULL_UP);
	gpio_free(EXYNOS4_GPX1(2));
	*/
	ret = request_irq(IRQ_EINT(9),buttons_irq, IRQ_TYPE_EDGE_RISING,"K1",1);
	if(ret < 0){
		printk("request_irq error.\n");
		return -1;
	}

	ret = request_irq(IRQ_EINT(10),buttons_irq, IRQ_TYPE_EDGE_RISING,"K2",2);
	if(ret < 0){
		printk("request_irq error.\n");
		return -1;
	}
	return 0;
}

static void __exit KeyIrqExit(void){
			class_destroy(cls);  
			unregister_chrdev(major,MYDEVICENAME);  
}

module_init(KeyIrqInit);
module_exit(KeyIrqExit);
MODULE_LICENSE("Dual BSD/GPL");

