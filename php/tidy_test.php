<?
  include("scrape_utils.php");
  //$url = "http://weather.yahoo.co.jp/weather/jp/13/4410/13113.html";
  //$url = "http://quote.yahoo.co.jp/q?s=3777";
  //$url = "http://www.traders.co.jp/domestic_stocks/domestic_market/foreign_funding/foreign_funding.asp";
  $url = "http://www.oliospec.com/item_detail/itemId,707/";
  $html_utf8 = getHtmlUtf8($url);
  $xhtml_utf8 = getXhtml($html_utf8);
  $doc = new DOMDocument();
  $doc->loadXML($xhtml_utf8);
  $xpath = new DOMXPath($doc);
  $xpath->registerNamespace("xhtml", "http://www.w3.org/1999/xhtml");
  $elems = $xpath->evaluate(".//xhtml:title");
  foreach ($elems as $elem) {
    echo trim($elem->nodeValue) . "\n";
  }
?>
