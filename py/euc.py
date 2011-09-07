#!/usr/bin/python
# -*- coding: japanese.euc_jp -*-

ustr = unicode("Æá²ì¼ù°ìÏº", "japanese.euc-jp")
jstr = ustr.encode("japanese.jis-7")

print "d:", jstr
