#!/usr/bin/python

import copy

class Base:
  def __init__(self):
    self.n0 = 128

class Derived1(Base):
  def __init__(self):
    Base.__init__(self)
    self.n1 = 256

class Derived2(Base):
  def __init__(self):
    Base.__init__(self)
    self.n2 = 512

import copy

def downCopy(derived, base):
  for key in  base.__dict__.keys():
    base.__dict__[key] = copy.deepcopy(derived.__dict__[key])
  return base

def upCopy(base, derived):
  for key in  base.__dict__.keys():
    derived.__dict__[key] = copy.deepcopy(base.__dict__[key])
  return derived

derived1 = Derived1()
derived1.n0 = 2048
base = downCopy(derived1, Base())
print base.__dict__
derived2 = upCopy(base, Derived2())
print derived2.__dict__
