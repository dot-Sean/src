#!/usr/bin/env python

import xmllib

ikey = 0
iattrs = 1
idata = 2

class XMLParser(xmllib.XMLParser):
  def __init__(self):
    import re
    self.root_node = ["", {}]
    self.current_node = self.root_node
    self.node_stack = []
    self.blank_line = re.compile("^[ \t\n]*$")
    xmllib.XMLParser.__init__(self)
  def unknown_starttag(self, tag, attrs):
    self.current_node.append([tag, attrs])
    self.node_stack.append(self.current_node)
    self.current_node = self.current_node[-1]
  def unknown_endtag(self, tag):
    self.current_node = self.node_stack.pop()
  def handle_data(self, data):
    if self.blank_line.match(data):
      return
    try:
      self.current_node[idata]
    except IndexError:
      self.current_node.append("")
    self.current_node[idata] += data
    
def xml2tree(file = None):
  import types
  if   not file:
    import sys
    input = sys.stdin
  elif isinstance(file, types.FileType):
    input = file
  elif isinstance(file, types.StringType):
    input = open(file, "r")
  else:
    raise "?"
  parser = XMLParser()
  for line in input.readlines():
    parser.feed(line)
  return parser.root_node

if __name__ == '__main__':
  import os
  import sys
  if len(sys.argv) > 1:
    if os.access(sys.argv[1], os.R_OK):
      tree = xml2tree(sys.argv[1])
    else:
      raise Exception, "hoge"
  else:
    tree = xml2tree()
  print `tree`
