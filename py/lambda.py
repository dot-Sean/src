
def func(f, s):
  f(s)

import sys

func(lambda s: sys.stdout.write("d: %s" % (s)), "hoge")

