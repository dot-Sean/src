#!/usr/bin/python

from string import split, atoi
def is_valid_addr(addr):
  list = split(addr, ".")
  return (len(list) == 4) and \
   reduce(lambda r, a: r and (0 <= atoi(a) <= 255), [1] + list)

print is_valid_addr("255.-1.0.0")
