obj-m := cdata.o

KDIR := /home/ubuntu/linux-alsa/linux_holiday-ics
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	rm -rf *.o *.ko .*cmd modules.* Module.* .tmp_versions *.mod.c test
