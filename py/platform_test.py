#!/usr/bin/python

import platform

(bits, linkage,) = platform.architecture("/bin/bash")
print "d0:", bits, linkage
print "d1:", platform.machine(), platform.node()
print "d2:", platform.platform()
print "d3:", platform.python_version(), platform.python_version_tuple()
print "d4:", platform.release()
print "d5:", platform.system(), platform.release(), platform.version(), \
 platform.system_alias(platform.system(), platform.release(),
 platform.version() )
print "d6:", platform.uname()
print "d7:", platform.dist()
print "d8:", platform.libc_ver()
