#!/usr/bin/python

import zipfile
import sys
import string

next = "90052"
input = zipfile.ZipFile("channel.zip")
while 1:
  name = "%s.txt" % (next,)
  sys.stdout.write(input.getinfo(name).comment)
  fields = string.split(input.read(name))
  next = fields[-1]
