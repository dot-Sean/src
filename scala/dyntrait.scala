object Test {
  class Foo {
    def foo() = {
      print("I am Foo")
    }
  }
  trait Bar {
    def bar() = {
      print("I am Bar")
    }
  }
  trait Buzz {
    def bar() = {
      print("I am Buzz")
    }
  }
  def main(args: Array[String]) = {
    val foo = new Foo with if (true) Bar else Buzz
    foo.foo()
  }
}
