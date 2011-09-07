#!/usr/bin/python
# -*- coding: utf-8 -*-

class Describable(object):
  def __init__(self):
    print "Describable constructed"
  def describe(self):
    return self._getDescription()
  def _getDescription(self):
    raise NotImplementedError

class Base(object):
  def __init__(self):
    print "Base constructed"
  @classmethod
  def factory(cls, n):
    if (n % 2) == 0:
      base = DerivedA()
    else:
      base = DerivedB()
    return base
  def getName(self):
    return "Basic"

class DerivedA(Base):
  def __init__(self):
    super(DerivedA, self).__init__()
    print "DerivedA constructed"
  def getName(self):
    return "DerivedA/%s" % (Base.getName(self))

class DerivedB(Base, Describable):
  def __init__(self):
    super(DerivedB, self).__init__()
    Describable.__init__(self)
    print "DerivedB constructed"
  def getName(self):
    self.describe()
    return "DerivedB"
  def _getDescription(self):
    return "Hello, World"

l = []
l.append(Base.factory(255))
l.append(Base.factory(256))
l.append(Base.factory(257))
for base in l:
  print "d1:", base.getName()
d = {}
d["One"] = 1
d["Two"] = 2
d["Three"] = 3
print d.keys()
print d.values()
