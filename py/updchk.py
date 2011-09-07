#!/usr/bin/python

import httplib
import sys

if __name__ == "__main__":
  http = httplib.HTTP(sys.argv[1])
  http.putrequest("HEAD", sys.argv[2])
  http.putheader("User-Agent", "test_program")
  http.putheader("Accept", "text/html")
  http.putheader("Accept", "text/plain")
  #http.putheader("If-Modified-Since", "Mon, 02 Apr 2001 03:55:04 GMT")
  #http.putheader("Last-Modified", "Sun, 25 Mar 2001 19:43:31 GMT")
  http.endheaders()
  (errcode, errmsg, headers) = http.getreply()
  print "d:", errcode
  if errcode == 200:
    print headers

