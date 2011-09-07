#!/usr/bin/env python

from snack import *

class MyGridForm(GridForm):
  def __init__(self, screen):
    self.screen = screen
    GridForm.__init__(self, screen, "My Test", 1, 3)
    self.list1 = Listbox(5, scroll = 1)
    self.list1.setCallback(self.on_list1_changed)
    for i in range(10):
      self.list1.append("1: %d" % (i), i);
    self.add(self.list1, 0, 0, padding = (0, 0, 0, 1))
    self.list2 = Listbox(5, scroll = 1)
    self.add(self.list2, 0, 1, padding = (0, 0, 0, 1))
    #self.on_list1_changed()
    # --------------------------------------------------------------------
    self.bb = ButtonBar(screen, (("Ok", "ok"), ("Cancel", "cancel")))
    self.add(self.bb, 0, 2)
  def on_list1_changed(self):
    import sys
    #print(self.list2)
    c1 = self.list1.current()
    while 1:
      try:
        self.list2.delete(self.list2.current())
      except:
        break
    #del self.list2
    #self.list2 = Listbox(5, scroll = 1)
    #self.add(self.list2, 0, 1, padding = (0, 0, 0, 1))
    for i in range(8):
      self.list2.append("2: %d - %d" % (c1, i), i)
    self.screen.refresh()
  def execute(self):
    return self.runOnce()    

screen = SnackScreen()
form = MyGridForm(screen)
result = form.execute()
screen.finish()

print result
print "listbox:", li.current()
print "rb:", rb.getSelection()
print "bb:", bb.buttonPressed(result)
print "checkboxtree:", ct.getSelection()
