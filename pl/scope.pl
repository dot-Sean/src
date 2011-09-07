#!/usr/bin/perl
# -*- coding: utf-8 -*-

our $global_a = 100;

sub bar {
  local $bar_c = 300;
  #local $x = "XXX";
  #my $y = "YYY";
  print "$global_a, $foo_b, $bar_c\n";
  print "$x, $y\n";
}

sub foo {
  local $foo_b = 200;
  local $x = "xxx";
  my $y = "yyy";
  bar();
  print "$x, $y\n";
  our $global_b = 1000;
}

&foo;
print "$global_b\n";
