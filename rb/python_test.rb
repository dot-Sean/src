#!/usr/bin/env ruby

require 'python' # Ruby/Python
require 'python/snack' # newt

class NewtTest
  def initialize
    @screen = Py::Snack::SnackScreen.new()
    @g = Py::Snack::GridForm.new(@screen, "My Test", 1, 2)
    i = 0
    # --------------------------------------------------------------------
    @lb = Py::Snack::Listbox.new(height = 3, width = 20, returnExit = 1)
    @lb.append("First", 1)
    @lb.append("Second", 2)
    @lb.append("Third", 3)
    @g.add(@lb, 0, i, [0, 0, 0, 1])
    i += 1
    # --------------------------------------------------------------------
    @bb = Py::Snack::ButtonBar.new(@screen,
     [["Ok", "hoge"], ["Cancel", "fuga"]] )
    @g.add(@bb, 0, i, [0, 0, 0, 0])
    i += 1
    @result = ""
  end
  def run 
    @result = @g.runOnce()
    @screen.finish()
  end
  def get_result
    @bb.buttonPressed(@result)
  end
end

newttest = NewtTest.new
newttest.run
print "d: ", newttest.get_result(), "\n"

