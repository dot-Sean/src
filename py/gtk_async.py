#!/usr/bin/env python

import sys
import os
import gtk
import signal

class MyWindow(gtk.GtkWindow):
  def close(self):
    if self.pinfo:
      if not self.isFinished():
        os.kill(self.pinfo.pid, signal.SIGKILL)
      self.flush()
    gtk.mainquit()
  def onCloseClicked(self, btn):
    self.close()
  def __init__(self):
    self.pinfo = None
    gtk.GtkWindow.__init__(self)
    self.connect("delete_event", lambda self, * args: sys.exit(0));
    vbox = gtk.GtkVBox() # {
    label = gtk.GtkLabel("hoge") # {
    label.show()
    vbox.pack_start(label) # }
    btn = gtk.GtkButton("close") # {
    btn.connect("clicked", self.onCloseClicked)
    btn.show()
    vbox.pack_start(btn) # }
    vbox.show()
    self.add(vbox) # }
  def flush(self):
    import select
    ret = select.select([self.pinfo.fromchild], [], [], 0)
    if len(ret[0]) > 0:
      sys.stdout.write(self.pinfo.fromchild.readline())
    pass
  def isFinished(self):
    return self.pinfo.poll() >= 0
  def onTimer(self):
    # Finished
    if self.isFinished():
      self.close()
    else:
      self.flush()
    return gtk.TRUE
  def execCmd(self):
    import popen2
    self.pinfo = popen2.Popen3("sleep 1 ; echo hoge ; sleep 1")
  def run(self):
    self.execCmd()
    # TODO: remove when quit
    gtk.timeout_add(100, self.onTimer)
    gtk.mainloop()

if __name__ == "__main__":
  signal.signal(signal.SIGINT, signal.SIG_DFL)
  wnd = MyWindow()
  wnd.show()
  wnd.run()
