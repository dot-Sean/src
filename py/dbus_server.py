#!/usr/bin/python

import dbus.service

class ServiceObject(dbus.service.Object):
  def __init__(self, conn, object_path = "/com/ayutaya/ObjectFoo",
   bus_name = "com.ayutaya.ServiceFoo" ):
    dbus.service.Object.__init__(self, conn = conn,
     object_path = object_path,
     bus_name = dbus.service.BusName(bus_name, bus = conn) )
  @dbus.service.method("com.ayutaya.InterfaceFoo")
  def hello(self, msg):
    s = "Hello %s" % (str(msg),)
    print "d0:", s
    return s

import dbus.mainloop.glib
import gobject

dbus.mainloop.glib.DBusGMainLoop(set_as_default = True)
session_bus = dbus.SessionBus()
serviceobject = ServiceObject(conn = session_bus)
mainloop = gobject.MainLoop()
mainloop.run()
