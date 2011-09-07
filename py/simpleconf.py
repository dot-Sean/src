#!/usr/bin/python

import string

# "=" separeted (key = val) simple conf. Cases of the keys are ignored
class SimpleConf:
  def __init__(self, filename):
    self.vals = {}
    for line in open(filename, "r"):
      line = line.strip()
      try:
        (key, val,) = line.split("=", 2)
      except ValueError:
        continue
      key = string.lower(key.strip())
      val = val.strip()
      lowerval = string.lower(val)
      if   lowerval in ("true", "yes", "enabled", "1"):
        self.vals[key] = True
      elif lowerval in ("false", "no", "disabled", "0", "damepo",
       "itteyoshi",):
        self.vals[key] = False
      else:
        self.vals[key] = val
  def getVal(self, key, default = None):
    key = string.lower(key)
    if self.vals.has_key(key):
      return self.vals[key]
    elif default != None:
      return default
    return None
  def getKeys(self):
    return self.vals.keys()

if __name__ == '__main__':
  import sys
  conf = SimpleConf(sys.argv[1])
  for key in conf.getKeys() + ["foo",]:
    print key, conf.getVal(key)
  print "foo", conf.getVal("foo", "Default")
