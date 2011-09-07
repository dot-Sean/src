#!/usr/bin/env python
# -*- coding: utf-8 -*-

main_id = 'knaka'
langs = ('en', 'zh',)
sers = {
  'knaka': 6467272,
  'knaka_en': 305406973,
  'knaka_zh': 309400173,
}

import feedparser
import sys
import codecs
import hashlib

sys.stdout = codecs.getwriter('UTF-8')(sys.stdout)

ids = sers.keys()
sub_ids = ['%s_%s' % ('knaka', lang,) for lang in langs]

def is_en_str(u):
  ret = True
  try:
    u.encode("ASCII")
  except UnicodeEncodeError, e:
    ret = False
  return ret

kanachrs = u'ーぁあぃいぅうぇえぉおかがきぎくぐけげこごさざしじすずせぜそぞただちぢっつづてでとどなにぬねのはばぱひびぴふぶぷへべぺほぼぽまみむめもゃやゅゆょよらりるれろゎわゐゑをんァアィイゥウェエォオカガキギクグケゲコゴサザシジスズセゼソゾタダチヂッツヅテデトドナニヌネノハバパヒビピフブプヘベペホボポマミムメモャヤュユョヨラリルレロヮワヰヱヲンヴヵヶ'

def is_zh_str(u):
  ret = True
  try:
    u.encode("GB18030")
    for chr in u:
      if chr in kanachrs:
        ret = False
        break
  except UnicodeEncodeError, e:
    ret = False
  return ret
    
if __name__ == '__main__':
  tweetsdat = {}
  hashes = {}
  for id, ser in sers.items():
    tweetsdat[id] = []
    hashes[id] = []
    url = 'http://twitter.com/statuses/user_timeline/%d.rss' % (ser,)
    data = feedparser.parse(url)
    for entry in data.entries:
      tweet = entry.summary.replace('%s: ' % (id,), '', 1)
      can_be_rt = (tweet.find("RT ") == 0)
      tweetsdat[id].append((tweet, entry, can_be_rt))
      hash = hashlib.md5(tweet.encode("UTF-8"))
      hashes[id].append(hash.digest())
    tweetsdat[id].reverse()
  print main_id
  for tweet, entry, can_be_rt in tweetsdat[main_id]:
    print "  " + tweet
    if can_be_rt:
      print "  RT?"
    hash = hashlib.md5(tweet.encode("UTF-8"))
    #for sub_id in sub_ids:
    for lang in langs:
      sub_id = '%s_%s' % (main_id, lang,)
      if not hash in hashes[sub_id]:
        #langchecker = getattr(, 'is_%s_str' % (lang,))
        langchecker = globals()['is_%s_str' % (lang,)]
        if langchecker(tweet):
          print "  Not in %s" % (sub_id,)
