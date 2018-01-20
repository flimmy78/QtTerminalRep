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
	//����GPL2CON[3:0]=1 GPL2CON(0)����Ϊ���
	*GPL2CON  &= 0xfffffff1;//CONΪ32λ�Ĵ������鿴����飬GPL2CON�ȼĴ�������
	*GPL2CON  |= 0x00000001;
	//GPL2PUD�Ĵ�����GPL2PUD[1:0]=3,����ģʽ
	*GPL2PUD |=0x0003;
	
	/*GPK1_1*/
	*GPK1CON &= 0xffffff1f; //GPK1CON[7:4]=1 32λ�Ĵ���
	*GPK1CON |= 0x00000010;
	*GPK1PUD |= 0x000c;		//GPK1PUD[3:2]=3 16λ�Ĵ���
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
//��������Ӧ�ò�Ĳ�����
//filep�ļ�ָ��
//cmd ��һ������
//arg �ڶ�������
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
	// ����platform_device����Դ����ioremap /
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	GPL2CON = ioremap(res->start, res->end - res->start + 1);
	GPL2DAT = GPL2CON + 4;
	res = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	GPK1CON = ioremap(res->start, res->end - res->start + 1);
	GPK1PUD = GPK1CON+4;
	// ע���ַ��豸�������� /
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
	phys_addr = 0x11000100;//0x11000100��GPL2CON�������ַ
	virt_addr =(unsigned long)ioremap(phys_addr,0x10);
	GPL2CON = (unsigned long *)(virt_addr+0x00);//ָ����Ҫ�����ļĴ�����ַ
	GPL2DAT = (unsigned long *)(virt_addr+0x04);
	GPL2PUD	= (unsigned long *)(virt_addr+0x08);

	phys_addr_gpk = 0x11000060;
	virt_addr_gpk =(unsigned long)ioremap(phys_addr_gpk,0x10);
	GPK1CON = (unsigned long *)(virt_addr_gpk+0x00);
	GPK1DAT = (unsigned long *)(virt_addr_gpk+0x04);
	GPK1PUD	= (unsigned long *)(virt_addr_gpk+0x08);
	
    devno = MKDEV(major,minor); //��ȡ�豸�� 
	
    ret = register_chrdev(major,"led_daniel",&led_ops); //ע���豸 
  
    cls = class_create(THIS_MODULE, "myclass");  //�����豸��
    if(IS_ERR(cls))  
    {  
        unregister_chrdev(major,"led_daniel");  
        return -EBUSY;  
    }  
    test_device = device_create(cls,NULL,devno,NULL,"led_daniel");//�����豸�ڵ� mknod /dev/hello  
    /*
	��������ʼ���Ĵ��������class_create(...)Ϊ���豸����һ��class��
	��Ϊÿ���豸����device_create(...)������Ӧ���豸��
    �ں��ж����struct class�ṹ�壬����˼�壬һ��struct class�ṹ�����ͱ�����Ӧһ���࣬
	�ں�ͬʱ�ṩ��class_create(��)��������������������һ���࣬���������sysfs���棬
	һ��������������࣬�ٵ��� device_create(��)��������/devĿ¼�´�����Ӧ���豸�ڵ㡣
     ����������ģ���ʱ���û��ռ��е�udev���Զ���Ӧ device_create()������
	 ȥ/sysfs��Ѱ�Ҷ�Ӧ����Ӷ������豸�ڵ㡣
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
	1. ��driver�ṹ�����bus��driver����
	2. ��bus��dev����ȡ��ÿһ��dev����bus��match�����ж�dev�ܷ�֧�����drv
	3. ��֧�־͵���������probe
	��: bus��match����ж�dev֧��drv�أ�
	��: ��\linux_dir\drivers\base\bus.c��driver_helper����:
	if (strcmp(name, dev->bus_id) == 0)  return 1;
	��������֪match�����Ǹ���device��bus_id��driver��name�Ƿ�һ����ƥ���
	device_add��driver_register���������Ƚ����ߵ�bus_id��name�����һ����
	����driver��probe
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