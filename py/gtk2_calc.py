#!/usr/bin/python

import gtk

Digits = 10
Margin = 4

def add(lhs, rhs):
  return lhs + rhs

def sub(lhs, rhs):
  return lhs - rhs

def mul(lhs, rhs):
  return lhs * rhs

def div(lhs, rhs):
  return lhs / rhs

class CalcWidget(gtk.Table):
  def set_op(self, op):
    self.op = op
    print "op:", op
  def set_buf(self, buf):
    self.buf = buf
    print "buf:", buf
  def all_clear(self):
    self.set_buf(None)
    self.set_op(add)
    self.label.set_text("0")
  def clear(self):
    text = "0"
    if self.buf != None:
      text = self.buf
    self.set_buf(None)
    self.label.set_text(text)
  def on_c_clicked(self, widget, * args):
    self.clear()
  def on_digit_clicked(self, widget, char):
    text = self.label.get_text()
    if self.buf == None:
      self.set_buf(text)
      text = "0"
    if len(text) == Digits:
      return
    if text == "0":
      text = ""
    text = text + char
    self.label.set_text(text)
  def on_ac_clicked(self, widget, * args):
    self.all_clear()
  def on_dot_clicked(self, widget, char):
    text = self.label.get_text()
    if not char in text:
      text = text + char
    self.label.set_text(text)
  def on_op_clicked(self, widget, char):
    text = self.label.get_text()
    if self.op and self.buf != None:
      text = "%g" % (self.op(float(self.buf), float(text)))
    self.label.set_text(text)
    self.set_buf(None)
    if char == "=":
      return
    for (op_char, op,) in (
      ("+", add,),
      ("-", sub,),
      ("*", mul,),
      ("/", div,),
    ):
      if char == op_char:
        self.set_op(op)
  def __init__(self):
    gtk.Table.__init__(self,  5, 5, homogeneous = 1)
    self.label = gtk.Entry(Digits)
    self.attach(self.label, 0, 5, 0, 1)
    self.set_border_width(Margin)
    self.set_row_spacings(Margin)
    self.set_col_spacings(Margin)
    for (left, right, top, bottom, char, callback,) in (
     (0, 1, 1, 2, "7",  self.on_digit_clicked,),
     (1, 2, 1, 2, "8",  self.on_digit_clicked,),
     (2, 3, 1, 2, "9",  self.on_digit_clicked,),
     (3, 4, 1, 2, "*",  self.on_op_clicked,),
     (4, 5, 1, 2, "AC", self.on_ac_clicked,),
     (0, 1, 2, 3, "4",  self.on_digit_clicked,),
     (1, 2, 2, 3, "5",  self.on_digit_clicked,),
     (2, 3, 2, 3, "6",  self.on_digit_clicked,),
     (3, 4, 2, 3, "-",  self.on_op_clicked,),
     (4, 5, 2, 3, "C",  self.on_c_clicked,),
     (0, 1, 3, 4, "1",  self.on_digit_clicked,),
     (1, 2, 3, 4, "2",  self.on_digit_clicked,),
     (2, 3, 3, 4, "3",  self.on_digit_clicked,),
     (3, 4, 3, 5, "+",  self.on_op_clicked,),
     (4, 5, 3, 4, "/",  self.on_op_clicked,),
     (0, 1, 4, 5, "0",  self.on_digit_clicked,),
     (1, 2, 4, 5, ".",  self.on_dot_clicked,),
     (2, 3, 4, 5, "=",  self.on_op_clicked,),
     (4, 5, 4, 5, "%",  None,),
    ):
      btn = gtk.Button(char)
      if callback:
        btn.connect("clicked", callback, char)
      else:
        btn.set_sensitive(gtk.FALSE)
      self.attach(btn, left, right, top, bottom)
    self.all_clear()

class MainWindow(gtk.Window):
  def on_delete(self, * args):
    gtk.mainquit()
  def __init__(self):
    gtk.Window.__init__(self)
    calc = CalcWidget()
    self.connect("delete_event", self.on_delete);
    self.add(calc)

import signal
signal.signal(signal.SIGINT, signal.SIG_DFL)
MainWindow().show_all()
gtk.main()
