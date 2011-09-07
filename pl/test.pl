@a = (1, 2, 3);
push @a, 5;
for $i (@a) {
  print "$i\n";
}
$a = "A" . ((0)? "B": "C");
print $a . "\n";

$s = "xxxabc123yyy";
if ($s =~ /([abc123]+)|([abc]+)/) {
  print "matched $1\n";
} else {
  print "unmatched\n";
}
