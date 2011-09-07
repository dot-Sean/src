#!/usr/bin/perl

use MyClass;

$obj = new MyClass(2, 3);
$obj->show();

use MySubClass;

$obj2 = new MySubClass(4, 5);
$obj2->show();
$obj2->hoge();
