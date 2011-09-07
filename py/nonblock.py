#!/usr/bin/python

import os
import sys
import fcntl
import subprocess
import time

fcntl.fcntl(sys.stdin.fileno(), fcntl.F_SETFL, \
 fcntl.fcntl(sys.stdin.fileno(), fcntl.F_GETFL) | os.O_NONBLOCK )

p = subprocess.Popen(("for i in 0 1 2; do date; sleep 2; done; echo Done",), \
 shell = True, \
 stdin = subprocess.PIPE, stdout = subprocess.PIPE, stderr = None )

#p = subprocess.Popen(("while read i; do echo d: $i; done",), \
# shell = True, \
# stdin = subprocess.PIPE, stdout = subprocess.PIPE, stderr = None )

fcntl.fcntl(p.stdout.fileno(), fcntl.F_SETFL, \
 fcntl.fcntl(p.stdout.fileno(), fcntl.F_GETFL) | os.O_NONBLOCK )

class MyExit(Exception): pass
while 1:
  ret = p.poll()
  if ret:
    # The process has finished.
    break
  try:
    # Read all the buffered stdin lines and write them to the subprocess
    while 1:
      p.stdin.write(sys.stdin.readline())
  # nonblock input causes IOError if no data can be read
  except IOError, e:
    pass
  try:
    # Read all from the subprocess
    while 1:
      s = p.stdout.readline()
      # EOF
      if len(s) == 0:
        raise MyExit, "MyExit"
      s = s.strip()
      print "d (%d):" % (len(s),), s
  except IOError, e:
    print "sleeping ..."
    time.sleep(0.5)
  except MyExit, e:
    break
del p
