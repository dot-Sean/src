#!/usr/bin/python

import urllib

#next = "12345"
next = "90052"
while 1:
  input = open("%s.txt" % (next,))
  a = input.readlines();
  print a
  input.close();
  fields = a[-1].split()
  next = fields[-1]
