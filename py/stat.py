#!/bin/sh

"exec" "python" "-O" "$0" "$@"

import gtk
import threading

class StatWindow:
  def __init__(self, title, text):
    self.window = gtk.GtkWindow(gtk.WINDOW_POPUP)
    self.window.set_title(title)
    self.window.set_position(gtk.WIN_POS_CENTER)
    self.window.set_modal(gtk.TRUE)
    self.label = gtk.GtkLabel(text)
    self.label.set_line_wrap(gtk.TRUE)
    box = gtk.GtkFrame()
    box.set_border_width(8)
    box.add(self.label)
    box.set_shadow_type(gtk.SHADOW_NONE)
    frame = gtk.GtkFrame()
    frame.set_shadow_type(gtk.SHADOW_OUT)
    frame.add(box)
    self.window.add(frame)
    self.window.show_all()
  def pop(self):
    self.window.destroy()

class BackThread(threading.Thread):
  def __init__(self, statwin, func, * args):
    self.statwin = statwin
    self.func = func
    self.args = args
    threading.Thread.__init__(self)
  def run(self):
    self.func(self.statwin, * self.args)

def checkThread(thread):
  print "d1:", threading.currentThread().getName() 
  if not thread.isAlive():
    gtk.mainquit()
    return gtk.FALSE
  return gtk.TRUE

def doBackground(func, * args):
  statwin = StatWindow("Wait", "For me!")
  thread = BackThread(statwin, func, * args)
  thread.start()
  # in mili-sec
  gtk.timeout_add(100, checkThread, thread)
  print "d0:", threading.currentThread().getName() 
  gtk.mainloop()
  statwin.pop()

# --------------------------------------------------------------------

def funcBack(statwin, count):
  import time
  print "Went ..."
  n = count
  for i in range(n):
    print n - i
    statwin.label.set_text("d: %d" % (n - i,))
    time.sleep(1)
  print "Back!"

import signal
signal.signal(signal.SIGINT, signal.SIG_DFL)

doBackground(funcBack, 5)
