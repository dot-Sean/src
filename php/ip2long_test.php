<?
function isPriv ($saddr) {
  $laddr = ip2long($saddr);
  return (
   (ip2long("10.0.0.0") <= $laddr && $laddr <= ip2long("10.255.255.255")) ||
   (ip2long("172.16.0.0") <= $laddr && $laddr <= ip2long("172.31.255.255")) ||
   (ip2long("192.168.0.0") <= $laddr && $laddr <= ip2long("192.168.255.255"))
  );  
}
print "d: " . ((isPriv("210.171.55.3"))? "True": "False") . "\n";
print "d: " . ((isPriv("172.16.37.3"))? "True": "False") . "\n";
?>
