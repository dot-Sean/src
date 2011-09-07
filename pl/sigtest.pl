#!/usr/bin/perl

sub on_sig_hup {
  my $sig = shift;
  print "HUP!!!!!!!!!!!!!!!!!!\n";
}

$atime = 2;

sub on_sig_alrm {
  my $sig = shift;
  print "$atime ALRM!!!!!!!!!!!!\n";
  alarm($atime);
}

$SIG{HUP} = "on_sig_hup";
$SIG{ALRM} = "on_sig_alrm";

alarm($atime);

while (1) {
  sleep(10);
}
