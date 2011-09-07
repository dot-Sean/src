#!/usr/bin/python

import gnome.ui
import gtk

class GnyomeDialog(gtk.GtkWindow):
  def __init__(self, title):
    gtk.GtkWindow.__init__(self)
    self.set_title(title)
    self.vbox = gtk.GtkVBox()
    self.add(self.vbox)
    self.hbox = gtk.GtkHBox()
    self.vbox.pack_end(self.hbox)
  def append_button_with_pixmap(self, msg, btn_name):
    btn = gtk.GtkButton(msg, btn_name)
  def run_and_close(self):
    self.show_all()
    gtk.mainloop()

#d = gnome.ui.GnomeDialog("Hello")
d = GnyomeDialog("Hello")
d.append_button_with_pixmap("OK", "gtk-ok")
d.vbox.pack_start(gtk.GtkLabel("hello"))
d.show_all()
d.run_and_close()
