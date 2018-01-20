#ifneq  ($(KERNELRELEASE),)  
obj-m:=devices.o driver.o  
obj-y:=test.o
#$(info "2nd")  
#else  
#KDIR := /lib/modules/$(shell uname -r)/build  
#KDIR := /home/fs/linux/linux-3.14-fs4412  
KDIR := /home/testfile/Testfile/iTop4412_Kernel_3.0//更改为你的内核目录
PWD:=$(shell pwd)  
all:  
	make -C $(KDIR) M=$(PWD) modules  
clean:  
	rm -f *.ko *.o *.symvers *.mod.c *.mod.o *.order  *o.cmd
#endif 