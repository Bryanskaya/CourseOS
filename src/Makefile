
obj-m += fw_module.o

all: fw.o fw_module.o

fw.o: fw.c fw.h
	gcc -o fw.o fw.c	

fw_module.o: fw_module.c
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	rm -rf fw *.o
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean