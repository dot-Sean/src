#!/usr/bin/python

import sys
import optparse

parser = optparse.OptionParser(
 version = "1.0beta",
 usage = "Usage: %prog [OPTIONS] ARG [ ARGS ... ]" )

def hello(opt_template, opt_arg, value, parser):
  print "hello:", opt_template, opt_arg, value, parser
  print "d:", parser.values
  raise optparse.OptionValueError, "Raised explicitly"

parser.add_option("-a", "--append",
 dest = "list", type = "string", default = [], action = "append",
 help = "append ELEM to list", metavar = "ELEM" )
parser.add_option("-c", "--call",
 callback = hello, type = "string", default = "", action = "callback",
 help = "call function with N", metavar = "N" )
parser.add_option("-f", "--file",
 dest = "filename", type = "string", default = "", action = "store",
 help = "write report to FILE", metavar = "FILE" )
parser.add_option("-n", "--number",
 dest = "number", type = "int", default = -1, action = "store",
 help = "put N characters", metavar = "N" )
parser.add_option("-q", "--quiet",
 dest = "verbose", default = True, action = "store_false",
 help = "don't print status messages to stdout" )
parser.add_option("-v", "--verbose",
 dest = "vlevel", default = 0, action = "count",
 help = "verbose mode" )

(options, args) = parser.parse_args(sys.argv[1:])

print "d0:", options, args

