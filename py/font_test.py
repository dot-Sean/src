#!/usr/bin/env python

from gtk import *

class MyWindow(GtkWindow):
  def __init__(self):
    GtkWindow.__init__(self)
    self.connect("destroy_event", lambda self, * args: sys.exit(0));
    self.connect("delete_event", lambda self, * args: sys.exit(0));
    box = GtkVBox() # {
    label = GtkLabel("hoge") # {
    label.show()
    box.pack_start(label) # }
    label = GtkLabel("fuga") # {
    label.show()
    box.pack_start(label) # }
    label = GtkLabel("foo") # {
    label.show()
    box.pack_start(label) # }
    label = GtkLabel("bar") # {
    label.show()
    box.pack_start(label) # }
    box.show()
    self.add(box) # }
  def run(self):
    mainloop()

if __name__ == "__main__":
  wnd = MyWindow()
  wnd.show()
  wnd.run()

-alias-fixed-medium-r-normal-*-*-100-*-*-c-*-jisx0208.1983-0
-alias-fixed-medium-r-normal-*-*-120-*-*-c-*-jisx0208.1983-0
-alias-fixed-medium-r-normal-*-*-160-*-*-c-*-jisx0208.1983-0
-alias-fixed-medium-r-normal-*-*-180-*-*-c-*-jisx0208.1983-0
