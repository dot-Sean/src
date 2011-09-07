#!/usr/bin/python

import os

def comb(n, m, a = [], l = []):
  if m == 0:
    l.append(a)
  elif n == m:
    l.append(list(range(1, m + 1)) + a)
  else:
    l = comb(n - 1, m, a, l)
    l = comb(n - 1, m - 1, [n] + a, l)
  return l

print(comb(8, 3))
