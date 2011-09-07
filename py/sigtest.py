#!/usr/bin/python

def handler(* args):
  print "d:", args[0], args[1], dir(args)
  signal.alarm(1)

import signal
print "d0:", signal.signal(signal.SIGALRM, handler)
signal.alarm(1)
while 1:
  pass

