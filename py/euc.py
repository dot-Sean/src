#!/usr/bin/python
# -*- coding: japanese.euc_jp -*-

ustr = unicode("������Ϻ", "japanese.euc-jp")
jstr = ustr.encode("japanese.jis-7")

print "d:", jstr
