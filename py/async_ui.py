import os

if os.environ.has_key("DISPLAY") and os.environ["DISPLAY"] != "": # {
  from gtk import *
  from gnome.ui import *
  class MainWindow(GtkDialog): # {
    def __init__(self, pid, stdin): # {
      self.stdin = stdin
      self.pid = pid
      self.timer = 0
      GtkDialog.__init__(self)
      self.set_title("Async Test")
      self.connect("destroy_event", self.killIt);
      self.connect("delete_event", self.killIt);
      self.set_border_width(4)
      self.progress = GtkProgressBar() # {
      self.progress.set_percentage(0)
      self.progress.set_bar_style(PROGRESS_CONTINUOUS)
      self.progress.show()
      self.vbox.pack_start(self.progress) # }
      self.button_ok = GtkButton("OK") # {
      self.button_ok.connect("clicked", self.killIt)
      self.button_ok.set_flags(CAN_DEFAULT)
      self.button_ok.grab_default()
      self.button_ok.show()
      self.action_area.pack_start(self.button_ok) # }
      self.timer = timeout_add(500, self.updateTimer, None)
    # }
    def killIt(self, * args): # {
      if self.timer:
        timeout_remove(self.timer)
        self.timer = 0
      self.hide()
      mainquit()
      return TRUE
    # }
    def updateTimer(self, data): # {
      try:
        (pid, stat) = os.waitpid(self.pid, os.WNOHANG)
      # The process does not exist.
      except OSError, e:
        self.killIt()
        return TRUE
      if 0:
        print self.pid, pid, "-", \
         os.WIFSTOPPED(stat), \
         os.WIFSIGNALED(stat), \
         os.WIFEXITED(stat), \
         os.WEXITSTATUS(stat), \
         os.WSTOPSIG(stat), \
         os.WTERMSIG(stat)
      while 1:
        import select
        ret = select.select([self.stdin], [], [], 0)
        # Input not available
        if len(ret[0]) == 0:
          break
        # Parsing should be more smart ...
        str = os.read(self.stdin, 16)
        if len(str) == 0:
          self.killIt()
          return TRUE
        import string
        try:
          progress = string.atoi(str)
        except ValueError, e:
          pass
        else:
          self.progress.update(float(progress) / float(100))
      return TRUE
    # }
    def run(self): # {
      import sys
      mainloop()
    # }
  # }
else: # } {
  from snack import *
  class MyGridForm(GridForm): # {
    def __init__(self, screen, pid, stdin, interval):
      print `screen.__dict__`
      self.screen = screen
      self.stdin = stdin
      self.interval = interval
      GridForm.__init__(self, screen, "Async Test", 1, 4)
      self.scale = Scale(40, 100)
      self.add(self.scale, 0, 0, (0, 0, 0, 0))
      self.bb = ButtonBar(screen, (("Ok", "ok"), ("Cancel", "cancel")))
      self.add(self.bb, 0, 1, (0, 1, 0, 0))
      #self.screen.resume()
      # setTimer() has been introduced after newt-0.50.8.
      self.setTimer(self.interval)
    def runUI(self): # {
      result = "TIMER"
      while result == "TIMER": # {
        result =  self.run()
        if result == "TIMER": # {
          while 1: # {
            import select
            ret = select.select([self.stdin], [], [], 0)
            if len(ret[0]) == 0: # {
              break
            # }
            str = os.read(self.stdin, 16)
            if len(str) == 0: # {
              result = "CHILD_DONE"
              break
            # }
            import string
            self.scale.set(string.atoi(str))
          # }
          self.setTimer(500)
        # }
      # }
    # }
  # }
# }
