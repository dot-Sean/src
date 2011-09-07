#!/usr/bin/python

import urllib

#next = "12345"
next = "46145"
while 1:
  input = urllib.urlopen("http://www.pythonchallenge.com/pc/def/linkedlist.php?nothing=%s" % (next,));
  a = input.readlines();
  print a
  input.close();
  fields = a[-1].split()
  next = fields[-1]
