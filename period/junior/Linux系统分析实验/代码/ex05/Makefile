obj-m := simple_char_dev_driver.o

KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

default:
	make -C $(KERNELDIR) M=$(PWD) modules
	gcc simple_char_dev_test_read.c -o simple_char_dev_test_read.o
	gcc simple_char_dev_test_write.c -o simple_char_dev_test_write.o

clean:
	make -C $(KERNELDIR) M=$(PWD) clean
