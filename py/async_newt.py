#!/usr/bin/python

import os
import sys
import time
import select
import threading

class JobThread(threading.Thread):
  def __init__(self):
    threading.Thread.__init__(self, None, None, "hoge")
    self.quit = False
  def stop(self):
    self.quit = True
  def appendLine(self, count):
    self.window.label.set_text("Counter: %i" % (count,))
  def run(self):
    for i in range(10):
      if self.quit:
        break
      #gobject.idle_add(self.appendLine, i)
      time.sleep(1)
      #print "d1:", self.quit, i
      os.system("echo d1: %d >> /tmp/tmp.log" % (i,))

def doit(jobthread):
  import snack
  class MyGridForm(snack.GridForm): # {
    def __init__(self, screen, jobthread):
      snack.GridForm.__init__(self, screen, "hello", 1, 4)
      self.interval = 1000
      self.bb = snack.ButtonBar(screen, (("OK", "ok",), ("Cancel", "cancel",),))
      self.add(self.bb, 0, 2)
      self.jobthread = jobthread
  
      #self.jobthread.start()
  
      #print "started 0"
      self.screen.suspend()
      print "started 1"
      #time.sleep(3)
      select.select([1], [], [], 1000000)
      print "started 2"
      self.screen.resume()
      #print "started 3"
  
      self.setTimer(self.interval)
    def exec_loop(self): # {
      result = "TIMER"
      while True:
        rc = self.run()
        if rc == "TIMER":
          pass
        elif isinstance(rc, snack.Button):
          button = self.bb.buttonPressed(rc)
          if button == "ok":
            #time.sleep(5)
            break
        else:
          raise Exception, "Unknown return code"
      self.jobthread.stop()
      #self.screen.suspend()
      #print "d0:", self.jobthread.quit
      #self.jobthread.join()
      #self.screen.resume()
  screen = snack.SnackScreen()
  form = MyGridForm(screen, jobthread)
  form.exec_loop()
  screen.finish()

class MainThread(threading.Thread):
  def __init__(self, jobthread):
    threading.Thread.__init__(self, None, None, "fuga")
    self.jobthread = jobthread
  def run(self):
    doit(self.jobthread)

try:
  #screen.suspend()
  jobthread = JobThread()
  jobthread.start()
  mainthread = MainThread(jobthread)
  mainthread.start()
  mainthread.join()
  #doit()
  jobthread.join()
except:
  raise
