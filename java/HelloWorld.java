import java.io.*;

//import java.lang.*;

class HelloWorld {
    static int n = 0;
    static FileNotFoundException act() throws FileNotFoundException {
        n += 1;
        System.out.println("aaa");
        if (n > 10) {
            n = 10 / 0;
        }
        if (true) {
            foo();
        }
        return (act());
    }
    static void foo() throws FileNotFoundException {
        throw act();
    }
    public static void main (String [] args) {
        System.out.println("Hello, World!");
        try {
          foo();
        } catch (FileNotFoundException e) {
           System.err.println(e.getMessage());
        }
//        System.out.println(System.getProperty("java.home"));
//        System.out.println(System.getProperty("sun.boot.class.path"));
    }
}
