#!/usr/bin/php
<?
//global $argv;
$i = 0;
foreach ($argv as $arg) {
  echo sprintf("d%d: %s\n", $i, $arg);
  $i ++;
}
?>
