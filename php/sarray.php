<?

class SArray {
  function SArray($filename) {
    $this->ver = "20050311";
    $this->filename = $filename;
    $this->cache_name = "$filename.idx";
    $this->fd = fopen($filename, "r");
    $this->lines = Array();
    if (file_exists($this->cache_name)) {
      $a = stat($this->filename);
      $file_mtime = $a["mtime"];
      $a = stat($this->cache_name);
      $cache_mtime = $a["mtime"];
      if ($file_mtime < $cache_mtime) {
        $this->fromCache();
      } else {
        $this->toCache();
      }
    } else {
      $this->toCache();
    }
    $this->num_lines = $this->idxinfo[1];
    $this->indexes = $this->idxinfo[2];
  }
  function fromCache() {
    trigger_error("*** fromCache()");
    $s = "";
    $fd_cache = fopen($this->cache_name, "r");
    while (! feof($fd_cache)) {
      $s .= fgets($fd_cache);
    }
    fclose($fd_cache);
    $this->idxinfo = unserialize($s);
    $cache_ver = $this->idxinfo[0];
    if ($cache_ver != $this->ver) {
      $this->toCache();
    }
  }
  function toCache() {
    trigger_error("*** toCache()");
    $num_lines = 0;
    $fd = $this->fd;
    while (! feof($fd)) {
      $indexes[] = ftell($fd);
      $line = "";
      while ((! feof($fd)) &&
       ((! $line) || (substr($line, strlen($line) - 1, 1) != "\n")) ) {
        $line .= fgets($fd);
      }
      $this->lines[] = $line;
      $num_lines ++;
    }
    $this->idxinfo = Array($this->ver, $num_lines, $indexes);
    $fd_cache = fopen($this->cache_name, "w+");
    if ($fd_cache) {
      fwrite($fd_cache, serialize($this->idxinfo));
      fclose($fd_cache);
    }
  }
  function get($line_index) {
    if ($this->lines[$line_index]) {
      trigger_error("*** Cached line");
      return ($this->lines[$line_index]);
    }
    trigger_error("*** Line from file");
    $fd = $this->fd;
    fseek($fd, $this->indexes[$line_index], SEEK_SET);
    $line = "";
    while ((! feof($fd)) &&
     ((! $line) || (substr($line, strlen($line) - 1, 1) != "\n")) ) {
      $line .= fgets($fd);
    }
    $this->lines[$line_index] = $line;
    return ($line);
  }
  function length() {
    return ($this->num_lines);
  }
}

$debug = 1;
ini_set("display_errors", ($debug)? "on": "off");
ini_set("error_reporting", ($debug)? E_ALL: 0);

$a = new SArray("/etc/fstab");

for ($i = $a->length(); $i >= 0; $i --) {
  echo $a->get($i);
}

?>
