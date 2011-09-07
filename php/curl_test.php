  function getHtml ($url) {
    global $buf;
    $input_encoding = "";
    $curl = curl_init();
    curl_setopt($curl, CURLOPT_URL, $url);
    curl_setopt($curl, CURLOPT_HEADER, 1);
    function onWrite($curl, $str) {
      global $buf;
      $buf .= $str;
      return strlen($str);
    }
    curl_setopt($curl, CURLOPT_WRITEFUNCTION, "onWrite");
    $buf = "";
    $ret = curl_exec($curl);
    $header_size = curl_getinfo($curl, CURLINFO_HEADER_SIZE);
    curl_close($curl);
    $header = substr($buf, 0, $header_size);
    # yum install php-devel
    # pecl install pecl_http (with default values)
    # says 'You should add "extension=http.so" to php.ini'
    $header = http_parse_headers($header);
    print_r($header);
    if (! $input_encoding) {
      if (array_key_exists("Content-Type", $header) &&
       preg_match("/charset=([^\s]+)/", $header["Content-Type"], $matches) ) {
        $input_encoding = trim($matches[1]);
      }
    }
    if (! $input_encoding) {
      $input_encoding = "sjis";
    }
    if (! $input_encoding) {
      echo "Oops\n";
      exit(1);
    }
    $html = substr($buf, $header_size);
    $input_encoding = strtoupper($input_encoding);
    # Some EUC-JP pages contain OMAJINAI character
    if ($input_encoding == "EUC-JP" || $input_encoding == "EUCJP") {
      $html = str_replace("\xFD\xFE", "", $html);
    }
    #echo "d: $input_encoding\n";
    return iconv($input_encoding, "UTF-8", $html);
  }
