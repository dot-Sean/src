#!/usr/bin/python
# -*- coding: utf-8 -*-

# https://developers.facebook.com/docs/reference/api/
# http://developers.facebook.com/docs/authentication/
# http://developers.facebook.com/docs/reference/api/permissions/

import urllib
import json

id = 100000515853032
access_token = 'XXXXXXXXXXXXXXX|XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|XXXXXXXXXXXXXXXXXXXXXXXXXXX'
url = 'https://graph.facebook.com/%d/feed' % (id,)
text = u'API 経由の日本語でのポスト。'
values = {
  'access_token': access_token,
  'message': text.encode('UTF-8'),
}
data = urllib.urlencode(values)
print data
input = urllib.urlopen(url, data)
lines = input.readlines()
d = json.loads(''.join(lines))

print d
