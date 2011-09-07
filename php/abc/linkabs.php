#!/usr/bin/php -q
<?
$datdir_ = "";
if ($fd = fopen("/etc/abc.conf", "r")) {
  $lines = array();
  while (! feof($fd)) {
    $lines[] = fgets($fd, 4096);
  }
  fclose($fd);
  foreach ($lines as $line) {
    $line = trim($line);
    list($key, $val) = explode("=", $line, 2);
    if       ($key == "datdir") {
      $datdir_ = $val;
    } elseif ($key == "passwd") {
      $passwd_file_ = $val;
    } elseif ($key == "abcdir") {
      $abcdir_ = $val;
    }
  }
}
if (! file_exists("$datdir_/meta.inf")) {
  exit();
}
require("$abcdir_/html/mz/common.php");
function putAbInfo($path, $abc, $ab, $pg, $next_url) {
  $dir = dirname($path);
  system("mkdir -p $dir");
  system("touch $dir/index.html");
  $fd = fopen($path, "w+");
  fputs($fd, "--- #YAML: 1.0\n");
  fputs($fd, "# " . strftime("%Y/%m/%d %H:%M:%S") . "\n");
  fputs($fd, "banners:\n");
  if ($pg) {
    foreach ($pg->getChildrenIds() as $wid) {
      $wd = $pg->getChild($wid);
      fputs($fd, "  - border: {$wd->params[border]}\n");
      fputs($fd, "    width: {$wd->params[width]}\n");
      fputs($fd, "    height: {$wd->params[height]}\n");
      $relpath = "{$ab->id}-{$pg->id}-{$wd->id}/";
      $wurl = "/{$abc->params[abspath]}/{$relpath}";
      $wurl = str_replace("//", "/", $wurl);
      $wurl = "{$abc->params[server]}$wurl";
      fputs($fd, "    url: $wurl\n");
    }
  }
  if ($ab) {
    fputs($fd, "refresh: {$ab->params["refresh"]}\n");
    fputs($fd, "arrange: {$ab->params["arrange"]}\n");
  } else {
    fputs($fd, "refresh: 1\n");
  }
  fputs($fd, "next: $next_url\n");
  fclose($fd);
}
function activeTime($vfrom, $vto, $stamp) {
  if ((! $vfrom && ! $vto) || ($vfrom == "-" && $vto == "-")) {
    return 1;
  }
  if ($vfrom && $vfrom != "-" && $stamp < $vfrom) {
    return 0;
  }
  if ($vto && $vto != "-" && $vto < $stamp) {
    return 0;
  }
  return 1;
}
$abc = new ActiveBannerController();
system("rm -fr {$abc->params[docroot]}/{$abc->params[abspath]}");
system("mkdir -p {$abc->params[docroot]}/{$abc->params[abspath]}");
system("touch {$abc->params[docroot]}/{$abc->params[abspath]}/index.html");
$stamp = time();
foreach ($abc->getChildrenIds() as $id) {
  $ab = $abc->getChild($id);
  $basename = basename($ab->params["path"]);
  $start_path = "{$ab->params[path]}.yaml";
  $abs_start_path = "{$abc->params[docroot]}{$start_path}";
  if ($ab->params["stat"] == "active" &&
   activeTime($ab->params["vfrom"], $ab->params["vto"], $stamp) ) {
    $pids = $ab->getChildrenIds();
    $pcount = count($pids);
    $i = 0;
    foreach ($pids as $pid) {
      $pg = $ab->getChild($pid);
      if ($i + 1 < $pcount) {
        $next_id = $i + 1;
      } else {
        $next_id = 0;
      }
      $chain_path = sprintf("%s/%s-chain%d.yaml", dirname($start_path), $basename, $i);
      $abs_chain_path = "{$abc->params[docroot]}{$chain_path}";
      $next_path = sprintf("%s/%s-chain%d.yaml", dirname($start_path), $basename, $next_id);
      $next_url = "{$abc->params[server]}$next_path";
      if ($i == 0) {
        putAbInfo($abs_start_path, $abc, $ab, $pg, $next_url);
      }
      putAbInfo($abs_chain_path, $abc, $ab, $pg, $next_url);
      foreach ($pg->getChildrenIds() as $wid) {
        $wd = $pg->getChild($wid);
        $src = "{$wd->datdir}/html";
        $relpath = "{$ab->id}-{$pg->id}-{$wd->id}";
        $dst = "{$abc->params[docroot]}/{$abc->params[abspath]}/{$relpath}";
        $dst = str_replace("//", "/", $dst);
        system("rm -fr $dst; ln -sf $src $dst");
      }
      $i ++;
    }
    for (; $i < $pcount + 20; $i ++) {
      $chain_path = sprintf("%s/%s-chain%d.yaml", dirname($start_path), $basename, $i);
      $abs_chain_path = "{$abc->params[docroot]}{$chain_path}";
      $next_id = 0;
      $next_path = sprintf("%s/%s-chain%d.yaml", dirname($start_path), $basename, $next_id);
      $next_url = "{$abc->params[server]}$next_path";
      putAbInfo($abs_chain_path, NULL, NULL, NULL, $next_url);
    }
  }
}
?>
