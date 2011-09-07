#!/usr/bin/python

import sys

def dprint(str):
  frame = sys._getframe(1)
  code = frame.f_code
  print "* %s(%d): %s" % (code.co_filename, frame.f_lineno, str,)
  # code.co_name

class Hoge:
  def func1(self):
    dprint("Hoge")

hoge = Hoge()
hoge.func1()
