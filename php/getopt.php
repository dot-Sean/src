#!/usr/bin/php
<?
$opts = getopt("ab:c");
while (list($key, $val) = each($opts)) {
  switch ($key) {
    case "a": {
      echo "\"a\" enabled\n";
      break;
    }
    case "b": {
      echo "val: $val\n";
      break;
    }
    default: {
      break;
    }
  }
}
?>
