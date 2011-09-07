<?

function hoge($params = array()) {
  $foo = array_key_exists("abc", $params)? $params["abc"]: "foo";
  $bar = array_key_exists("123", $params)? $params["123"]: "123";
  print_r($params);
  echo "d: $foo, $bar\n";
}

hoge();
hoge(array("abc" => "xyz", 3 => "9"));
hoge(array("123" => "789"));

?>
