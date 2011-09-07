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

import time
def sleeper():
  time.sleep(.001)
  return 1 # don't forget this otherwise the timeout will be removed
        
def doBackground(func, * args):
  print "cp1-0:", threading.currentThread().getName()
  statwin = StatWindow("Wait", "For me!")
  thread = BackThread(statwin, func, * args)
  print "cp1-0.1:", threading.currentThread().getName()
  thread.setDaemon(1)
  gtk.timeout_add(400,sleeper)
  thread.start()
  #gtk.threads_enter()
  #gtk.threads_leave()
  print "cp1-0.2:", threading.currentThread().getName()
  time.sleep(0)
  print "cp1-0.3:", threading.currentThread().getName()
  sys.stdout.write("cp1-1\n"); sys.stdout.flush()
  #time.sleep(10000)
  time.sleep(1)
  # in mili-sec
  #gtk.timeout_add(100, checkThread, thread)
  #gtk.threads_enter()
  sys.stdout.write("cp1-2: " + `gtk.main_level()` + "\n")
  sys.stdout.write("cp1-3\n"); sys.stdout.flush()
  gtk.threads_enter()
  win = gtk.MessageDialog(None, gtk.DIALOG_MODAL, \
   gtk.MESSAGE_INFO, gtk.BUTTONS_OK, "Hoge" )
  win.run()
  win.destroy()
  gtk.threads_leave()
  #gtk.mainloop()
  win.hide_all()
  del win
  thread.join()
  sys.stdout.write("cp1-4\n"); sys.stdout.flush()
  #gtk.threads_leave()
  statwin.pop()

# --------------------------------------------------------------------

import sys

def funcBack(statwin):
  #gtk.threads_enter()
  #gtk.threads_leave()
  import time
  print "Went ..."
  sys.stdout.write("cp2-0\n"); sys.stdout.flush()
  #statwin.grab_remove()
  sys.stdout.write("cp2-1: " + `gtk.main_level()` + "\n")
  sys.stdout.write("cp2-2: " + `threading.activeCount()` + "\n")
  #gtk.threads_leave()
  #gtk.threads_enter()
  sys.stdout.write("cp2-3\n"); sys.stdout.flush()
  #gtk.block_
  #gtk.threads_enter()
  win = gtk.MessageDialog(None, gtk.DIALOG_MODAL, \
   gtk.MESSAGE_INFO, gtk.BUTTONS_OK, "Hello" )
  #gtk.threads_leave()
  sys.stdout.write("cp2-3.1\n"); sys.stdout.flush()
  #gtk.threads_leave()
  sys.stdout.write("cp2-4\n"); sys.stdout.flush()
  win.show_all()
  win.run()
  win.destroy()
  win.hide_all()
  del win
  print "Back!"

#import signal
#for sig in range(signal.NSIG):
#  try:
#    signal.signal(sig, signal.SIG_DFL)
#  except ValueError:
#    pass
#  except RuntimeError:
#    pass

#signal.signal(signal.SIGINT, signal.SIG_DFL)

#gtk.threads_init()
sys.stdout.write("cp0-0: " + `gtk.main_level()` + "\n")

#win = gtk.MessageDialog(statwin, gtk.DIALOG_MODAL, \
# gtk.MESSAGE_INFO, gtk.BUTTONS_OK, "Hello" )
#win.show_all()
#win.run()
#win.hide_all()

doBackground(funcBack)
