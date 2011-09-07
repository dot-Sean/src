// インターフェイスと基底クラスとでメソッドのシグネチャが一致すると、オーバーライドしなくてもコンパイルエラーにならずに、基底のメソッドを呼んでしまう

import java.lang.*;

class Conflict {
    public static void main (String [] args) {
        I i = new D();
        i.foo();
    }
}

interface I {
    void foo();
    void bar();
}

class B {
    public void foo() { System.out.println("Base"); }
}

class D extends B implements I {
    @Override
    public void foo() {
        System.out.println("Derived");
    }
}
