#!/usr/bin/env perl

$g = "GLOBAL";
$l = "GLOBAL";

sub foo {
  my $l = "LOCAL";
  print "d: $g, $l\n";
  my $s = "abc XYZ";
  if      ($s =~ /ABC/) {
    print "1\n";
  } elsif ($s =~ /([x-z]*)z/i) {
    print "2: $1\n";
  } else {
    print "3\n";
  }
  my @l = (1, 2, 3);
  for my $e (@l) { print "d0: $e\n"; }
  push @l, ("tail",);
  unshift @l, ("head",);
  for (my $i = 0; $i <= $#l; $i ++) { print "d1: " . $l[$i] . "\n"; }
  %h = ("hoge" => "HOGE", "fuga" => "FUGA",);
  $h{"foo"} = "FOO";
  foreach my $k (sort(keys(%h))) { print "d2: " . $h{$k} . "\n"; }
}

foo();
$file = "/etc/fstab";
if (-r $file) {
  open(CMD, "cat -n $file |");
  while (<CMD>) {
    print;
  }
  close(CMD);
}
