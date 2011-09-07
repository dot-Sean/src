#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys
import codecs
sys.stdout = codecs.getwriter('UTF-8')(sys.stdout)

import urllib2
import lxml.etree

opener = urllib2.build_opener()

url = "http://www.ayutaya.com/home/knaka/rsp_index.rdf.php"
input = opener.open(url)
dom = lxml.etree.parse(input)
#ns = {
# "rdf": "http://www.w3.org/1999/02/22-rdf-syntax-ns#",
# "rss": "http://purl.org/rss/1.0/",
# "content": "http://purl.org/rss/1.0/modules/content/",
#}
ns = dom.getroot().nsmap; ns["rss"] = ns[None]; del ns[None]
items = dom.xpath("/rdf:RDF/rss:item", namespaces = ns)
for item in items: # {
  for attr in item:
    if attr.tag == ("{%(rss)s}title" % ns):
      print "d1:", attr.text
  print "d2:", item.xpath("content:encoded", namespaces = ns)[0].text
# }
