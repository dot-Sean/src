CLASSES := FormTest.class Polygon.class

all: $(CLASSES)
	make -C custom all
	make -C struts all

%.class: %.java
	CLASSPATH=$$CLASSPATH:/usr/share/java/servlet.jar javac $^

clean:
	rm -f $(CLASSES) *~
	make -C custom clean
	make -C struts clean
	