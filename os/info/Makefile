obj-m := info.o
KDIR   := /usr/src/kernels/2.6.32-696.23.1.el6.x86_64 
PWD    := $(shell pwd)
default:
	echo '    编译自定义模块在 2.6 kernel.'
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
install:
	insmod info.ko
clean:
	rmmod info.ko
	rm -f -r *.o *.ko .*cmd .tmp* core *.i
