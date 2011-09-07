#!/usr/bin/env python

import os
import sys
import rpm

class Package:
  def __init__(self, ts, path):
    self.path = path
    fd = os.open(path, os.O_RDONLY)
    self.header = ts.ts.hdrFromFdno(fd)
    os.close(fd)
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
    if not key:
      retval = None
    elif key == "name":
      retval = self.header[rpm.RPMTAG_NAME]
    elif key == "requires":
      retval = self.header[rpm.RPMTAG_REQUIRES]
    else:
      retval = None
    return retval
  def isSource(self):
    return (self.header[rpm.RPMTAG_SOURCEPACKAGE] == 1)

class TransactionSet:
  def __init__(self):
    self.ts = rpm.TransactionSet()
  def addPackageToBeInstalled(self, pkg):
    self.ts.addInstall(pkg.header, (pkg.header, pkg.path,), "i")
  def callback(self, what, bytes, total, h, user):
    retval = None
    if   what == rpm.RPMCALLBACK_TRANS_START:
      print "RPMCALLBACK_TRANS_START"
    elif what == rpm.RPMCALLBACK_TRANS_PROGRESS:
      print "RPMCALLBACK_TRANS_PROGRESS"
    elif what == rpm.RPMCALLBACK_TRANS_STOP:
      print "RPMCALLBACK_TRANS_STOP"
    elif what == rpm.RPMCALLBACK_INST_OPEN_FILE:
      print "RPMCALLBACK_INST_OPEN_FILE"
      (header, path,) = h
      # Must be free()d
      fd = os.open(path, os.O_RDONLY)
      retval = fd
    elif what == rpm.RPMCALLBACK_INST_CLOSE_FILE:
      print "RPMCALLBACK_INST_CLOSE_FILE"
    elif what == rpm.RPMCALLBACK_INST_PROGRESS:
      print "RPMCALLBACK_INST_PROGRESS"
    elif what == rpm.RPMCALLBACK_UNINST_START:
      print "RPMCALLBACK_UNINST_START"
    elif what == rpm.RPMCALLBACK_UNINST_PROGRESS:
      print "RPMCALLBACK_UNINST_PROGRESS"
    elif what == rpm.RPMCALLBACK_UNINST_STOP:
      print "RPMCALLBACK_UNINST_STOP"
    elif what == rpm.RPMCALLBACK_REPACKAGE_START:
      print "RPMCALLBACK_REPACKAGE_START"
    elif what == rpm.RPMCALLBACK_REPACKAGE_STOP:
      print "RPMCALLBACK_REPACKAGE_STOP"
    elif what == rpm.RPMCALLBACK_REPACKAGE_PROGRESS:
      print "RPMCALLBACK_REPACKAGE_PROGRESS"
    elif what == rpm.RPMCALLBACK_CPIO_ERROR:
      print "RPMCALLBACK_CPIO_ERROR"
    elif what == rpm.RPMCALLBACK_UNPACK_ERROR:
      print "RPMCALLBACK_UNPACK_ERROR"
    return retval
  def run(self):
    self.ts.run(self.callback, "")

if __name__ == "__main__":
  ts = TransactionSet()
  pkg = Package(ts, sys.argv[1])
  ts.addPackageToBeInstalled(pkg)
  ts.run()
