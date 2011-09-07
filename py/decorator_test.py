#!/usr/bin/python

def decorator(func):
  def wrapper():
    print "Hello"
    func()
  return wrapper

@decorator
def myfunc1():
  print "World"

def myfunc():
  print "Monde"

myfunc2 = decorator(myfunc)

myfunc1()
myfunc2()
