#!/usr/bin/python

import os

def comb(n, m, a = [], l = []):
  if m == 0:
    l.append(a)
  elif n == m:
    l.append(range(1, m + 1) + a)
  else:
    l = comb(n - 1, m, a, l)
    l = comb(n - 1, m - 1, [n] + a, l)
  return l

queries = (
  'echo %s > /dev/null; echo "BEGIN;" >&%d; sleep 0.1',
  'echo %s > /dev/null; echo "SELECT * FROM TEST WHERE KEY = 0;" >&%d; sleep 0.1',
  'echo "UPDATE TEST SET VAL = \'%s\' WHERE KEY = 0;" >&%d; sleep 0.1',
  'echo %s > /dev/null; echo "COMMIT;" >&%d; sleep 0.1',
)

for (il, ilname) in (("rc", "READ COMMITTED"), ("sr", "SERIALIZABLE"),):
  for c in comb(8, 4):
    #print c
    ia = 0
    ib = 0
    id = reduce(lambda s, a: "%s%d" % (s, a,), c, "")
    out = open("scenario-%s.sh" % id, "w")
    out.write("echo 'SET SESSION CHARACTERISTICS AS TRANSACTION ISOLATION LEVEL %s;' >&3; sleep 0.1\n" % ilname);
    out.write("echo 'SET SESSION CHARACTERISTICS AS TRANSACTION ISOLATION LEVEL %s;' >&4; sleep 0.1\n" % ilname);
    for i in range(1, 8 + 1):
      if i in c:
        out.write((queries[ia] % (id + "-A", 3,)) + "\n")
        ia = ia + 1
      else:
        out.write((queries[ib] % (id + "-B", 4,)) + "\n")
        ib = ib + 1
    out.close()
    os.system("transactions %s | tee result-%s-%s.log" % (id, il, id,))
    #break
