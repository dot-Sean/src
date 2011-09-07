CLASSES := HogeForm.class HogeProcess.class

all: $(CLASSES)

%.class: %.java
	CLASSPATH=$$CLASSPATH:$(shell build-classpath servlet):$(shell build-classpath struts):$$HOME/src/svl/WEB-INF/classes/ javac $^

clean:
	rm -f $(CLASSES) *~

