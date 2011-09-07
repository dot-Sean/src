#!/usr/bin/python

# Too late?

import urllib
input = urllib.urlopen("http://www.ayutaya.com/")
for line in input.readlines():
  line = line.strip()
  print "d:", line
