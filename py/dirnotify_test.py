#!/usr/bin/python

import os
import sys
import signal
if not signal.__dict__.has_key("SIGRTMIN"):
  signal.SIGRTMIN = 32 + 3
  signal.SIGRTMAX = 63
import fcntl

class DirectoryNotifier:
  def sig_handler(self, signum, * args):
    pass
  def __init__(self, dir):
    self.fd = os.open(dir, os.O_RDONLY)
    if dir[0] == "/":
      self.dir = dir
    else:
      self.dir = "%s/%s" % (os.getcwd(), dir,)
    signal.signal(signal.SIGRTMIN + 0, self.sig_handler)
    fcntl.fcntl(self.fd, fcntl.F_SETSIG, signal.SIGRTMIN + 0);
    fcntl.fcntl(self.fd, fcntl.F_NOTIFY, \
     fcntl.DN_ACCESS | # read \
     fcntl.DN_MODIFY | # write, truncate \
     fcntl.DN_CREATE | \
     fcntl.DN_DELETE | \
     fcntl.DN_RENAME | \
     fcntl.DN_ATTRIB | # chmod, chown \
     fcntl.DN_MULTISHOT )
    self.prev_infos = self.get_infos()
  def get_infos(self):
    ret = {}
    for file in os.listdir(self.dir):
      ret[file] = os.stat("%s/%s" % (self.dir, file,))
    return ret
  def run(self):
    while 1:
      signal.pause()
      self.infos = self.get_infos()
      self.handler()
      self.prev_infos = self.infos
  def get_created_info(self):
    for key in self.infos.keys():
      try:
        self.prev_infos[key]
      except KeyError:
        return (key, self.infos[key],)
    return None
  def get_deleted_info(self):
    for key in self.prev_infos.keys():
      try:
        self.infos[key]
      except KeyError:
        return (key, self.prev_infos[key],)
    return None
  def get_modified_info(self):
    for key in self.infos.keys():
      try:
        if self.infos[key] != self.prev_infos[key]:
          return (key, (self.infos[key], self.prev_infos[key],),)
      except KeyError:
        pass
    return None
  def handler(self):
    created_info = self.get_created_info()
    print "C:", created_info
    modified_info = self.get_modified_info()
    print "M:", modified_info
    deleted_info = self.get_deleted_info()
    print "D:", deleted_info
    print "--------"

if __name__ == "__main__":
  notifier = DirectoryNotifier(sys.argv[1])
  notifier.run()
