#include <linux/module.h>  
#include <linux/fs.h>  
#include <linux/cdev.h>  
#include <linux/device.h>  
#include <linux/platform_device.h>  
#include <asm/io.h>  
 
#include <plat/gpio-cfg.h>
#include <mach/regs-gpio.h> 
#include <mach/gpio.h>
#include <linux/regulator/consumer.h>
#include <mach/gpio-exynos4.h>
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
	*GPL2PUD |=0x0003;
	
	/*GPK1_1*/
	*GPK1CON &= 0xffffff1f; //GPK1CON[7:4]=1 32位寄存器
	*GPK1CON |= 0x00000010;
	*GPK1PUD |= 0x000c;		//GPK1PUD[3:2]=3 16位寄存器
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
	iounmap(GPL2PUD); 	

	iounmap(GPK1CON);  
    iounmap(GPK1DAT); 
	iounmap(GPK1PUD); 	
}  
static int led_open (struct inode *inode, struct file *filep)  
{  
	printk("<0>""led open!\r\n");  
	//led_on();
    return 0;  
}  
  
static int led_release(struct inode *inode, struct file *filep)  
{  
	printk("<0>""led release!\r\n");
	//led_off();
     return 0;  
}    
static long led_ioctl(struct file *filep, unsigned int cmd, unsigned long arg)  
{  
//接收来自应用层的参数；
//filep文件指针
//cmd 第一个参数
//arg 第二个参数
	printk("<0>""going to ioctl!\r\n");
	printk("<0>""cmd=%d\r\n",cmd);
	printk("<0>""arg=%d\r\n",arg);
    switch(cmd)  
    {  
        case 0: {
			printk("<0>""command is 0\r\n");		
           led_on();  
            break;  }
        case 1:  {
			printk("<0>""command is 1\r\n");
           led_off();  
            break;  }
        default :  
		{
			printk("<0>para error\r\n");
			
			return -EINVAL; 
		}
             
    }
	if(arg>2) return -EINVAL;
	else {
		;
		
	}//gpio_set_value(led_gpios[arg], cmd);	
	printk("<0>""finished\r\n");
    return 0;  
}  
  
static struct file_operations led_ops=  
{  
    .open     	= led_open,  
	.write 		= led_open,
    .release 	= led_release, 
	.unlocked_ioctl      = led_ioctl,  
};  
/*
static int led_probe_(struct platform_device *pdev)  
{
	struct resource	*res;
	printk("<0>""led_probe matching!\r\n"); 
	// 根据platform_device的资源进行ioremap /
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	GPL2CON = ioremap(res->start, res->end - res->start + 1);
	GPL2DAT = GPL2CON + 4;
	res = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	GPK1CON = ioremap(res->start, res->end - res->start + 1);
	GPK1PUD = GPK1CON+4;
	// 注册字符设备驱动程序 /
	printk("<0>""led_probe, found led\n");
	major = register_chrdev(0, "led_daniel", &led_ops);
	cls = class_create(THIS_MODULE, "led_daniel");
	class_device_create(cls, NULL, MKDEV(major, minor), NULL, "led_daniel"); //dev/led 
}
*/
static int led_probe(struct platform_device *pdev)//former  
{  
    int ret,i; 
	int *p;	
//	printk("<0>""%s%s%d\n",_FILE_,_FUNCTION_,_LINE_);
    printk("<0>""led_probe matching!\r\n");  
	// p=(int *)0x0000;
	// *p=100;
	phys_addr = 0x11000100;//0x11000100是GPL2CON的物理地址
	virt_addr =(unsigned long)ioremap(phys_addr,0x10);
	GPL2CON = (unsigned long *)(virt_addr+0x00);//指定需要操作的寄存器地址
	GPL2DAT = (unsigned long *)(virt_addr+0x04);
	GPL2PUD	= (unsigned long *)(virt_addr+0x08);

	phys_addr_gpk = 0x11000060;
	virt_addr_gpk =(unsigned long)ioremap(phys_addr_gpk,0x10);
	GPK1CON = (unsigned long *)(virt_addr_gpk+0x00);
	GPK1DAT = (unsigned long *)(virt_addr_gpk+0x04);
	GPK1PUD	= (unsigned long *)(virt_addr_gpk+0x08);
	
    devno = MKDEV(major,minor); //获取设备号 
	
    ret = register_chrdev(major,"led_daniel",&led_ops); //注册设备 
  
    cls = class_create(THIS_MODULE, "myclass");  //创建设备类
    if(IS_ERR(cls))  
    {  
        unregister_chrdev(major,"led_daniel");  
        return -EBUSY;  
    }  
    test_device = device_create(cls,NULL,devno,NULL,"led_daniel");//创建设备节点 mknod /dev/hello  
    /*
	在驱动初始化的代码里调用class_create(...)为该设备创建一个class，
	再为每个设备调用device_create(...)创建对应的设备。
    内核中定义的struct class结构体，顾名思义，一个struct class结构体类型变量对应一个类，
	内核同时提供了class_create(…)函数，可以用它来创建一个类，这个类存放于sysfs下面，
	一旦创建好了这个类，再调用 device_create(…)函数来在/dev目录下创建相应的设备节点。
     这样，加载模块的时候，用户空间中的udev会自动响应 device_create()函数，
	 去/sysfs下寻找对应的类从而创建设备节点。
	*/
	
	if(IS_ERR(test_device))  
    {  
        class_destroy(cls);  
        unregister_chrdev(major,"led_daniel");  
        return -EBUSY;  
    }  
     led_init_con();  
	 led_on();
	 printk("<0>""match ok!\r\n"); 
    return 0;  
}  
  
static int led_remove(struct platform_device *pdev)  
{  
	led_unmap();  
    device_destroy(cls,devno);  
    class_destroy(cls);   
    unregister_chrdev(major,"led_daniel");  
	printk("<0>""ledremove ok!\r\n"); 
    return 0;  
}  
  
  
static struct platform_driver led_driver=  
{  
    .driver.name = "danieldev",  
    .probe = led_probe,  
    .remove = led_remove,  
};  
   
  
static int led_init(void)  
{  
    printk("<0>""led_init\r\n");  
      
    return platform_driver_register(&led_driver);  
	/*
	1. 将driver结构体放入bus的driver链表
	2. 从bus的dev链表取出每一个dev，用bus的match函数判断dev能否支持这个drv
	3. 若支持就调用驱动的probe
	问: bus的match如何判断dev支持drv呢？
	答: 在\linux_dir\drivers\base\bus.c的driver_helper函数:
	if (strcmp(name, dev->bus_id) == 0)  return 1;
	分析代码知match函数是根据device的bus_id和driver的name是否一致来匹配的
	device_add和driver_register都会两两比较两者的bus_id或name，如果一样就
	调用driver的probe
	*/
}  
  
static void led_exit(void)  
{  
    printk("<0>""led_exit\r\n");  
    platform_driver_unregister(&led_driver);  
      
    return;  
}  
  
  
MODULE_LICENSE("GPL");  
module_init(led_init);  
module_exit(led_exit); 