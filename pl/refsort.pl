#!/usr/bin/perl

# �ݻ��������Ϥ��ˤϻ��Ȥ򡢴�¸�ؿ��Ǥ����ѻ��ˤΤ߽���η���

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

