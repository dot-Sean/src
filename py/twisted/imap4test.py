#!/usr/bin/env python 
# +-+ coding: utf-8 +-+
"""
This simple imap client is used to notice the user if he has new messages.
  
Copyright (C) 2008 Joerg Sawatzki <joerg.sawatzki@web.de>
  
This file is part of IStick.
  
IStick is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.
  
IStick is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
  
You should have received a copy of the GNU General Public License along with this program; if not, see <http://www.gnu.org/licenses/>.
"""
  
from twisted.internet import defer
from twisted.internet import protocol
from twisted.mail import imap4
from twisted.internet import ssl 
from twisted.python import log
from twisted.internet import reactor
  
class ImapClient(imap4.IMAP4Client):
   greetdefer = None
  
   def serverGreeting(self, caps):
      self.caps = caps
      if self.greetdefer is not None:
         d, self.greetdefer = self.greetdefer, None
         d.callback(self)
  
  
  
class ImapClientFactory(protocol.ClientFactory):
   protocol = ImapClient
  
   def __init__(self, uid, defer):
      self.uid = uid
      self.onconn = defer
      #self.context = ssl.ClientContextFactory
      self.context = None
  
   def buildProtocol(self, addr):
      p = self.protocol(self.context)
      p.factory = self
      p.greetdefer = self.onconn
  
      auth1 = imap4.CramMD5ClientAuthenticator(self.uid)
      auth2 = imap4.PLAINAuthenticator(self.uid)
      auth3 = imap4.LOGINAuthenticator(self.uid)
      p.registerAuthenticator(auth1)
      p.registerAuthenticator(auth3)
      p.registerAuthenticator(auth2)
      p.registerAuthenticator(auth1)
  
      return p
  
  
def cbGreeting(proto, uid, pwd):
   log.msg("Got imap greeting")
   log.msg("Logging in as uid "+ uid)
   return proto.login(uid, pwd).addCallback(cbAuth, proto).addErrback(cbAuthFailed)
   #return proto.authenticate(pwd).addCallback(cbAuth, proto).addErrback(cbAuthFailed)
  
def cbAuth(result, proto):
   log.msg("Auth succeeded")
  
   return proto.examine("INBOX").addCallback(cbInbox, proto)
def cbAuthFailed(proto):
   log.err("Auth failed")
def cbInbox(content, proto):
   log.msg("Selected INBOX")
   return proto.search("NEW").addCallback(cbNewCount)
def cbNewCount(content):
   """ Gets a list with all message ids of new messages """
   cnt = len(content)
   log.msg("Mailbox contains %d new messages." % cnt)
   return cnt
  
def checkmbox(server, uid, pwd):
   log.msg("Checking mails on "+server)
   deferred = defer.Deferred().addCallback(cbGreeting, uid, pwd)
   factory = ImapClientFactory(uid, deferred)
   #reactor.connectTCP(server, 143, factory)
   reactor.connectTCP(server, 993, factory)
   return deferred
  
def blub(cnt):
   print cnt
  
if __name__ == "__main__":
   print "simple imap client"
   server = raw_input("Server name: ")
   uid = raw_input("Username: ")
   from twisted.python import util
   pwd = util.getPassword("Password: ")
  
   from twisted.internet import reactor
   checkmbox(server, uid, pwd).addCallback(blub)
   reactor.run()
