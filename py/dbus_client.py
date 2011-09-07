#!/usr/bin/python

import dbus

sessionbus = dbus.SessionBus()
remoteobj = sessionbus.get_object("com.ayutaya.ServiceFoo",
 "/com/ayutaya/ObjectFoo" )
foo = dbus.Interface(remoteobj, "com.ayutaya.InterfaceFoo")
retval = foo.hello("Hoge Fuga")
print "d1:", retval
print remoteobj.Introspect(
 dbus_interface = "org.freedesktop.DBus.Introspectable" )
