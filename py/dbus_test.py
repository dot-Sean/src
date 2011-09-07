#!/usr/bin/python

# http://dbus.freedesktop.org/wiki/
# http://www-6.ibm.com/jp/developerworks/linux/040827/j_l-dbus.html

import dbus
bus = dbus.SystemBus()
proxy = bus.get_object("org.freedesktop.NetworkManager",
 "/org/freedesktop/NetworkManager/Devices/eth0" )
