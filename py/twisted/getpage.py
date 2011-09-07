#!/bin/env python
# -*- coding: utf-8 -*-

from twisted.web.client import getPage
from twisted.internet import reactor

def printContent(content):
  print content
  # Twistedのイベントループの終了

def handleError(error):
  print "Error: " + str(error)
  # Twistedのイベントループの終了

import sys

deferred = getPage("http://127.0.0.1/home/")
deferred. \
 addCallback(printContent). \
 addErrback(handleError). \
 addBoth((lambda _: reactor.stop()))

reactor.run()
