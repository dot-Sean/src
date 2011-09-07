import os
import rpm

class Package:
  def __init__(self, ts, path):
    self.path = path
    fd = os.open(path, os.O_RDONLY)
    self.header = ts.hdrFromFdno(fd)
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
    elif key == "version":
      retval = self.header[rpm.RPMTAG_VERSION]
    elif key == "release":
      retval = self.header[rpm.RPMTAG_RELEASE]
    elif key == "requires":
      retval = self.header[rpm.RPMTAG_REQUIRES]
    else:
      retval = None
    return retval
  def isSource(self):
    return (self.header[rpm.RPMTAG_SOURCEPACKAGE] == 1)

def compareRpm(lhs, rhs):
  if lhs["name"] == rhs["name"] and lhs["serial"] != rhs["serial"]:
    return int(lhs["serial"]) - int(rhs["serial"])
  return rpm.labelCompare( \
   (lhs["name"], lhs["version"], lhs["release"],), \
   (rhs["name"], rhs["version"], rhs["release"],) )
