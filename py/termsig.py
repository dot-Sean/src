#!/usr/bin/python

import signal
import time
import sys

def hoge(signum, frame):
  print "hoge"
  sys.exit(0)

signal.signal(signal.SIGTERM, hoge)

while 1:
  print "sleep"
  time.sleep(1)
