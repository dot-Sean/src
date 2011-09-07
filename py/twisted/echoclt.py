#!/bin/env python
# -*- coding: utf-8 -*-

from twisted.internet.protocol import Protocol

class EchoCltProtocol(Protocol):
  def dataReceived(self, data):
    print data
  def sendMessage(self, data):
    self.transport.write(data + "\r\n")
  def connectionLost(self, reason):
    print "X 接続終了: ", reason
    reactor.stop()
  def connectionFailed(self, reason):
    print "X 接続失敗: ", reason

from twisted.internet.protocol import ClientFactory
from twisted.internet import defer
from twisted.internet import reactor

class EchoCltManager(ClientFactory):
  protocol = EchoCltProtocol
  #def __init__(self, deferred):
  #  self.deferred = deferred
  def startedConnecting(self, connector):
    print "接続開始"
  def buildProtocol(self, addr):
    print "接続完了"
    clt = self.protocol()
    clt.factory = self
    #reactor.callLater(0, self.deferred.callback, clt)
    reactor.callLater(0, gotProtocol, clt)
    return clt
  # CB "client～()" は、Protocol.～() から呼ばれる
  #def clientConnectionLost(self, connector, reason):
  #  print "接続終了: ", reason
  #def clientConnectionFailed(self, connector, reason):
  #  reactor.callLater(0, self.deferred.errback, reason)
  #  print "接続失敗: ", reason

def gotProtocol(clt):
  clt.sendMessage("Hello, world")
  reactor.callLater(1, clt.sendMessage, "Hello, world, again")
  reactor.callLater(2, clt.transport.loseConnection)

#deferred = defer.Deferred()
#reactor.connectTCP("localhost", 1234, EchoCltManager(deferred))
reactor.connectTCP("localhost", 1234, EchoCltManager())
#deferred.addCallback(gotProtocol)

reactor.run()
