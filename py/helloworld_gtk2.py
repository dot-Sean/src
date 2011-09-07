#!/bin/sh

"exec" "python" "-O" "$0" "$@"

import time
import gtk
import threading

class StatWindow(gtk.Window):
  def __init__(self, title, text):
    gtk.Window.__init__(self, gtk.WINDOW_POPUP)
    self.set_title(title)
    self.set_position(gtk.WIN_POS_CENTER)
    self.set_modal(gtk.TRUE)
    self.label = gtk.Label(text)
    self.label.set_line_wrap(gtk.TRUE)
    box = gtk.Frame()
    box.set_border_width(8)
    box.add(self.label)
    box.set_shadow_type(gtk.SHADOW_NONE)
    frame = gtk.Frame()
    frame.set_shadow_type(gtk.SHADOW_OUT)
    frame.add(box)
    self.add(frame)
    self.show_all()
  def pop(self):
    self.destroy()

class BackThread(threading.Thread):
  def __init__(self, statwin, func, * args):
    self.statwin = statwin
    self.func = func
    self.args = args
    threading.Thread.__init__(self)
  def run(self):
    self.func(self.statwin, * self.args)

def checkThread(thread):
  #print "d1:", threading.currentThread().getName()
  if not thread.isAlive():
    gtk.mainquit()
    return gtk.FALSE
  return gtk.TRUE

statwin = None

def doBackground(func, * args):
  print "cp1-0:", threading.currentThread().getName()
  #statwin = StatWindow("Wait", "For me!")
  thread = BackThread(statwin, func, * args)
  thread.start()
  sys.stdout.write("cp1-1\n"); sys.stdout.flush()
  time.sleep(10000)
  # in mili-sec
  gtk.timeout_add(100, checkThread, thread)
  gtk.threads_enter()
  sys.stdout.write("cp1-2: " + `gtk.main_level()` + "\n")
  sys.stdout.write("cp1-3\n"); sys.stdout.flush()
  gtk.mainloop()
  sys.stdout.write("cp1-4\n"); sys.stdout.flush()
  gtk.threads_leave()
  statwin.pop()

# --------------------------------------------------------------------

import sys

def funcBack(statwin):
  import gtk
  import time
  print "Went ..."
  sys.stdout.write("cp2-0\n"); sys.stdout.flush()
  #statwin.grab_remove()
  sys.stdout.write("cp2-1: " + `gtk.main_level()` + "\n")
  sys.stdout.write("cp2-2: " + `threading.activeCount()` + "\n")
  sys.stdout.write("cp2-3\n"); sys.stdout.flush()
  #import pdb
  #pdb.set_trace()
  gtk.threads_enter()
  win = gtk.MessageDialog(statwin, gtk.DIALOG_MODAL, \
   gtk.MESSAGE_INFO, gtk.BUTTONS_OK, "Hello" )
  gtk.threads_leave()
  sys.stdout.write("cp2-4\n"); sys.stdout.flush()
  win.show_all()
  win.run()
  print "Back!"

import signal
signal.signal(signal.SIGINT, signal.SIG_DFL)

gtk.threads_init()
sys.stdout.write("cp0-0: " + `gtk.main_level()` + "\n")

#win = gtk.MessageDialog(statwin, gtk.DIALOG_MODAL, \
# gtk.MESSAGE_INFO, gtk.BUTTONS_OK, "Hello" )
#win.show_all()
#win.run()

doBackground(funcBack)

def main():
  thread = threading.Thread()
  thread.run()

main()