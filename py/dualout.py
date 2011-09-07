#!/usr/bin/python

import os
import sys

output = open("/tmp/tmp.txt", "w")

input = os.popen("while true; do echo hoge; sleep 1; done")
while 1:
  line = input.readline()
  sys.stdout.write(line)
  sys.stdout.flush()
  output.write(line)
  output.flush()

output.close()

