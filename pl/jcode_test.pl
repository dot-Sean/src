require "jcode.pl";

&jcode'init();

$_ = "abc";
&jcode'getcode;
print "d: " . $_;

while (<>) {
  &jcode'convert($_, "jis");
  print $_;
}

