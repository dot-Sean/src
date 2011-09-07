#!/usr/bin/php
<?
$str = "http:// https:// http://";
echo preg_match_all("@https?://@", $str, $a);
?>
