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
  # fill �ϡ��֥��������åȤ����礭���ʤ롣�����ΰ�򡢥��������åȤǤ����
  # ipadx �ϡ��֥��������åȤ���¦�ˡץ��ڡ���������
  # expand �ϡ��֥��������åȤ�ͽ���ΰ褬���礭���ʤ롣�����ΰ�򡢾岼 and/or ����������;��Ǥ����
  # padx �ϡ��֥��������åȤγ�¦�ˡץ��ڡ���������
  btnPrint.pack(side = "top",   fill = "both")
  btnExit.pack( side = "left", expand = 1, ipady = "10m")
  btnHoge.pack( side = "top", pady = "3m")
  # expand �Τ����ǡ����ˤĤ��ʤ�  
  btnFuga.pack( side = "bottom", expand = 1)
  frmMain.mainloop()

if __name__ == '__main__':
  test()
