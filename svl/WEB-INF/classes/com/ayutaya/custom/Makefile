CLASSES := circle.class

all: $(CLASSES)

%.class: %.java
	CLASSPATH=$$CLASSPATH:$(shell build-classpath servlet):$(shell build-classpath jsp) javac $^

clean:
	rm -f $(CLASSES) *~
