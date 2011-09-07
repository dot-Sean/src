obj-m := bar.o

all: user
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) V=1 modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm -f Module.* Modules.* *~ user

install_udev_rules:
	cat bar.rules > /etc/udev/rules.d/51-bar.rules
