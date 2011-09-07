#!/usr/bin/python

import sys
import string

sys.path.append("/home/knaka/bin/")

from plre import RegExp

class ConfigFile:
  def recover(self):
    lines = self.lines
    self.lines = []
    i = 0;
    while (i < len(lines)):
      line = lines[i]
      if line == self.begcmt:
        i = i + 1
        line = lines[i]
        line = line[len(self.cmt):]
        i = i + 1
      elif line == self.begadd:
        i = i + 3
        continue
      self.lines.append(line)
      i = i + 1
  def readlines(self):
    return self.lines
  def __init__(self, obj, \
   name = "REWCONF",
   val_re = ".*",
   cmt = "#",
   cmt_re = "#[ \t]*",
   sep = " ",
   sep_re = "[ \t]+",
  ):
    self.name = name
    self.cmt = cmt
    self.cmt_re = cmt_re
    self.sep = sep
    self.sep_re = sep_re
    self.val_re = val_re
    self.infile = ""
    self.begcmt = "%s BEGIN_%s_CMTOUT" % (self.cmt, self.name,)
    self.endcmt = "%s END_%s_CMTOUT" % (self.cmt, self.name,)
    self.begadd = "%s BEGIN_%s_ADDED" % (self.cmt, self.name,)
    self.endadd = "%s END_%s_ADDED" % (self.cmt, self.name,)
    if type(obj) == type(sys.stdout):
      input = obj
    elif type(obj) == type(""):
      self.infile = obj
      input = open(self.infile, "r")
    else:
      raise Exception
    self.lines = []
    for line in input.readlines():
      self.lines.append(string.rstrip(line))
  def write(self):
    output = open(self.infile, "w")
    for line in self.lines:
      output.write(line + "\n")
    output.close()
  def getItemInfo(self, key, commented = 0):
    i = 0;
    cmt_re = ""
    if commented:
      cmt_re = self.cmt_re
    reLine = RegExp("^(%s)(%s)(%s)(%s)" % \
     (cmt_re, key, self.sep_re, self.val_re,) )
    for line in self.lines:
      if reLine.search(line):
        return (i, reLine[4],)
      i = i + 1
    return (-1, None,)
  def __getitem__(self, key):
    return self.getItemInfo(key)[1]
  def __setitem__(self, key, new_val):
    newline = "%s%s%s" % (key, self.sep, new_val,)
    for fCommented in (0, 1,):
      (lineno, val,) = self.getItemInfo(key, fCommented)
      if lineno >= 0:
        if fCommented == 0 and val == new_val:
          pass
        else:
          if self.lines[lineno - 1] == self.begadd:
            self.lines[lineno] = newline
          else:
            self.lines[lineno] = self.cmt + self.lines[lineno]
            self.lines.insert(lineno + 0, self.begcmt)
            self.lines.insert(lineno + 2, self.endcmt)
            self.lines.insert(lineno + 3, self.begadd)
            self.lines.insert(lineno + 4, newline)
            self.lines.insert(lineno + 5, self.endadd)
        break
    else:
      self.lines.append(self.begadd)
      self.lines.append(newline)
      self.lines.append(self.endadd)

if __name__ == '__main__':

  #cfile = ConfigFile("sample.conf", \
  cfile = ConfigFile(sys.stdin, \
   cmt = ";", \
   cmt_re = "[ \t]*;[ \t]*",
   sep = " = ", \
   sep_re = "[ \t]*=[ \t]*",
   val_re = "[a-zA-Z0-9]+",
  )
  cfile.recover()
  cfile["fuga"] = "OnOn"
  cfile["hare"] = "OffOff"
  for line in cfile.readlines():
    print line

  #import sys
  #import getopt
  #(opts, args) = getopt.getopt(sys.argv[1:],
  # "rn:V:c:C:s:S:i:",
  # (
  #  "recov",
  #  "name=",
  #  "val_re=",
  #  "cmt=",
  #  "cmt_re=",
  #  "sep=",
  #  "sep_re=",
  #  "input=",
  # )
  #)
  #print opts
  #print args
