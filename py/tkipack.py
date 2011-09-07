#!/usr/bin/env python

from Tkinter import *

def cb():
  print "hoge"

def exit():
  import sys
  sys.exit(0)  

def hoge():
  import sys
  sys.exit(1)

def fuga():
  import sys
  sys.exit(2)

def test():
  frmMain = Frame()
  Pack.config(frmMain)
  btnPrint = Button(frmMain, text = 'Print Hoge is Very Long', command = cb)
  btnExit = Button(frmMain, text = "Exit", command = exit)
  btnHoge = Button(frmMain, text = "Hoge", command = hoge)
  btnFuga = Button(frmMain, text = "F", command = fuga)
  # ------------------------------------------------------------------
  # fill は、「ウィジェットが」大きくなる。空き領域を、ウィジェットでうめる
  # ipadx は、「ウィジェットの内側に」スペースが入る
  # expand は、「ウィジェットの予約領域が」大きくなる。空き領域を、上下 and/or 左右均等な余白でうめる
  # padx は、「ウィジェットの外側に」スペースが入る
  btnPrint.pack(side = "top",   fill = "both")
  btnExit.pack( side = "left", expand = 1, ipady = "10m")
  btnHoge.pack( side = "top", pady = "3m")
  # expand のせいで、下につかない  
  btnFuga.pack( side = "bottom", expand = 1)
  frmMain.mainloop()

if __name__ == '__main__':
  test()
