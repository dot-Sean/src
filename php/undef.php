<?

function my_sha1($str) {
  if (function_exists("sha1")) {
    return sha1($str);
  } else {
    return `echo -n 'hogefuga' | sha1sum | sed -e 's/ .*//'`;
  }
}

echo my_sha1("hogefuga");
echo "\n";
echo `echo -n 'hogefuga' | sha1sum | sed -e 's/ .*//'`;

?>
