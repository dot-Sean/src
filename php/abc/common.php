<?
header("Expires: Mon, 26 Jul 1997 05:00:00 GMT");
header("Last-Modified: " . gmdate("D, d M Y H:i:s") . " GMT");
header("Cache-Control: no-store, no-cache, must-revalidate");
header("Cache-Control: post-check=0, pre-check=0", false);
header("Pragma: no-cache");
$datefmt_ = "%Y/%m/%d %H:%M";
global $abcdir_;
global $datdir_;
global $passwd_file_;
$lines = Array();
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
    } elseif ($key == "abcdir") {
      $abcdir_ = $val;
    }
  }
  $passwd_file_ = "$abcdir_/passwd";
} else {
  exit;
}
class Base {
  function Base($id, $parent, $lst_file, $children_dir, $prefix,
   $cclass, $new_name, $params ) {
    if (! $id) {
      return;
    }
    $this->id = $id;
    $this->parent = $parent;
    if ($parent) {
      $this->datdir = "{$parent->children_dir}/$id";
    } else {
      global $datdir_;
      global $abcdir_;
      $this->datdir = $datdir_;
      $html_dat = "$abcdir_/html/mz/dat";
      system("rm -f $html_dat");
      symlink($datdir_, $html_dat);
    }
    $this->lst_file = "{$this->datdir}/{$lst_file}";
    $this->children_dir = "{$this->datdir}/{$children_dir}";
    $this->prefix = $prefix;
    $this->cclass = $cclass;
    $this->params = $params;
    $this->new_name = $new_name;
    $this->meta_inf_file = "{$this->datdir}/meta.inf";
    $this->i_have_created = 0;
    if ($this->children_dir && ! is_dir($this->children_dir)) {
      mkdir($this->children_dir, 0755);
    }
    if ($this->meta_inf_file && ! file_exists($this->meta_inf_file)) {
      $this->i_have_created = 1;
      $this->reg = time();
      $this->mod = $this->reg;
      $this->name = $this->new_name;;
      $this->writeMeta();
    } else {
      $this->readMeta();
    }
  }
  function readMeta(){
    if ($fd = fopen($this->meta_inf_file, "r")) {
      $lines = array();
      while (! feof($fd)) {
        $lines[] = fgets($fd, 4096);
      }
      fclose($fd);
      foreach ($lines as $line) {
        $line = trim($line);
        list($key, $val) = explode(":", $line, 2);
        if (0) {
          ;
        } elseif ($key == "reg") {
          $this->reg = 0 + $val;
        } elseif ($key == "mod") {
          $this->mod = 0 + $val;
        } elseif ($key == "name") {
          $this->name = $val;
        } elseif (array_key_exists($key, $this->params)) {
          $this->params[$key] = $val;
        }
      }
    }
  }
  function writeMeta() {
    $this->mod = time();
    $fd = fopen($this->meta_inf_file, "w+");
    fputs($fd, "reg:" . $this->reg . "\n");
    fputs($fd, "mod:" . $this->mod . "\n");
    fputs($fd, "name:" . $this->name . "\n");
    foreach ($this->params as $key => $val) {
      fputs($fd, "$key:$val\n");
    }
    fclose($fd);
    if ($this->parent) {
      $this->parent->writeMeta();
    }
  }
  function createNewChildIfNew() {
    if ($this->i_have_created) {
      $this->createNewChild();
    }
  }
  function createChildDir() {
    $datdir =
     tempnam($this->children_dir, strftime("{$this->prefix}%Y%m%d"));
    unlink($datdir);
    mkdir($datdir, 0755);
    return ($datdir);
  }
  function createNewChild() {
    if (! $this->cclass) {
      return 0;
    }
    $datdir = $this->createChildDir();
    $id = basename($datdir);
    $fd = fopen($this->lst_file, "a+");
    fputs($fd, $id . "\n");
    fclose($fd);
    $ret = new $this->cclass($id, $this);
    $this->linkChildTop();
    return ($ret);
  }
  function getChild($id) {
    return (new $this->cclass($id, $this));
  }
  function getChildrenIds() {
    $ids = array();
    if (is_file($this->lst_file) &&
     $fd = fopen($this->lst_file, "r") ) {
      while (! feof($fd)) {
        $lines[] = fgets($fd, 4096);
      }
      fclose($fd);
      foreach ($lines as $line) {
        $id = trim($line);
        if (strlen($id) > 0 && is_dir("{$this->children_dir}/{$id}")) {
          $ids[] = $id;
        }
      }
    }
    return ($ids);
  }
  function linkChildTop() {
    $link = "{$this->children_dir}/top";
    //if (file_exists($link)) {
    //  unlink($link);
    //}
    system("rm -f $link");
    $cids = $this->getChildrenIds();
    if (count($cids) >= 1) {
      // newer php add $pwd to source ????????
      //symlink($cids[0], $link);
      system("ln -sf {$cids[0]} {$link}");
    }
  }
  function setChildrenIds($ids) {
    if (($fd = fopen($this->lst_file, "w"))) {
      foreach ($ids as $id) {
        fputs($fd, $id . "\n");
      }
      fclose($fd);
    }
  }
  function removeChild($id) {
    if (($ids = $this->getChildrenIds())) {
      $i = array_search($id, $ids);
      if ($i === NULL || $i === FALSE) {
        return;
      }
      array_splice($ids, $i, 1);
      system("rm -fr {$this->children_dir}/{$id}");
      $this->setChildrenIds($ids);
    }
    $this->linkChildTop();
    $this->writeMeta();
  }
  function up($id) {
    $ids = $this->getChildrenIds();
    if (count($ids) > 0) {
      $i = array_search($id, $ids);
      if ($i === NULL || $i === FALSE) {
        return;
      }
      array_splice($ids, $i, 1);
      array_splice($ids, $i - 1, 0, $id);
      $this->setChildrenIds($ids);
    }
    $this->linkChildTop();
    $this->writeMeta();
  }
  function down($id) {
    $ids = $this->getChildrenIds();
    if (count($ids) > 0) {
      $i = array_search($id, $ids);
      if ($i === NULL || $i === FALSE) {
        return;
      }
      array_splice($ids, $i, 1);
      array_splice($ids, $i + 1, 0, $id);
      $this->setChildrenIds($ids);
    }
    $this->linkChildTop();
    $this->writeMeta();
  }
  function toTop($id) {
    $ids = $this->getChildrenIds();
    if (count($ids) > 0) {
      $i = array_search($id, $ids);
      if ($i === NULL || $i === FALSE) {
        return;
      }
      array_splice($ids, $i, 1);
      array_splice($ids, 0, 0, $id);
      $this->setChildrenIds($ids);
    }
    $this->linkChildTop();
    $this->writeMeta();
  }
  function duplicate($id) {
    $new_child = $this->createNewChild();
    system("rm -fr {$new_child->datdir}/*");
    system("cp -a {$this->children_dir}/{$id}/* {$new_child->datdir}/");
    $new_child = $this->getChild($new_child->id);
    $copy = "（コピー）";
    if (! ereg("$copy\$", $new_child->name)) {
      $new_child->name = "{$new_child->name}$copy";
    }
    $new_child->writeMeta();
    return ($new_child);
  }
}
class Window extends Base {
  function Window($id, $parent) {
    parent::Base($id, $parent, "", "", "", NULL, "New Banner", Array(
     "width" => "200",
     "height" => "200" ) );
    $this->html_dir = "{$this->datdir}/html";
    if ($this->i_have_created && ! is_dir($this->html_dir)) {
      mkdir($this->html_dir, 0755);
      if (($fd = fopen("{$this->html_dir}/index.html", "w"))) {
        fputs($fd, "<html><head><meta http-equiv='Pragma' " .
         "content='no-cache'></head><body>Banner ({$id})</body>" );
        fclose($fd);
      }
    }
  }
}
class Page extends Base {
  function Page($id, $parent) {
    parent::Base($id, $parent, "bn.lst", "bns", "bn", Window,
     "New Screen", Array() );
    $this->createNewChildIfNew(1);
  }
  function createNewWindow() {
    return ($this->createNewChild());
  }
  function getWindowIds() {
    return (parent::getChildrenIds());
  }
}
class ActiveBanner extends Base {
  function ActiveBanner($id, $parent) {
    parent::Base($id, $parent, "sc.lst", "scs", "sc", Page,
     "新規プロジェクト",
     Array(
      "stat" => "inactive",
      "refresh" => "3600",
      "arrange" => "horizontal",
      "vfrom" => "-",
      "vto" => "-",
      "path" => "/path/sample") );
    $this->createNewChildIfNew(1);
  }
  function createNewPage() {
    $pg = $this->createNewChild();
    $this->toTop($pg->id);
    return ($pg);
  }
  function getPageIds() {
    return ($this->getChildrenIds());
  }
  function getPage($id) {
    return ($this->getChild($id));
  }
  function removePage($id) {
    return (parent::removeChild());
  }
  function getTopWindow() {
    $pids = $this->getPageIds();
    if (count($pids) > 0) {
      $pg = $this->getChild($pids[0]);
      $wids = $pg->getChildrenIds();
      if (count($wids) > 0) {
        $wd = $pg->getChild($wids[0]);
        return ($wd);
      }
    }
    return (NULL);
  }
  function writeMeta() {
    parent::writeMeta();
    system("/usr/bin/abcpriv/linkabs");
  }
}
class ActiveBannerController extends Base {
  function ActiveBannerController() {
    global $_SERVER;
    $hostname = $_SERVER["HTTP_HOST"];
    if ($hostname) {
      $hostname = ereg_replace(":.*", "", $hostname);
    }
    $i = strchr($hostname, ".");
    if (! $hostname || ($i === NULL || $i === FALSE)) {
      $ip_addr = $_SERVER["SERVER_ADDR"];
      if ($ip_addr) {
        $hostname = gethostbyaddr($ip_addr);
      }
    }
    if (! $hostname) {
      $hostname = "www.example.com";
    }
    parent::Base(-1, NULL, "pj.lst", "pjs", "pj", ActiveBanner, "New ABC",
     Array(
     "docroot" => "/var/www/html",
     "abspath" => "/pjs",
     "server" => "http://$hostname" ));
  }
  function getActiveBannerIds() {
    return (parent::getChildrenIds());
  }
  function createNewActiveBanner($name = "") {
    $ab = parent::createNewChild();
    $this->toTop($ab->id);
    if ($name) {
      $ab->name = $name;
      $ab->writeMeta();
    }
    return ($ab);
  }
  function getActiveBanner($id) {
    return (parent::getChild($id));
  }
  function removeActiveBanner($id) {
    $ret = parent::removeChild($id);
    system("/usr/bin/abcpriv/linkabs");
    return ($ret);
  }
  function duplicate($id) {
    $new = parent::duplicate($id);
    $new->params["stat"] = "inactive";
    $new->writeMeta();
    return ($new);
  }
}
function insertHeader($topanchor = "") {
  ?>
<table BORDER=0 CELLSPACING=0 CELLPADDING=0 width=100% height=100%>
  <tr>
    <td>
      <table BORDER=0 CELLSPACING=0 CELLPADDING=0 width=100%>
        <tr>
          <td rowspan=2 valign=top><img src="img/top1.jpg" alt="" valign=top width=191></td>
          <td background="img/top2.jpg" width=100% height=54 nowrap></td>
          <td align=right valign=top><img src="img/top3.jpg" alt="Turbolinuxアクティブバナーコントローラ" width=329></td>
        </tr>
        <tr>
          <td width=100% height=32 nowrap bgcolor=#ffffff><br></td>
          <td valign=top align=right>
            <table border=0 cellpadding=0 cellspacing=0><tr>
              <td><a HREF=index<?= $topanchor ?> onMouseover=swImg('menu1','img/config-on.jpg') onMouseout=swImg('menu1','img/config-off.jpg')><img src=img/config-off.jpg ALT="トップ" name=menu1 BORDER=0></a></td>
              <td><a HREF=account onMouseover=swImg('menu2','img/account-on.jpg') onMouseout=swImg('menu2','img/account-off.jpg')><img src=img/account-off.jpg ALT="アカウント管理" name=menu2 BORDER=0></a></td>
              <td><a HREF=prop onMouseover=swImg('menu3','img/system-on.jpg') onMouseout=swImg('menu3','img/system-off.jpg')><img src=img/system-off.jpg ALT="システム設定" name=menu3 BORDER=0></a></td>
              <td><a HREF=../index onMouseover=swImg('menu4','img/logout-on.jpg') onMouseout=swImg('menu4','img/logout-off.jpg')><img src=img/logout-off.jpg ALT="ログアウト" name=menu4 BORDER=0></a></td>
            </tr></table>
          </td>
        </tr>
      </table>
    </td>
  </tr>
  <tr height=100%><td align=center valign=top>
  <?
}
function insertFooter () {
  ?>
  </td></tr>
  <tr><td width=100% nowrap background="img/bottom.gif" height=26 align=right><font size=-1 color=#ffffff>&copy;2005 <a href="http://www.turbolinux.co.jp/">Turbolinux, Inc.</a> All Rights Reserved.</td></tr>
</table>
  <?
}

class AccountMan {
  function AccountMan() {
    $this->accounts = Array();
    global $passwd_file_;
    $lines = Array();
    if (file_exists($passwd_file_) &&
     ($fd = fopen($passwd_file_, "r")) ) {
      $this->filename = $passwd_file_;
      while (! feof($fd)) {
        $lines[] = fgets($fd, 4096);
      }
      fclose($fd);
    } else {
      return;
    }
    foreach ($lines as $line) {
      $line = trim($line);
      if ($line) {
        list($uname, $pwhash, $rest) = explode(":", $line, 3);
        $this->accounts[$uname] = Array();
        $this->accounts[$uname]["pwhash"] = $pwhash;
        $this->accounts[$uname]["rest"] = $rest;
      }
    }
  }
  function authenticate($uname, $passwd) {
    if ($uname && array_key_exists($uname, $this->accounts) ) {
      $pwhash = $this->accounts[$uname]["pwhash"];
      if (crypt($passwd, $pwhash) == $pwhash ) {
        return (1);
      }
    }
  }
  function chpw($uname, $passwd) {
    if ($uname && array_key_exists($uname, $this->accounts)) {
      $this->accounts[$uname]["pwhash"] = crypt($passwd);
      $this->write();
    }
  }
  function useradd($uname, $passwd) {
    if ($uname && ! array_key_exists($uname, $this->accounts)) {
      $this->accounts[$uname] = Array();
      $this->accounts[$uname]["pwhash"] = crypt($passwd);
      $this->accounts[$uname]["rest"] = "";
      $this->write();
      return (1);
    }
    return (0);
  }
  function write() {
    $fd = fopen($this->filename, "w+");
    foreach ($this->accounts as $key => $val) {
      $pwhash = $this->accounts[$key]["pwhash"];
      $rest = $this->accounts[$key]["rest"];
      fputs($fd, "$key:$pwhash:$rest\n");
    }
    fclose($fd);
  }
  function userdel($uname) {
    unset($this->accounts[$uname]);
    $this->write();
  }
}
function insertBody() {
  ?>
<body BGCOLOR=#FFFFFF TEXT=#333333 LINK=#258FB8
 VLINK=#258FB8 ALINK=#996600 LEFTMARGIN=0 TOPMARGIN=0
 MARGINWIDTH=0 MARGINHEIGHT=0>
  <?
}
?>
