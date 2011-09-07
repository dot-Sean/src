#!/usr/bin/php
<?
//($stdin = fopen("php://stdin", "r")) || die("Cannot open stdin.");
while (! feof(STDIN)) {
  $line = trim(fgets(STDIN));
  echo "d:$line\n";
}
?>
