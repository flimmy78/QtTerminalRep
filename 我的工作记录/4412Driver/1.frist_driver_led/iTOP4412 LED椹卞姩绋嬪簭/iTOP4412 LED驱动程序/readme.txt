1. 将内核中的LED设备节点注释，参考itop4412开发板手册说明
2. 执行Makefile文件，编译为.ko模块
3. 在开发板上insmod 加载devices.ko driver.ko