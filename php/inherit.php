<?

class Base {
  var $hoge = "hoge";
}

class Derived {
  var $hoge = "fuga";
}

$class = "Derived";
$i = new $class;
echo $i->hoge;

?>
