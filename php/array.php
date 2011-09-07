#!/usr/bin/php
<?php
// "array" is not a function but a part of the language
$a = array(
  "hoge",
  "fuga",
  "abc" => array(
    "ABC",
  ),
);
$a[] = "foo";
echo "dd: " . $a["abc"] . "\n";
array_push($a, "bar");
print_r($a);
array_pop($a);
echo "----------------------------------------------------------------------\n";
// 連想配列のキーを配列で取得
echo "d0: " . var_export(array_keys($a), 1) . " -> " . count($a) . "\n";

// 配列の各要素処理
while (list($key, $val) = each($a)) {
  echo "d1: " . $key . " => ";
  echo var_export($val, 1) . "\n";
}

foreach($a as $val) {
  echo "d1-1: " . $val . "\n";
}

// フィルタ
echo "d2: " . var_export(array_filter($a, is_array), 1) . "\n";

if (array_key_exists("abc", $a)) {
  echo "Exists\n";
} else {
  echo "Not exists\n";
}

if ($key = array_search("foo", $a)) {
  echo "Found: $key\n";
} else {
  echo "Not found\n";
}

function cube ($n) {
  return ($n * $n * $n);
}
echo "d3: " . var_export(array_map(cube, array(1, 2, 3)), 1) . "\n";

$a = array();
array_unshift($a, "ZZZ");
array_unshift($a, "YYY");
array_unshift($a, "XXX");
echo "d4: " . var_export($a, 1) . "\n";
arsort($a);
echo "d5: " . var_export($a, 1) . "\n";
asort($a);
echo "d6: " . var_export($a, 1) . "\n";

echo "d7:\n";
$a = array(1, 2, 3);
function hoge($val, $key) {
  echo "  $key, $val\n";
}
array_walk($a, hoge);

$oses = array ("Mac", "NT", "Irix", "Linux");
if (in_array ("Irix", $oses)) {
  print "Got Irix\n";
}
if (in_array ("mac", $oses)) { 
  print "Got mac\n";
}

$newarray["hoge"]["fuga"] = "HOGE";
print $newarray["hoge"]["fuga"];
?>
