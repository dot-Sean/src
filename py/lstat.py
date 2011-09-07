#!/usr/bin/python

import os
import stat
import time

print os.stat("/dev/ida/c0d0p5")

(st_mode, st_ino, st_dev, st_nlink, st_uid, st_gid, st_size, st_atime,
 st_mtime, st_ctime ) = os.stat("//etc/fstab")
diff = time.time() - st_mtime
print "%02dhr %02dmn" % (diff / (60 * 24), (diff / 60) % 60,)
