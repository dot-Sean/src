#!/usr/bin/python
# -*- coding: utf-8 -*-
# あいうえお

import twitter
t = twitter.Twitter()
stats = t.statuses.user_timeline(id = 'nina_ayutaya', include_rts = True)
#stats = t.statuses.public_timeline(id = 'nina_ayutaya')
#ret = t.statuses.user_timeline(id = 'nina_ayutaya')
user = t.users.show(id = 'nina_ayutaya')

