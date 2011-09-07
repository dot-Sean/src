#!/usr/bin/perl

# 保持・受け渡しには参照を、既存関数での利用時にのみ所定の型に

$a = [
 ["abc", 987,],
 ["xyz", 123,],
 ["def", 456,],
];

sub show {
  my ($a) = @_;
  for $i (@$a) {
    $delim = "";
    map { print $delim . $_ ; $delim = ", "; } @$i;
    print "\n";
  }
}

$delim = "";

print $delim;
&show($a);
$delim = "--------\n";

@$a = sort { @$a[1] <=> @$b[1] } @$a;

print $delim;
&show($a);
$delim = "--------\n";

@b = sort { @$a[0] cmp @$b[0] } @$a;

print $delim;
&show(\@b);
$delim = "--------\n";

