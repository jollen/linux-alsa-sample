CONFIG_MODULE_SIG=n
CONFIG_MODULE_SIG_ALL=n

obj-m := snd_my_soc.o

KDIR := /usr/src/linux-headers-3.13.0-74-generic

PWD := $(shell pwd)

default:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	rm -rf *.o *.ko .*cmd modules.* Module.* .tmp_versions *.mod.c test
