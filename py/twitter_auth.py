#!/usr/bin/python
# -*- coding: utf-8 -*-

orgname = ''
conskey = ''
conssec = ''

from twitter.oauth_dance import oauth_dance
(oauth_token, oauth_token_secret) = oauth_dance(orgname, conskey, conssec)
print "oauth_token:", oauth_token
print "oauth_token_secret:", oauth_token_secret
