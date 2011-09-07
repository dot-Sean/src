#!/usr/bin/python

import getopt
import sys
(opts, args) = getopt.getopt(sys.argv[1:], "a:b:c", ["alpha=", "beta=", "gamma"])
print "opts:", `opts`
print "args:", `args`
print "d: ", len(sys.argv)
