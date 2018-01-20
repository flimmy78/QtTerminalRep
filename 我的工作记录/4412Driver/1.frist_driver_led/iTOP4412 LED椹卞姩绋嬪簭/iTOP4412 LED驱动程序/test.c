#include <sys/types.h>  
#include <sys/stat.h>  
#include <fcntl.h>  
#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>
int main(int argc, char **argv) 
{  
    int fd,i,lednum;  
	printf("hello test \r\n");
	printf("argc=%d\r\n",argc);//argc 通过命令行传入参数的个数 参数间空格区分
	printf("argv1=%s\r\n",argv[1]);//argv数组保存传入的参数
	printf("argv2=%s\r\n",argv[2]);
    fd = open("/dev/led_daniel",O_RDWR); //调用驱动中的file_operations成员open()函数 
    if(fd<0)  
    {  
        perror("open fail \n");  
        return ;  
    }  
    else 
	{
		printf("---begin test---\r\n\r\n");
		if(argc<3) {printf("error para\r\n");exit(1);}
		printf("find devices\r\n");
		ioctl(fd, atoi(argv[1]),atoi(argv[2]));//atoi()将字符串转化为整型
		//将调用file_operations  .unlocked_ioctl
		//此处 ioctl()在早期的内核(2.6.22之前)成员函数为 ioctl();
		//在后期的内核中 成员函数为 unlocked_ioctl
		printf("open devices OK \r\n");
	}		
    // 
	printf("exit debug\r\n");
	/*用户空间延时
	sleep(5); //延时5s  
	usleep(5);//延时5ms
	*/
	/*内核空间延时函数
	udelay(int n);  延时n微秒
	mdelay(int n);  延时n毫秒
	ndelay(int n);  延时n纳秒
	*/
    close(fd); //调用 file_operations .release
}  