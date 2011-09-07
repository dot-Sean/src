all: test

HelloWorld.class: HelloWorld.java
	javac $^

test: HelloWorld.class
	java HelloWorld

HelloWorld: HelloWorld.class
	gcj --main=$@ $^ -o $@

JdbcTest.class: JdbcTest.java
	javac $^

jdbctest: JdbcTest.class
	CLASSPATH=$$CLASSPATH:/usr/share/java/postgresql-jdbc.jar:/opt/PostgresPlus/8.3R2AS/migrationstudio/lib/jtds-1.2.jar \
	 java JdbcTest

JdbcVer.class: JdbcVer.java
	javac $^

jdbcver: JdbcVer.class
	CLASSPATH=$$CLASSPATH:/tmp/edb-jdbc14.jar
	 java JdbcVer

clean:
	rm -f *.class *~ *.s HelloWorld

HelloEJBClient.class: HelloEJBClient.java
	javac -classpath /tmp/jboss-5.0.1.GA/client/jbossall-client.jar:/tmp/jboss-5.0.1.GA/server/default/deploy/helloejb.jar $^
