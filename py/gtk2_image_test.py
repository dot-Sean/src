#!/usr/bin/python

import gtk

window = gtk.Window()
image = gtk.Image()
#image.set_from_pixbuf(gtk.gdk.pixbuf_new_from_file("turbo-logo.png"))
image.set_from_file("turbo-logo.png")
window.add(image)
window.show_all()
gtk.gdk.flush()
#while gtk.events_pending():
#  gtk.main_iteration(gtk.FALSE)
gtk.main()
window.destroy()
