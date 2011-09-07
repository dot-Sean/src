#!/usr/bin/python

import re
import string
import sys

output = sys.stdout

def capitalize(m):
  s = m.group(0)
  return string.upper(s[0]) + s[1:]

r = re.compile("[a-z]+");
for line in open("/etc/fstab", "r").readlines():
  # default: all replacement, count = ...
  line = r.sub(capitalize, line)
  output.write(line)
