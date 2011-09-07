<?
  # Get HTML in UTF-8
  function getHtmlUtf8 ($url, $input_encoding = "") {
    $fp = fopen($url, "r");
    $meta_data = stream_get_meta_data($fp);
    $html = stream_get_contents($fp);
    fclose($fp);
    $charset_pattern = "/charset=([^;\\s]+)/i";
    # Get encoding from response header entries
    if (! $input_encoding) {
      foreach ($meta_data["wrapper_data"] as $line) {
        if (count(($keyval = preg_split("/\\s*:\\s*/", $line, 2)) == 2)) {
          $key = $keyval[0];
          $val = $keyval[1];
          if ($key == "Content-Type" &&
           preg_match($charset_pattern, $val, $matches) ) {
            $input_encoding = trim($matches[1]);
          }
        }
      }
    }
    # Otherwise, get from the HTML meta tag
    if (! $input_encoding) {
      # 2nd byte of SJIS (ISO-2022 incompatible encoding) can be [<>]
      if (($html_utf8 = iconv("SJIS", "UTF-8", $html)) &&
       stristr($html_utf8, "</html>") ) {
        $html_to_be_checked = $html_utf8;
      } else {
        $html_to_be_checked = $html;
      }
      $html_ascii = preg_replace("/[^ -~]/", "", $html_to_be_checked);
      $html_ascii = preg_replace("@<body\\>.*</body>@", "<body/>",
       $html_ascii );
      $html_ascii = preg_replace("@<title\\>.*</title>@", "<title/>",
       $html_ascii );
      echo $html_ascii;
      $doc = new DOMDocument();
      $doc->loadHTML($html_ascii);
      $xpath = new DOMXPath($doc);
      $elems = $xpath->query("./head/meta[@http-equiv='Content-Type']");
      foreach ($elems as $elem) {
        if (preg_match($charset_pattern, $elem->getAttribute("content"),
         $matches )) {
          $input_encoding = trim($matches[1]);
        }
      }
    }
    # Failed to get
    if (! $input_encoding) {
      exit(1);
    }
    $input_encoding = strtoupper($input_encoding);
    # Some EUC-JP pages contain OMAJINAI character. Bad habit
    if ($input_encoding == "EUCJP" || $input_encoding == "EUC-JP") {
      $html = str_replace("\xFD\xFE", "", $html);
    }
    return iconv($input_encoding, "UTF-8", $html);
  }
  function getXhtml ($html) {
    $config = array(
     "indent"=> TRUE,
     "output-xhtml" => TRUE,
     "indent-spaces" => 2,
     "quote-nbsp" => FALSE );
    $tidy = tidy_parse_string($html, $config, "utf8");
    tidy_clean_repair($tidy);
    return (tidy_get_output($tidy));
  }
?>
