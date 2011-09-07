#!/usr/bin/python
#http://www.async.com.br/faq/pygtk/index.py?req=show&file=faq20.006.htp
#http://www.pygtk.org/pygtk2reference/gobject-functions.html#function-gobject--idle-add

import signal
import threading
import time
import gobject
import gtk

class JobThread(threading.Thread):
  def __init__(self, window):
    super(JobThread, self).__init__()
    self.window = window
  def stop(self):
    self.quit = True
  def appendLine(self, count):
    self.window.label.set_text("Counter: %i" % (count,))
  def run(self):
    self.quit = False
    for i in range(10):
      if self.quit:
        break
      gobject.idle_add(self.appendLine, i)
      time.sleep(0.5)

class AsyncExampleWindow(gtk.Window):
  def __init__(self):
    gtk.Window.__init__(self)
    self.jobthread = None
    self.connect("destroy", self.onDestroy)
    vbox = gtk.VBox()
    self.button = gtk.Button("Start")
    self.button.connect("clicked", self.onStartClicked)
    vbox.pack_start(self.button)
    self.label = gtk.Label()
    vbox.pack_start(self.label)
    self.add(vbox)
  def onStartClicked(self, widget):
    if self.jobthread and self.jobthread.isAlive():
      return
    self.jobthread = JobThread(self)
    self.jobthread.start()
    gobject.timeout_add(800, self.onTimeout)
  def onDestroy(self, * args):
    if self.jobthread:
      self.jobthread.stop()
    gtk.main_quit()
  def onTimeout(self):
    print "timer"
    return self.jobthread and self.jobthread.isAlive()

signal.signal(signal.SIGINT, signal.SIG_DFL)
gobject.threads_init()
window = AsyncExampleWindow()
window.show_all()
gtk.main()
