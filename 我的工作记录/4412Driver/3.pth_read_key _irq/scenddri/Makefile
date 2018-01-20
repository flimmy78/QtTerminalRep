KERNEL = /home/topeet/iTop4412_Kernel_3.0
all:  
	make -C $(KERNEL) M=`pwd` modules 
clean:
	make -C $(KERNEL) M=`pwd` modules clean
	rm -rf modules.order
obj-m += key_irq.o
