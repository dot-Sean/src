#!/usr/bin/python

def devpath2uuid(devpath):
  import uuid
  import re
  import os
  re_uuid = re.compile("^(........-....-....-....-............)$")
  for line in os.popen("blkid -o value %s" % (devpath,), "r"):
    line = line.strip()
    #print line
    m = re_uuid.search(line)
    if m:
      return uuid.UUID(m.group(1))
  return None

uuid0 = devpath2uuid("/dev/sda1")
print uuid0
