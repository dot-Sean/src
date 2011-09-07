import threading
import time
import threading

class tail_recursive(object):
    def __init__(self, func):
        self.CONTINUE = object()
        self.func = func
        self.firstcall = True
    def __call__(self, *args, **kwd):
        if self.firstcall:
            print "cp"
            func = self.func
            CONTINUE = self.CONTINUE
            self.firstcall = False
            try:
                while True:
                    result = func(*args, **kwd)
                    if result is CONTINUE: # update arguments
                        args, kwd = self.argskwd
                    else: # last call
                        return result
            finally:
                self.firstcall = True
        else: # return the arguments of the tail call
            self.argskwd = args, kwd
            return self.CONTINUE

@tail_recursive
def even(n):
    time.sleep(0.001)
    if n == 0:
        return True
    else:
        return odd(n-1)
def odd(n):
    if n == 0:
        return False
    else:
        return even(n-1)

class TestThread(threading.Thread):
  def __init__(self, wait):
    self.wait = wait
    threading.Thread.__init__(self, name = "Test")
  def run(self):
    #time.sleep(self.wait)
    time.sleep(1)
    for i in range(3):
      time.sleep(0.1)
      print "{0} {1}".format(i, even(10000))

threads = []
for i in range(3):
  t = TestThread(i)
  threads.append(t)
  t.start()

for t in threads:
  t.join()

