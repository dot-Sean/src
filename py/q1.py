#!/usr/bin/python

#str = "g fmnc wms bgblr rpylqjyrc gr zw fylb. rfyrq ufyr amknsrcpq ypc dmp. bmgle gr gl zw fylb gq glcddgagclr ylb rfyr'q ufw rfgq rcvr gq qm jmle. sqgle qrpgle.kyicrpylq() gq pcamkkclbcb. lmu ynnjw ml rfc spj."
str = "map"

print reduce(lambda a, b: a + b, map(lambda c: (ord("a") <= ord(c) and ord(c) <= ord("z")) and chr(((ord(c) - ord("a") + 2) % 26) + ord("a")) or c, str));

import string;
print str.translate(string.maketrans(string.ascii_lowercase, string.ascii_lowercase[2:] + string.ascii_lowercase[:2]));
