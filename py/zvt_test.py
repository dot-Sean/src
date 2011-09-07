import os

from gtk import *
from gnome.zvt import *

class TestWindow(Window): # {
  def on_child_died(self, zvt, hoge):
    zvt.reset(1)
    zvt.killchild(9)
    zvt.closepty()
  #def on_destroy(self, * args):
  #  mainquit()
  #def on_delete(self, * args):
  #  mainquit()
  #  return 1
  def __init__(self):
    self.result = "cancel"
    Window.__init__(self, type = WINDOW_TOPLEVEL)
    self.set_size_request(640, 480)
    self.set_title("Test Window")
    #self.connect("destroy_event", self.on_destroy);
    #self.connect("delete_event", self.on_delete);
    table = Table(1, 1) # {
    #self.zvt = Term(80, 24) # {
    self.zvt = Term(80, 24) # {
    self.zvt.connect("child_died", self.on_child_died, self.zvt)
    rc = self.zvt.forkpty()
    if rc == -1:
      print "Error!"
      import sys
      sys.exit(1)
    if rc == 0:
      env = os.environ
      cmd = "/bin/sh";
      os.execve(cmd, (cmd,), env)
    self.zvt.show()
    #self.timer = timeout_add(100, self.on_timer, None)
    #self.zvt.set_size(80, 25)
    table.attach(self.zvt, 0, 1, 0, 1, EXPAND | FILL,
     EXPAND | FILL, 5, 5 ) # }
    self.add(table) # }
    table.show()
  def on_timer(self, data): # {
    try:
      window = self.get_window()
      self.set_usize(window.width, window.height)
    except:
      return 1
    return 0
  # }
  def run_ui(self):
    self.show_all()
    #mainloop()
    #return self.result

class MainWindow(Window):
  def __init__(self):
    Window.__init__(self, type = WINDOW_TOPLEVEL)
    btn = Button("test")
    btn.connect("clicked", self.on_clicked)
    self.add(btn)
  def on_clicked(self, widget, * args):
    wnd = TestWindow()
    wnd.show()
    wnd.run_ui()
  def run_ui(self):
    self.show_all()
    mainloop()

wnd = MainWindow()
wnd.run_ui()
