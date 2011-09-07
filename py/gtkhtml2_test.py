#!/usr/bin/python

import gtk
import gtkhtml2

class MainWindow(gtk.Window):
  def on_delete(self, * args):
    gtk.main_quit()
  def __init__(self):
    gtk.Window.__init__(self)
    self.connect("delete_event", self.on_delete);

    doc = gtkhtml2.Document()
    doc.clear()
    doc.open_stream("text/html")
    #doc.write_stream(open("/home/knaka/buildcfg-fuji/license.desktop_companion.ia32/EULA.html").read())
    doc.write_stream("<html><body>Hello World!</body></html>")
    doc.close_stream()

    view = gtkhtml2.View()
    view.set_document(doc)
    #view.connect('request_object', request_object)

    self.add(view)

import signal
signal.signal(signal.SIGINT, signal.SIG_DFL)
MainWindow().show_all()
gtk.main()
