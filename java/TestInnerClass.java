class EnclosingClass {
  public int i = 10;
  public class InnerClass { // "static" is not allowed becase using enclosing "this"
    // EnclosingClass.this is the enclosing instance
    public int x = EnclosingClass.this.i;
    public InnerClass () {
      System.out.printf("Inner: %d%n", x);
    }
  }
  public EnclosingClass () {
    System.out.printf("Enclosing%n");
    InnerClass bar = new InnerClass();
  }
  public static InnerClass getInst(EnclosingClass encinst) {
    return encinst.new InnerClass();
  }
}

class TestInnerClass {
  public static void main (String [] args) {
    EnclosingClass foo = new EnclosingClass();
    foo.i = 20;
    EnclosingClass.InnerClass buzz = EnclosingClass.getInst(foo);
  }
}
