#include <linux/init.h>
#include <linux/module.h>

#include <linux/kernel.h>
/*注册设备节点的文件结构体*/
#include <linux/fs.h>
/*Linux 中申请GPIO的头文件*/
#include <mach/gpio.h>
/*三星平台的GPIO配置函数头文件*/
/*三星平台EXYNOS系列平台，GPIO配置参数宏定义头文件*/
#include <plat/gpio-cfg.h>
/*注册杂项设备的头文件*/
#include <linux/miscdevice.h>
/*驱动注册的头文件，包含驱动的结构体和注册和卸载的函数 platform_match*/
#include <linux/platform_device.h>
//#include <mach/gpio-bank.h>
#include <mach/regs-gpio.h>
#include <asm/io.h>
#include <linux/regulator/consumer.h>
//#include "gps.h"
#include <linux/delay.h>

#define MYDRIVER_NAME "hello_ctl"
static int major = 248;  
static int minor=0;  
static dev_t devno;  
static struct class *cls;  
static struct device *test_device;  

volatile unsigned long *GPL2CON,*GPL2DAT,*GPL2PUD;
volatile unsigned long *GPK1CON,*GPK1DAT,*GPK1PUD;
volatile unsigned long virt_addr,phys_addr;
volatile unsigned long virt_addr_gpk,phys_addr_gpk;
static void led_init_con(void)
{
	/*GPL2_0*/
	//配置GPL2CON[3:0]=1 GPL2CON(0)设置为输出
	*GPL2CON  &= 0xfffffff1;//CON为32位寄存器，查看规格书，GPL2CON等寄存器定义
	*GPL2CON  |= 0x00000001;
	//GPL2PUD寄存器，GPL2PUD[1:0]=3,上拉模式
	//*GPL2PUD |=0x0003;
	
	/*GPK1_1*/
	*GPK1CON &= 0xffffff1f; //GPK1CON[7:4]=1 32位寄存器
	*GPK1CON |= 0x00000010;
	//*GPK1PUD |= 0x000c;		//GPK1PUD[3:2]=3 16位寄存器
}
void led_on(void)  
{  
	printk("<0>""led open!\r\n");
	*GPL2DAT |= 0x01;//0000 0001
	*GPK1DAT |= 0x02;//0000 0010
}  
  
void led_off(void)  
{
	printk("<0>""led off!\r\n");
	*GPL2DAT &= 0xfe;//1111 1110
	*GPK1DAT &= 0xfd;//1111 1101
}  
  
static void led_unmap(void)  
{  
	printk("<0>""led unmap!\r\n");
    iounmap(GPL2CON);  
    iounmap(GPL2DAT); 	

	iounmap(GPK1CON);  
    iounmap(GPK1DAT); 	
}  

static int hello_open(struct inode *inode,struct file *filp)
{
	printk("Device Opened Success!\n");
	return 0;
}

static long hello_ioctl(struct file *files,unsigned int cmd,unsigned long arg){
	printk("Cmd is %d\n",cmd);

	switch(cmd){  
        case 0: {
			printk("<0>""command is 0\r\n");		
            led_on();
            break;  
			}
			case 1:{ 
			printk("<0>""command is 1\r\n");
          	led_off();  
            break; 
			} 
        default:{  
			printk("<0>para error\r\n");
			return -EINVAL;
		}
    }
	return 0;
}

static struct file_operations hello_ops = {
	.owner 	= THIS_MODULE,
	.open 	= hello_open,
	.unlocked_ioctl = hello_ioctl,
};

static int hello_probe(struct platform_device *pdev){
	int ret; 
	printk("Hello_Probe\n");

	phys_addr = 0x11000100;//0x11000100是GPL2CON的物理地址
	virt_addr =(unsigned long)ioremap(phys_addr,0x10);
	GPL2CON = (unsigned long *)(virt_addr+0x00);//指定需要操作的寄存器地址
	GPL2DAT = (unsigned long *)(virt_addr+0x04);
	
	phys_addr_gpk = 0x11000060;
	virt_addr_gpk =(unsigned long)ioremap(phys_addr_gpk,0x10);
	GPK1CON = (unsigned long *)(virt_addr_gpk+0x00);
	GPK1DAT = (unsigned long *)(virt_addr_gpk+0x04);

	devno = MKDEV(major,minor); //获取设备号 
	ret = register_chrdev(major,MYDRIVER_NAME,&hello_ops); //注册设备 
  
    cls = class_create(THIS_MODULE, "myclass");  //创建设备类 platform_device_register
    if(IS_ERR(cls))  
    {  
        unregister_chrdev(major,MYDRIVER_NAME);  
        return -EBUSY;  
    }  
    test_device = device_create(cls,NULL,devno,NULL,MYDRIVER_NAME);//创建设备节点 mknod /dev/hello  
	if(IS_ERR(test_device))  
    {  
        class_destroy(cls);  
        unregister_chrdev(major,MYDRIVER_NAME);  
        return -EBUSY;  
    }  
	led_init_con();  
	led_on();
	return 0;
		
}
static int hello_remove(struct platform_device *pdev){
	printk("hello_remove\n");
	led_unmap();  
    device_destroy(cls,devno);  
    class_destroy(cls);   
    unregister_chrdev(major,"led_daniel");  
	printk("<0>""ledremove ok!\r\n"); 
	return 0;
}

static struct platform_driver hello_driver = {
	.probe  = hello_probe,
	.remove = __devexit_p(hello_remove),  
	.driver = {
		.name = MYDRIVER_NAME,
		.owner =THIS_MODULE,
	},
};
static int __init LED_Init(void)
{
	 printk("Hello_LED_Init\n");
	 platform_driver_register(&hello_driver);
	 return 0;
}
static void __exit LED_Exit(void)
{
	printk("Hello_LED_Exit\n");
	platform_driver_unregister(&hello_driver);
}
module_init(LED_Init);
module_exit(LED_Exit);
MODULE_LICENSE("Dual BSD/GPL");





