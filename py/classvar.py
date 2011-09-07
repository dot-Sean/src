#!/usr/bin/python

class Hoge:
  fuga = 0

hoge0 = Hoge()
print hoge0.fuga

Hoge.fuga = 1

print hoge0.fuga
hoge1 = Hoge()
print hoge1.fuga
