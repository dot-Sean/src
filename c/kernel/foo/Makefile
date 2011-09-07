#CFLAGS += -S # ASM
CFLAGS += -E # CPP

obj-m := foo.o

foo-objs := main.o sub.o

all: user
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm -f Module.* Modules.* *~ user

install_udev_rules:
	cat foo.rules > /etc/udev/rules.d/51-foo.rules
