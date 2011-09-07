// http://www.itmedia.co.jp/enterprise/articles/0908/22/news001_3.html

import java.util.*;

import java.text.*; // Format

abstract class AbstractDescribable {
    abstract protected String getDescription ();
    public void describe () {
        System.out.println(getDescription());
    }
}

interface Describable {
    public void describe ();
}

abstract class Base {
    Base () { System.out.println("Base constructed"); }
    protected void finalize () { System.out.println("Base finalized"); }
    public static Base factory (int n) {
      Base base;
        if ((n % 2) == 0) {
            base = new DerivedA();
        } else {
            base = new DerivedB();
        }
        return (base);
    }
    public String getName() { return "Basic"; }
}

class DerivedA extends Base {
    DerivedA () { System.out.println("DerivedA constructed"); }
    public String getName() { return ("DerivedA/" + super.getName()); }
    protected void finalize () { System.out.println("DerivedA finalized"); }
}

class DerivedB extends Base implements Describable {
    DerivedB () { System.out.println("DerivedB constructed"); }
    private AbstractDescribable descimp = new AbstractDescribable() {
        protected String getDescription() { return ("Hello, World"); }
    };
    public String getName() {
        describe();
        return ("DerivedB");
    }
    public void describe() { descimp.describe(); }
    protected void finalize () { System.out.println("DerivedA finalized"); }
}

public class Basic {
    public static void main (String [] args) {
        // ArrayList (Java 2 Platform SE 5.0)
        // http://www.solar-system.tuis.ac.jp/Java/jdk-1_5_0-doc-ja/api/java/util/ArrayList.html
        // Queue ÇÕÅAimplement ÇµÇƒÇ¢Ç‹ÇπÇÒ
        List<String> list = new ArrayList<String>();
        list.add("Hello");
        list.add("World");
        list.add(1, "256");
        System.out.println("0: " + list.get(0));
        System.out.println("len: " + list.size());
        for (String s: list) {
            System.out.println("d0: " + s);
        }
        list.clear();
        // -----------------------------------------------------------
        List<Base> listb = new ArrayList<Base>();
        listb.add(Base.factory(255));
        listb.add(Base.factory(256));
        listb.add(Base.factory(257));
        for (Base base: listb) {
            System.out.println("d1: " + base.getName());
        }
        // -----------------------------------------------------------
        // LinkedList (Java 2 Platform SE 5.0)
        // http://java.sun.com/j2se/1.5.0/ja/docs/ja/api/java/util/LinkedList.html
        Queue<String> queue = new LinkedList<String>();
        queue.offer("Foo");
        queue.offer("Bar");
        for (String s: queue) {
            System.out.println("d2: " + s);
        }
        // -----------------------------------------------------------
        // Map (Java 2 Platform SE 5.0)
        // http://www3.ea.u-tokai.ac.jp/~sakata/jdk5/docs/ja/api/java/util/Map.html
        Map<Integer, String> map = new HashMap<Integer, String>();
        map.put(1, "One"); // put(), get(), remove()
        map.put(2, "Two");
        map.put(3, "Three");
        NumberFormat format = NumberFormat.getPercentInstance();
        for (int k: map.keySet()) {
            // Type safe?
            System.out.printf("d3-0: %s\n", format.format(k));
        }
        for (String v: map.values()) {
            System.out.println("d3-1: " + v);
        }
        // Formatter (Java 2 Platform SE 5.0)
        // http://java.sun.com/j2se/1.5.0/ja/docs/ja/api/java/util//Formatter.html
        System.out.printf("%1$s %3$s %2$s\n", 123, "Hoge", "Fuga");
    }
}
