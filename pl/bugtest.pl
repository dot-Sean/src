sub f {
  local(*_) = @_;
  $_ = "modified";
}
$_ = "unchanged";
$a = "unchanged";
&f(*a);
print "\$_: $_, \$a: $a\n"; # must be "$_: unchanged, $a: modified"
