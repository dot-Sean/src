#!/usr/bin/python
# -*- coding: utf-8 -*-

import sqlite3

dbcon = sqlite3.connect("/tmp/testdb", timeout = 1000)

print "done"

try:
  dbcon.executescript("""
    create table testtbl(
     idx integer primary key,
     kai real,
     uri real,
     val text );
  """ )
except sqlite3.OperationalError:
  pass

def dump(dbcon):
  cur = dbcon.cursor()
  cur.execute("select idx, uri, val from testtbl order by idx")
  for row in cur:
    print row[0], row[1], row[2]
  cur.close()

cur = dbcon.cursor()
try:
  for i in range(50):
    try:
      cur.execute("insert into testtbl values (?, ?, ?, ?)",
       (i, float(i), float(i), u"ほげ") )
      #import time
      #time.sleep(10000000)
    except sqlite3.IntegrityError:
      pass
  dbcon.commit()
except:
  dbcon.rollback()
finally:
  cur.close()
dump(dbcon)
dbcon.close()
