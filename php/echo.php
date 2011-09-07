#!/usr/bin/php
<?php
echo <<<EOF
Here document
available.
EOF;
echo " Hello\n";
$hello = "Hello World\n";
?>
Hoge fuga <?= $hello ?>
<?= "???\n" ?>
