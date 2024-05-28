obj-m = bl_drv.o
PWD = $(shell pwd)
ccflags-y := -std=gnu99 -Wno-declaration-after-statement

all:
	make -C /lib/modules/$(shell uname -r)/build M="$(PWD)" modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M="$(PWD)" clean

load:
	sudo insmod bl_drv.ko    

uload:
	sudo rmmod bl_drv

lcheck:
	@sudo lsmod | grep bl_drv || true