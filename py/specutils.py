#!/usr/bin/env python

import os
import sys
import rpm

class rpmSpec:
  def __init__(self,specpath=None):
    self.spec=None
    if(specpath):
      self.parseSpec(specpath)

  def parseSpec(self,specpath):
    ts = rpm.TransactionSet()
    self.spec = ts.parseSpec(specpath)

  def getSources(self):
    if not self.spec : return
    source=[]
    patch=[]
    for (name,nr,type) in self.spec.sources():
      if type == 1:
  	  source.insert(nr,name)
      elif type == 2:
	  patch.insert(nr,name)
    return (source,patch)
  
  def getBuild(self):
    if not self.spec : return
    return self.spec.build()
  def getBuildRoot(self):
    if not self.spec : return
    return self.spec.buildRoot()
  def getClean(self):
    if not self.spec : return
    return self.spec.clean()
  def getInstall(self):
    if not self.spec : return
    return self.spec.install()
  def getPrep(self):
    if not self.spec : return
    return self.spec.prep()

if __name__=="__main__":
  spec=rpmSpec(sys.argv[1])

  rpm.addMacro("_topdir", "/tmp/")
  ts = rpm.ts()
  spec = ts.parseSpec(sys.argv[1])
  print dir(ts)
  print dir(spec)

