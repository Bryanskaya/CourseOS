
#obj-m += parse_comm.o

all: fw_comm.o

fw_comm.o: fw_comm.c
	gcc -o fw_comm.o fw_comm.c	
#	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	rm -rf fw_comm *.o
#	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean