#include <linux/module.h>  
#include <linux/device.h>  
#include <linux/platform_device.h>  
#include <linux/ioport.h>  
/*
static struct resource led_resource[] = 
{
	[0] ={
			.start = 0x11000100 
			.end = 0x11000100 + 8 - 1, 
			.flags = IORESOURCE_MEM,
		},
	[1] ={
			.start = 0x11000060, 
			.end = 0x11000060+8-1,
			.flags = IORESOURCE_IRQ, 
		}
};*/
static void hello_release(struct device *dev)  
{  
    printk("<0>""hello_release\n");  
    return ;  
}  
static struct platform_device hello_device=  
{  
    .name = "danieldev", //必须和platform_driver内嵌的driver.name一样 
    .id = -1,  
    .dev.release = hello_release, //必须设置，空的也可以 
    // .num_resources = ARRAY_SIZE(led_resource),  
    // .resource = led_resource,  
};  
static int hello_init(void)  
{  
    printk("<0>""hello_init");  
    return platform_device_register(&hello_device);  
}   
static void hello_exit(void)  
{  
    printk("<0>""hello_exit");  
    platform_device_unregister(&hello_device);  
    return;  
}  
MODULE_LICENSE("GPL");  
module_init(hello_init);  
module_exit(hello_exit); 