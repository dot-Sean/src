<?
header("Content-type: text/plain");
$dname = $_REQUEST["dname"];
$dver = $_REQUEST["dver"];
$darch = $_REQUEST["darch"];
$internal = ($_REQUEST["internal"] == "true");
$stabtype = $_REQUEST["stype"]; # empty | tested | untested | full
$raddr = $_SERVER["REMOTE_ADDR"];
#$raddr = "222.73.18.144"; # CN

# --------------------------------------------------------------------

$darchaliases["i486"] = "i386";
$darchaliases["i586"] = "i386";
$darchaliases["i686"] = "i386";
$darchaliases["ia32"] = "i386";
$darchaliases["IA32"] = "i386";

$darchaliases["x64"] = "x86_64";

function iprange($from, $to) {
  return array(ip2long($from), ip2long($to));
}

function ipstartlength($start, $length) {
  return array(ip2long($start), ip2long($start) + $length - 1);
}

require("ipranges.php");

$regionips = array();
foreach (array_keys($ipranges) as $type) {
  if (strtolower($type) == "ipv4") {
    foreach (array_keys($ipranges[$type]) as $cc) {
      $regionips[$cc] = array();
      foreach ($ipranges[$type][$cc] as $range) {
        $regionips[strtolower($cc)][] = ipstartlength($range[0], $range[1]);
      }
    }
  }
}

# --------------------------------------------------------------------

$dveraliases["TL11S"] = "TL12C";
$dveraliases["12"] = "TL12C";
$dveraliases["TL12"] = "TL12C";
$dveraliases["TL12D"] = "TL12C";

# All packages for TL12C

$mirrordata["manbo"]["TL12C"]["i386"]["empty"] = array(
 "jp-int" => array("http://saturn.jp.tlan/distro/Manbo/mnb1-main/"),
 "jp" => array("http://jupiter.turbolinux.co.jp/yum/12d/ia32/manbo/"),
 "global" => array(),
);
$mirrordata["manbo-updates"]["TL12C"]["i386"]["full"] = array(
 "jp-int" => array("http://saturn.jp.tlan/distro/Manbo/mnb1/bCore/"),
 "jp" => array("http://jupiter.turbolinux.co.jp/yum/12d/ia32/manbo-updates/"),
 "global" => array(),
);

$mirrordata["turbolinux"]["TL12C"]["i386"]["empty"] = array(
 "jp-int" => array("http://saturn.jp.tlan/distro//MagnyCours/buildRPMS/RPMS-main/"),
 "jp" => array("http://jupiter.turbolinux.co.jp/yum/12d/ia32/turbolinux/"),
);
$mirrordata["turbolinux-updates"]["TL12C"]["i386"]["full"] = array(
 "cn-int" => array("http://ftp.cn.tlan/yum/12d/ia32/turbolinux-updates/"),
 "jp-int" => array("http://saturn.jp.tlan/distro//MagnyCours/buildRPMS/RPMS/"),
 "jp" => array("http://jupiter.turbolinux.co.jp/yum/12d/ia32/turbolinux-updates/"),
 "global" => array("http://ftp.turbolinux.com/yum/12d/ia32/turbolinux-updates/"),
);

$mirrordata["non-free"]["TL12C"]["i386"]["empty"] = array(
 "jp-int" => array("http://saturn.jp.tlan/distro/MagnyCours/buildRPMS/non-free/"),
 "jp" => array("http://jupiter.turbolinux.co.jp/yum/12d/ia32/non-free/"),
);
$mirrordata["non-free-updates"]["TL12C"]["i386"]["full"] = array(
 "jp-int" => array("http://saturn.jp.tlan/distro/MagnyCours/buildRPMS/non-free-updates/"),
 "jp" => array("http://jupiter.turbolinux.co.jp/yum/12d/ia32/non-free-updates/"),
);

# Untested and tested packages listed in comps for TL12C

$mirrordata["manbo"]["TL12C"]["i386"]["tested"] = array(
 "cn" => array("http://www.sh.turbolinux.com/mc/yumrepos/manbo/"),
 "jp" => array("http://ftp.turbolinux.co.jp/pub/TurboLinux/TurboLinux/ia32/Client/12/manbo/"),
 "jp-int" => array("http://saturn.jp.tlan/mc/yumrepos/manbo/"),
 "global" => array(),
);
$mirrordata["manbo-updates"]["TL12C"]["i386"]["tested"] = array(
 "cn" => array("http://www.sh.turbolinux.com/mc/yumrepos/manbo-updates/"),
 "jp" => array("http://ftp.turbolinux.co.jp/pub/TurboLinux/TurboLinux/ia32/Client/12/manbo-updates/"),
 "jp-int" => array("http://saturn.jp.tlan/mc/yumrepos/manbo-updates/"),
 "global" => array(),
);

$mirrordata["turbolinux"]["TL12C"]["i386"]["tested"] = array(
 "cn" => array("http://www.sh.turbolinux.com/mc/yumrepos/turbolinux/"),
 "jp-int" => array("http://saturn.jp.tlan/mc/yumrepos/turbolinux/"),
 "jp" => array("http://ftp.turbolinux.co.jp/pub/TurboLinux/TurboLinux/ia32/Client/12/turbolinux/"),
);
$mirrordata["turbolinux-updates"]["TL12C"]["i386"]["tested"] = array(
 "cn" => array("http://www.sh.turbolinux.com/mc/yumrepos/turbolinux-updates/"),
 "jp" => array("http://ftp.turbolinux.co.jp/pub/TurboLinux/TurboLinux/ia32/Client/12/turbolinux-updates/"),
 "jp-int" => array("http://saturn.jp.tlan/mc/yumrepos/turbolinux-updates/"),
);

$mirrordata["non-free"]["TL12C"]["i386"]["tested"] = array(
 "cn" => array("http://www.sh.turbolinux.com/mc/yumrepos/non-free/"),
 "jp-int" => array("http://saturn.jp.tlan/mc/yumrepos/non-free/"),
 "jp" => array("http://ftp.turbolinux.co.jp/pub/TurboLinux/TurboLinux/ia32/Client/12/non-free/"),
);
$mirrordata["non-free-updates"]["TL12C"]["i386"]["tested"] = array(
 "cn" => array("http://www.sh.turbolinux.com/mc/yumrepos/non-free-updates/"),
 "jp-int" => array("http://saturn.jp.tlan/mc/yumrepos/non-free-updates/"),
 "jp" => array("http://ftp.turbolinux.co.jp/pub/TurboLinux/TurboLinux/ia32/Client/12/non-free-updates/"),
);

$mirrordata["manbo-updates"]["TL12C"]["i386"]["untested"] = array(
 "jp-int" => array("http://saturn.jp.tlan/mc/yumrepos/manbo-updates-untested/"),
 "global" => array(),
 "jp" => array("http://ftp.turbolinux.co.jp/pub/TurboLinux/TurboLinux/ia32/Client/12/manbo-updates-untested/"),
);
$mirrordata["turbolinux-updates"]["TL12C"]["i386"]["untested"] = array(
 "jp-int" => array("http://saturn.jp.tlan/mc/yumrepos/turbolinux-updates-untested/"),
 "jp" => array("http://ftp.turbolinux.co.jp/pub/TurboLinux/TurboLinux/ia32/Client/12/turbolinux-updates-untested/"),
);
$mirrordata["non-free-updates"]["TL12C"]["i386"]["untested"] = array(
 "jp-int" => array("http://saturn.jp.tlan/mc/yumrepos/non-free-updates-untested/"),
 "jp" => array("http://ftp.turbolinux.co.jp/pub/TurboLinux/TurboLinux/ia32/Client/12/non-free-updates-untested/"),
);

# Source packages listed in comps for TL12C
$mirrordata["manbo-source"]["TL12C"]["i386"]["tested"] = array(
 "jp-int" => array("http://saturn.jp.tlan/mc/yumrepos/manbo-source/"),
 "jp" => array("http://ftp.turbolinux.co.jp/pub/TurboLinux/TurboLinux/ia32/Client/12/manbo-source/"),
);
$mirrordata["turbolinux-source"]["TL12C"]["i386"]["tested"] = array(
 "jp-int" => array("http://saturn.jp.tlan/mc/yumrepos/turbolinux-source/"),
 "jp" => array(
  "http://ftp.turbolinux.co.jp/pub/TurboLinux/TurboLinux/ia32/Client/12/turbolinux-source/"
 ),
);
$mirrordata["non-free-source"]["TL12C"]["i386"]["tested"] = array(
 "jp-int" => array("http://saturn.jp.tlan/mc/yumrepos/non-free-source/"),
 "jp" => array("http://ftp.turbolinux.co.jp/pub/TurboLinux/TurboLinux/ia32/Client/12/non-free-source/"),
);
# --------------------------------------------------------------------

$raddr = ip2long($raddr);
if (! $stabtype) {
  $stabtype = "tested";
}

$region = "";
foreach (array_keys($regionips) as $candregion) {
  foreach ($regionips[$candregion] as $pair) {
    $from = $pair[0];
    $to = $pair[1];
    //echo sprintf("# raddr: %lu, from: %lu, to: %lu ($candregion)\n", $raddr, $from, $to);
    if ($from <= $raddr && $raddr <= $to) {
      $region = $candregion;
    }
  }
}

if (FALSE !== strpos($_SERVER["SCRIPT_NAME"], "intmirrorlist.php")) {
  $internal = TRUE;
  echo "# Forcing internal repositories\n";
}

if (array_key_exists($darch, $darchaliases)) {
  $darch = $darchaliases[$darch];
}

if (! $dver || $dver == "\$releasever") {
  $dver = "TL12C";
}

if (array_key_exists($dver, $dveraliases)) {
  $dver = $dveraliases[$dver];
}

echo sprintf("# dname: $dname, dver: $dver, darch: $darch, raddr: %x, stabtype: $stabtype, region: $region\n", $raddr);

if (array_key_exists($dname, $mirrordata)) {
  $dverdct = $mirrordata[$dname];
  if (array_key_exists($dver, $dverdct)) {
    $darchdct = $dverdct[$dver];
    if (array_key_exists($darch, $darchdct)) {
      $stabtypedct = $darchdct[$darch];
      if (array_key_exists($stabtype, $stabtypedct)) {
        $regmirrorlists = $stabtypedct[$stabtype];
        $mirrors = array();
        # internal access & country is detected
        if ($internal && array_key_exists("$region-int", $regmirrorlists)) {
          foreach ($regmirrorlists["$region-int"] as $mirror) {
            if (! in_array($mirror, $mirrors)) {
              array_push($mirrors, $mirror);
            }
          }
        }
        # country is detected
        if (array_key_exists("$region", $regmirrorlists)) {
          foreach ($regmirrorlists["$region"] as $mirror) {
            if (! in_array($mirror, $mirrors)) {
              array_push($mirrors, $mirror);
            }
          }
        }
        # put global address
        if (array_key_exists("global", $regmirrorlists)) {
          foreach ($regmirrorlists["global"] as $mirror) {
            if (! in_array($mirror, $mirrors)) {
              array_push($mirrors, $mirror);
            }
          }
        }
        # the others
        $extregkeys = array();
        foreach (array_keys($regmirrorlists) as $key) {
          if (! strstr($key, "-int")) {
            array_push($extregkeys, $key);
          }
        }
        foreach ($extregkeys as $key) {
          foreach ($regmirrorlists[$key] as $mirror) {
            if (! in_array($mirror, $mirrors)) {
              array_push($mirrors, $mirror);
            }
          }
        }
        foreach ($mirrors as $mirror) {
          echo "$mirror\n";
        }
      }
    }
  }
}
?>
