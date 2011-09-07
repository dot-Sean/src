#!/usr/bin/python
# -*- coding: utf-8 -*-

def count_from(n):
  while True:
    yield n
    n += 1

# generator object. next() を持つ
print count_from(0)

for i in count_from(256):
  print i
  if i > 300:
    break

# closure: 引数以外の変数を、実行時ではなく、関数定義時の静的スコープにおいて解決する関数
# generator: 繰り返しの振る舞いを定義するための関数。関数自体は "generator object" 型のイテレータオブジェクトを返し、イテレータオブジェクトは next() で次の値を返す
# Python のジェネレータの返すイテレータオブジェクトは、一種のクロージャオブジェクトだよな

# generator の返す generator object は、generator が呼ばれた際のスタックと、インデックスとを記憶している
# 略して、generator は、初回呼び出し時の自らのスタックと、インデックスとを記憶している、と言っても良い
# closure は、動的に定義された際の静的スコープのスタックを記憶している

# closure factory は、呼び出し時の自らのスタックを記憶したクロージャを返す。呼び出されるのはクロージャ部分。
# generator は、呼び出し時の自らのスタックを記憶した generator object を返す。呼び出されるのは generator 自体。