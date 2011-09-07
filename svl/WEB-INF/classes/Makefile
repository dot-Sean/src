CLASSES := WelcomeExample.class HelloWorldExample.class \
 ExceptionTest.class SynchronizedTest.class TestFilter.class

all: $(CLASSES)
	make -C com/ayutaya all

%.class: %.java
	CLASSPATH=$$CLASSPATH:$(shell build-classpath servlet) javac $^

clean:
	rm -f $(CLASSES) *~
	make -C com/ayutaya clean
	