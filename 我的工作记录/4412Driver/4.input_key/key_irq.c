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
#include <linux/input.h>

static unsigned int major = 248;
#define MYDEVICENAME	"iKey"
static dev_t devno;  
static struct class *cls;  
static struct device *test_device;  

static struct input_dev *button_dev;   /*输入设备结构体*/

struct iKeyPin
{
	int Pin;
	int Flag;
	char Event;
};

static struct iKeyPin iButton[2] = {
	{IRQ_EINT(9),1,KEY_1},{IRQ_EINT(10),2,KEY_2}
};

static irqreturn_t buttons_irq(int irq, void *dev_id)
{
	struct iKeyPin *KeyTmp	= (struct iKeyPin *)dev_id;
	int dome = 0;
	switch(KeyTmp->Flag){
		case 1:
			dome = 2;
		       printk("KEY1\n");
		       break;
		case 2:
			dome = 3;
		       printk("KEY2\n");
			       break;
		}
	input_event(button_dev, EV_KEY, KeyTmp->Event,dome);  
	input_sync(button_dev);    /*通知接收者,一个报告发送完毕*/
	return IRQ_RETVAL(IRQ_HANDLED);
}
/*platform_get_resource	IORESOURCE_IRQ*/

static int KeyIrqOpen(struct inode * inode, struct file *file){

	return 0;
}
static ssize_t KeyIrqRead(struct file *file, char __user *user, size_t size, loff_t *loff){

	return 0;
}

static int KeyIrqClose(struct inode *inode, struct file *file){

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
	/*
	gpio_request(EXYNOS4_GPX1(1),"EINT9");
	s3c_gpio_cfgpin(EXYNOS4_GPX1(1),S3C_GPIO_SFN(0xF));
	s3c_gpio_setpull(EXYNOS4_GPX1(1),S3C_GPIO_PULL_UP);
	gpio_free(EXYNOS4_GPX1(1));

	gpio_request(EXYNOS4_GPX1(2),"EINT10");
	s3c_gpio_cfgpin(EXYNOS4_GPX1(2),S3C_GPIO_SFN(0xF));
	s3c_gpio_setpull(EXYNOS4_GPX1(2),S3C_GPIO_PULL_UP);
	gpio_free(EXYNOS4_GPX1(2));
	*/
	ret = request_irq(iButton[0].Pin,buttons_irq,IRQ_TYPE_EDGE_RISING,"K1",&iButton[0]);
	if(ret < 0){
		printk("request_irq error.\n");
		return -1;
	}
	ret = request_irq(iButton[1].Pin,buttons_irq,IRQ_TYPE_EDGE_RISING,"K2",&iButton[1]);
	if(ret < 0){
		printk("request_irq error.\n");
		return -1;
	}
	 button_dev = input_allocate_device();     /*分配一个设备结构体*/
	 if (!button_dev){
			printk(KERN_ERR "button.c: Not enough memory\n");
			free_irq(iButton[0].Pin,&iButton[0]);
			free_irq(iButton[1].Pin,&iButton[1]);
			device_destroy(cls,devno);
			class_destroy(cls); 
			unregister_chrdev(major,MYDEVICENAME);  
			return -1;
	}

	// button_dev->evbit[0] = BIT_MASK(EV_KEY);    /*设置按键信息*/
    // button_dev->keybit[BIT_WORD(BTN_0)] = BIT_MASK(BTN_0);
 
 // 2. 设置input_dev  
 // 2.1 能产生 哪类 事件    
	 button_dev->evbit[0] = BIT(EV_KEY);  

	 // 2.2 能产生 哪些 事件  
	__set_bit(KEY_2, button_dev->keybit);  
	__set_bit(KEY_1, button_dev->keybit);  
	ret = input_register_device(button_dev);      /*注册一个输入设备*/
	if (ret){
	    printk(KERN_ERR "button.c: Failed to register device\n");
	    free_irq(iButton[0].Pin,&iButton[0]);
		free_irq(iButton[1].Pin,&iButton[1]);
		device_destroy(cls,devno);
		class_destroy(cls); 
		unregister_chrdev(major,MYDEVICENAME); 
		input_free_device(button_dev);
	    return -1;
 	}
	return 0;
}

static void __exit KeyIrqExit(void){
			free_irq(iButton[0].Pin,&iButton[0]);
			free_irq(iButton[1].Pin,&iButton[1]);
			device_destroy(cls,devno);
			class_destroy(cls); 
			unregister_chrdev(major,MYDEVICENAME); 
			input_unregister_device(button_dev);   
}

module_init(KeyIrqInit);
module_exit(KeyIrqExit);
MODULE_LICENSE("Dual BSD/GPL");

