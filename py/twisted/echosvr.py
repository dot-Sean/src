#!/bin/env python
# -*- coding: utf-8 -*-

from twisted.protocols.basic import LineReceiver

class EchoSvcProtocol(LineReceiver):
  def connectionMade(self):
    self.factory.numProtocols = self.factory.numProtocols + 1
    if self.factory.numProtocols < 100:
      print "Connected"
    else:
      self.transport.write("Too many connections, try later") 
      self.transport.loseConnection()
  def connectionLost(self, reason):
    self.factory.numProtocols = self.factory.numProtocols - 1
    print "Disconnected"
  def lineReceived(self, line):
    print "Got line: " + line
    self.transport.write("d: " + line + "\r\n")

from twisted.internet.protocol import Factory
from twisted.internet import reactor

class EchoSvcManager(Factory):
  # インスタンス化する Protocol クラスを指定
  protocol = EchoSvcProtocol
  # Echoオブジェクトが参照するフィールドの初期化
  numProtocols = 0

# ポート番号1234でリッスンして，接続が確立したときに使用する
# Factoryオブジェクトを設定
reactor.listenTCP(1234, EchoSvcManager())
# Twistedのイベントループの実行
reactor.run()
