#!/usr/bin/perl

use Dumpvalue;
my $dumper = new Dumpvalue;

@a = ("hoge", "fuga");
push @a, "foo";
print("@a\n");
print($#a . "\n");
print("$a[$#a]\n");
@b = (1, 2, 3);
push @a, \@b;

$dumper->dumpValues(\@a);

use Data::Dumper;
print Dumper(\@a);
