ifndef CONFIG_HELLO
  CONFIG_HELLO := x
endif

obj-$(CONFIG_HELLO) := hello.o world.o

world-objs := main.o sub.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm -f Module.* Modules.* *~
