#!/usr/bin/python
# -*- coding: utf-8 -*-

# ループと、擬似 3 項演算子で
for i in range(1, 10):
  for j in range(1, 10):
    print "%2d%s" % (i * j, ("", "\n")[j == 9]),

print

# リストの内包表現 (list comprehension) で
for l in [[i * j for i in range(1, 10)] for j in range(1, 10)]:
  print(" ".join(["%2d" % (x,) for x in l]))

print

# 一行で書けないこともない
print("\n".join([" ".join("%2d" % (x,) for x in l) for l in [[i * j for i in range(1, 10)] for j in range(1, 10)]]))
