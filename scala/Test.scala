import scala.io.Source
object Test {
  def main(args: Array[String]) = {
    val input = Source.fromFile(args(0))
    val lines = for (l <- input.getLines) yield l.stripLineEnd // >= 2.8
    input.close // >= 2.8
    for (line <- lines) {
      println("d: " + line)
    }
  }
}
