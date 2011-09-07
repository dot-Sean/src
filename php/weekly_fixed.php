<html>
<body>
<?
function myname() {
  global $HTTP_SERVER_VARS;
  return $HTTP_SERVER_VARS["HTTP_HOST"] . $HTTP_SERVER_VARS["PHP_SELF"];
}
global $_GET;
$now = 0 + time();
$year = 0 + $_GET["year"];
if (! $year) {
  $year = 0 + strftime("%Y", $now);
}
$prev_year = $year - 1;
$next_year = $year + 1;
echo "<p><a href=http://" . myname() . "?year=$prev_year>Prev</a> / <a href=http://" . myname() . "?year=$next_year>Next</a><p>";
for (
 $first_sunday = mktime(0, 0, 0, 1, 1, $year);
 strftime("%u", $first_sunday) != 7;
 $first_sunday = strtotime("-1 day", $first_sunday) ) {
  ;
}
for ($i = 0; ; $i ++) {
  $from = strtotime(sprintf("+%s week", $i), $first_sunday);
  $to = strtotime("+7 day", $from) - 1;
  $from_year = strftime("%Y", $from);
  $from_month = strftime("%m", $from);
  $from_day = strftime("%d", $from);
  if ($year < $from_year) {
    break;
  }
  $to_year = strftime("%Y", $to);
  $to_month = strftime("%m", $to);
  $to_day = strftime("%d", $to);
  $url = sprintf('https://bts.turbolinux.co.jp/bugzilla/buglist.cgi?query_format=advanced&short_desc_type=allwordssubstr&short_desc=&long_desc_type=substring&long_desc=&bug_file_loc_type=allwordssubstr&bug_file_loc=&keywords_type=allwords&keywords=&bug_status=UNCONFIRMED&bug_status=RESOLVED&bug_status=VERIFIED&bug_status=CLOSED&emailassigned_to1=1&email1=&emailtype1=substring&emailassigned_to2=1&emailreporter2=1&emailqa_contact2=1&emailcc2=1&email2=&emailtype2=substring&bugidtype=include&bug_id=&chfieldfrom=%04d-%02d-%02d&chfieldto=%04d-%02d-%02d&chfield=resolution&chfieldvalue=Fixed&cmdtype=doit&order=Reuse+same+sort+as+last+time&field0-0-0=noop&type0-0-0=noop&value0-0-0=', $from_year, $from_month, $from_day, $to_year, $to_month, $to_day);
  $fmt = "%Y/%m/%d (%a)";
  if ($from <= $now) {
    ?>
    <a href=<?= $url ?>><?= strftime($fmt, $from) ?> - <?= strftime($fmt, $to) ?></a>
    <?
    if ($now <= $to) {
      echo "&lt";
    }
  } else {
    ?>
    <?= strftime($fmt, $from) ?> - <?= strftime($fmt, $to) ?>
    <?
  }
  ?>
  <br>
  <?
}
?>
</body>
</html>
