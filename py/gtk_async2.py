#!/usr/bin/env python

import sys
import os
import gtk
import signal
import threading

class StatWin(gtk.GtkWindow):
  class SimpleThread(threading.Thread):
    def __init__(self, job, setMsg):
      self.job = job
      self.setMsg = setMsg
      threading.Thread.__init__(self)
    def run(self):
      self.job(self.setMsg)
  def close(self):
    # Any way to stop the thread?
    if self.thread.isAlive():
      #self.thread.join(0)
      # Is this correct?
      self.thread._Thread__stop()
    gtk.timeout_remove(self.timer_tag)
    gtk.mainquit()
  def onCloseClicked(self, btn):
    self.close()
  def setMsg(self, msg):
    self.label.set_text(msg)
  def __init__(self):
    gtk.GtkWindow.__init__(self)
    self.connect("delete_event", self.close);
    vbox = gtk.GtkVBox(gtk.FALSE, 8) # {
    self.label = gtk.GtkLabel("XXXXXXXXXX") # {
    self.label.show()
    vbox.pack_start(self.label) # }
    btn = gtk.GtkButton("Close") # {
    btn.connect("clicked", self.onCloseClicked)
    btn.show()
    vbox.pack_start(btn) # }
    vbox.show()
    self.add(vbox) # }
  def onTimer(self):
    # Finished
    if not self.thread.isAlive():
      self.close()
    return gtk.TRUE
  def run(self, job):
    self.thread = self.SimpleThread(job, self.setMsg)
    self.thread.start()
    self.timer_tag = gtk.timeout_add(100, self.onTimer)
    gtk.mainloop()

import time

def jobHoge(setMsg):
  setMsg("hoge")
  time.sleep(1)
  setMsg("fuga")
  time.sleep(1)

def jobFoo(setMsg):
  setMsg("foo")
  time.sleep(1)
  setMsg("bar")
  time.sleep(1)

if __name__ == "__main__":
  signal.signal(signal.SIGINT, signal.SIG_DFL)
  wnd = StatWin()
  wnd.show()
  wnd.run(jobHoge)
  wnd.hide()
  time.sleep(1)
  wnd.show()
  wnd.run(jobFoo)
  del wnd

