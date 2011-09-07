#!/usr/bin/python

import sys
import qt

for i, name in enumerate(("AppendEvent", "FinishEvent",)):
  locals()[name] = qt.QCustomEvent.User + i

class JobThread(qt.QThread):
  def __init__(self, receiver):
    qt.QThread.__init__(self)
    self.receiver = receiver
  def run(self):
    for i in range(10):
      qt.QThread.postEvent(self.receiver,
       qt.QCustomEvent(AppendEvent, "%d(thread)" % (i,)) )
      self.msleep(500) # msecs
    qt.QThread.postEvent(self.receiver,
     qt.QCustomEvent(FinishEvent, "bye(thread)") )

class AsyncExampleWidget(qt.QWidget):
  def __init__(self):
    qt.QWidget.__init__(self)
    self.jobthread = JobThread(self)
    self.button = qt.QPushButton("&Start", self)
    self.connect(self.button, qt.SIGNAL("clicked()"), self.onStartClicked)
    self.edit = qt.QMultiLineEdit(self)
    widgets = (self.button, self.edit,)
    vbox = qt.QVBoxLayout(self, len(widgets))
    for widget in widgets:
      vbox.addWidget(widget)
  def onStartClicked(self):
    if self.jobthread.running():
      qt.QMessageBox.information(self, "Error", "It's still running!")
      return
    self.edit.clear()
    self.timer = qt.QTimer(self, "Interval timer")
    self.connect(self.timer, qt.SIGNAL("timeout()"), self.onTimeout)
    self.timer.start(800, False) # msec, sshot
    self.jobthread.start()
  def customEvent(self, event):
    if event.type() == AppendEvent:
      self.edit.append("d: %s" % (event.data(),))
    elif event.type() == FinishEvent:
      self.edit.append("finish: %s" % (event.data(),))
      self.timer.stop()
    else:
       print "Unknown custom event type:", event.type()
  def onTimeout(self):
    self.edit.append("timer")

import signal
signal.signal(signal.SIGINT, signal.SIG_DFL)
app = qt.QApplication(sys.argv)
widget = AsyncExampleWidget()
app.setMainWidget(widget)
widget.show()
sys.exit(app.exec_loop())
