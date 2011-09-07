class Clock:
  def __getattr__(self, key):
    if key == "curtime":
      import time
      return time.localtime(time.time())
    return getattr(self, key)

clock = Clock()
print clock.curtime

