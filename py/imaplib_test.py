#!/usr/bin/env python

# /usr/lib/python1.5/imaplib.py(1)
# (type, data) = imap4.fetch(6, '(RFC822.HEADER)')

import getpass, imaplib, string

imap4 = imaplib.IMAP4("mail.turbolinux.co.jp")
imap4.login(getpass.getuser(), getpass.getpass())
imap4.select("tlj/saved")
(type, data) = imap4.search(None, '(FROM "kazutomo")')
for msgnum in string.split(data[0]):
  #(type, data) = imap4.fetch(msgnum, '(RFC822)')
  (type, data) = imap4.fetch(msgnum, '(RFC822)')
  print 'Message %s\n%s\n' % (msgnum, data[0][1])
imap4.logout()

#(type, data) = imap4.fetch(6, '(RFC822.HEADER)')
#(type, data) = imap4.fetch(6, '(RFC822.TEXT)')
#print data[0][1]
#imap4.logout()
