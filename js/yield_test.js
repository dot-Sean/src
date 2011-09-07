<html>
<body>
<scirpt language=javascript>
document.write("hello<br>");
</script>
<script type="text/javascript; version=1.7">
function fib() {
  var i = 0, j = 1;
  while (true) {
    yield i;
    var t = i;
    i = j;
    j += t;
  }
}

var g = fib();
for (var i = 0; i < 10; i++) {
  document.write(g.next() + "<br>\n");
}
</script>
</body>
</html>
