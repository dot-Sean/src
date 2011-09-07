#!/usr/bin/python
# coding=UTF-8

# --------------------------------------------------------------------

import HTMLParser

class HtmlEncodingParser(HTMLParser.HTMLParser):
  def feed(self, s):
    try:
      i = s.lower().index('<title>')
    except ValueError:
      pass
    else:
      s = s[:i]
    HTMLParser.HTMLParser.feed(self, s)
  def reset(self):
    HTMLParser.HTMLParser.reset(self)
    self.htmltype = None
    self.encoding = None
  def handle_starttag(self, tag, attributes):
    if not self.encoding and tag == 'meta':
      a = dict(attributes)
      if a.get('http-equiv', '').lower() == "content-type":
        try:
          content = a['content']
        except KeyError:
          return
        for i in content.split(';'):
          try:
            start = i.lower().index('charset=')
          except ValueError:
            continue
          start += len('charset=')
          self.encoding = i[start:].strip()
          break
  def handle_decl(self, decl):
    astr = decl.split()
    if len(astr) > 1 and astr[0] == 'DOCTYPE':
      if astr[1] == 'HTML':
        self.htmltype = 'HTML'
      elif astr[1] == 'html':
        self.htmltype = 'XHTML'
  def handle_pi(self, data):
    if not self.encoding and data.split()[0] == 'xml':
      try:
        start = data.index('encoding="')
      except ValueError:
        return
      start += len('encoding="')
      end = data.index('"', start)
      self.encoding = data[start:end]

# --------------------------------------------------------------------

input_encoding = ""
output_encoding = "UTF-8"
url = "http://weather.yahoo.co.jp/weather/jp/13/4410/13112.html"

import sys
import codecs
import tidy
import urllib

input = urllib.urlopen(url)
s = input.read()
if not input_encoding:
  input_encoding = input.headers.getparam("charset")
if not input_encoding:
  parser = HtmlEncodingParser()
  parser.feed(s)
  parser.close()
  input_encoding = parser.encoding
if not input_encoding:
  input_encoding = "UTF-8"
s = s.decode(input_encoding).encode("UTF-8")
# "*_encoding" are not those for gconv, but defined in libtidy.
# Other than "utf8" cause SEGV frequently ...
tobj = tidy.parseString(s, output_xhtml = 1,
 add_xml_decl = 1, indent = 1, tidy_mark = 0, quote_nbsp = 0,
 input_encoding = "utf8",
 output_encoding = "utf8"  )
#import pdb; pdb.set_trace()
xhtml_utf8 = str(tobj)
if output_encoding:
  sys.stdout = codecs.getwriter(output_encoding)(sys.stdout)
#print xhtml_utf8.decode("UTF-8")
#sys.exit(0)

# --------------------------------------------------------------------

import xml.dom.minidom
dom = xml.dom.minidom.parseString(xhtml_utf8)
for elem in dom.documentElement.getElementsByTagName("title"):
  for node in  elem.childNodes:
    if node.nodeType == node.TEXT_NODE:
      print node.data.strip()

try:
  from lxml import etree
  print("running with lxml.etree")
except ImportError:
  try:
    # Python 2.5
    import xml.etree.cElementTree as etree
    print("running with cElementTree on Python 2.5+")
  except ImportError:
    try:
      # Python 2.5
      import xml.etree.ElementTree as etree
      print("running with ElementTree on Python 2.5+")
    except ImportError:
      try:
        # normal cElementTree install
        import cElementTree as etree
        print("running with cElementTree")
      except ImportError:
        try:
          # normal ElementTree install
          import elementtree.ElementTree as etree
          print("running with ElementTree")
        except ImportError:
          print("Failed to import ElementTree from any known place")

# Only for lxml.etree
# XPath and XSLT with lxml <http://codespeak.net/lxml/xpathxslt.html#xslt>
#transform = etree.XSLT(xslt_doc)
#result_tree = transform(etree.parse("test.xml"))

root_node = etree.fromstring(xhtml_utf8)

if root_node.tag == "{http://www.w3.org/1999/xhtml}html":
  for elem in root_node.findall("./"
   "{http://www.w3.org/1999/xhtml}head/"
   "{http://www.w3.org/1999/xhtml}title"):
    print dir(elem)
    print elem.text.strip()
  #for elem in dom.findall(".//{http://www.w3.org/1999/xhtml}td"):
  #  if elem.text: print elem.text.strip()
  for elem in root_node.findall("./*"):
    print elem
  for elem in root_node.findall(".//{http://www.w3.org/1999/xhtml}table"):
    if elem.attrib.has_key("class") and \
     elem.attrib["class"] == "yjw_table2":
      print elem
  # Requires: ElementTree >= 1.3, F9: 1.2.6
  #for elem in root_node.findall(
  # ".//{http://www.w3.org/1999/xhtml}table[@class='yjw_table2']" ):
  #  print elem

print

#from xml.dom.ext.reader import Sax2
#from xml import xpath
#print dir(Sax2)
#doc = Sax2.FromXmlFile('foo.opml').documentElement
#for url in xpath.Evaluate('//@xmlUrl', doc):
#  print url.value

#import libxml2
#doc = libxml2.parseMemory(xhtml_utf8, len(xhtml_utf8))
#doc.dump(sys.stdout)
#print doc.xpathEval('html/head/title')
#ctx = doc.xpathNewContext()
#ctx.xpathRegisterNs("rss", "http://purl.org/rss/1.0/")
#nodes = ctx.xpathEvalExpression("//html")
#print nodes

#elems = dom.documentElement.getElementsByTagName("table")
#tables = []
#for i in range(elems.length):
#  try:
#    if elems[i].attributes["class"].value == "yjw_table2":
#      tables.append(elems[i])
#  except:
#    pass

# Requires: PyXML
import xml.xpath
doc = dom
# Too slow ...
#from xml.dom.ext.reader import Sax2 
#doc = Sax2.FromXml(xhtml_utf8).documentElement 
tables = xml.xpath.Evaluate(".//table[@class='yjw_table2']", doc)

def traceNodes(nodeArg):
  for node in nodeArg.childNodes:
    #print node.nodeName
    if node.nodeType == node.TEXT_NODE:
      s = node.data.strip()
      #print type(s)
      if s:
        print s
    traceNodes(node)

for table in  tables:
  #traceNodes(table)
  print table

#dom.documentElement.getElementsByClass("yjw_pinpoint_tomorrow")
#import pdb; pdb.set_trace()

# yjw_table2: 今日の天気 & 明日の天気
# yjw_table: 週間の天気 & 世界の天気

# node.ELEMENT_NODE	要素(element)
# node.ATTRIBUTE_NODE	属性(attribute)
# node.TEXT_NODE	テキスト
# node.CDATA_SECTION_NODE	CDATA
# node.ENTITY_NODE	実体
# node.PROCESSING_INSTRUCTION_NODE	処理命令(PI)
# node.COMMENT_NODE	コメント
# node.DOCUMENT_NODE	ドキュメント
# node.DOCUMENT_TYPE_NODE	ドキュメントタイプ
# node.NOTATION_NODE	NOTATION
