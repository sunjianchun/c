obj-m  := first_mod.o

KDIR   := /usr/src/kernels/2.6.32-696.23.1.el6.x86_64 
PWD    := $(shell pwd)

default:
		$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	-rm *.o *.ko
