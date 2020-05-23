obj-m += map_driver.o

KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

default:
	make -C $(KERNELDIR) M=$(PWD) modules
	gcc maptest_read.c -o maptest_read.o
	gcc maptest_write.c -o maptest_write.o

clean:
	make -C $(KERNELDIR) M=$(PWD) clean
