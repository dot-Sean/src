#!/usr/bin/python

if __name__ == "__main__":
  import os
  (parent_stdin, child_stdout) = os.pipe()
  pid = os.fork()
  #pid = 1
  if pid == 0:
    # Child process must not have initialized gtk
    os.dup2(child_stdout, 1)
    import time
    import sys
    i = 0
    while i < 100:
      time.sleep(0.1)
      sys.stdout.write("%16d" % (i))
      sys.stdout.flush()
      i = i + 1
    sys.exit(0)
    raise Exception, "This code must not be reached."
  os.close(child_stdout)
  from async_ui import *
  if os.environ.has_key("DISPLAY") and os.environ["DISPLAY"] != "": # {
    dlg = MainWindow(pid, parent_stdin)
    dlg.show()
    dlg.run()
  else: # } {
    screen = SnackScreen()
    form = MyGridForm(screen, pid, parent_stdin, 500)
    form.runUI()
    screen.finish()
  # }
