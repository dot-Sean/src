#!/usr/bin/python

import sys
import os
import codecs

lines = sys.stdin.readlines()

inputenc = "utf-8"
try:
  codecs.lookup("japanese.euc_jp")
  output = sys.stdout
  outputenc = "japanese.euc-jp"
except LookupError:
  output = os.popen("iconv -f utf-8 -t euc-jp", "w")
  outputenc = "utf-8"

for line in lines:
  line = unicode(line, inputenc)
  output.write(line.encode(outputenc))
