#!/usr/bin/python
# -*- coding: utf-8 -*-
# encoding declatation <http://www.python.jp/doc/release/ref/encodings.html>

# --------------------------------------------------------------------
# 入出力

def io():
  import tempfile

  # このテンポラリは、閉じると消えてしまう。テンポラリは mkdtemp() 内が吉
  #output = tempfile.NamedTemporaryFile("w", suffix = ".suffix")
  #filename = output.name

  #filename = tempfile.mktemp(".postfix")
  ## 普通に開く
  #output = open(filename, "w")

  fd, filename = tempfile.mkstemp(".postfix")
  import os
  output = os.fdopen(fd, "w")

  output.write("Hello, World!\n")
  output.write("Foo Bar!\n")
  output.close()
  import sys
  sys.stdout.write("Filename: %s\n" % (filename,))
  # popen する
  import os
  input = os.popen("/bin/cat -n %s" % (filename,), "r")
  # 一行ずつ読み出す、標準的な方法。逐次なら readline()
  for line in input.readlines():
    #line = line.rstrip()
    print line,
  input.close()

io()

# --------------------------------------------------------------------
# 制御構造

def control_structure():
  if True:
    pass
  elif False:
    pass
  else:
    pass
  while True:
    print "Looping"
    break
  for i in range(3):
    print i
  # ----
  # No DO WHILE
  i = 0
  n = 5
  while True:
    pass
    if i > n:
      break
    i += 1;
  # ----
  # No post-positioned IF
  # 前置でいいよ
  if True: print "Hoge"
  # ----
  # No SWITCH
  # switch は、コーディング時に条件と挙動が固定化されてしまうので、動的
  # なプログラミングにならず、仕様変更に弱いのだ
  def print_abc():
    print "ABC"
  key = "abc"
  tbl = {"abc": print_abc}
  tbl.get(key)()
  def print_xyz():
    print "XYZ"
  import sys
  tbl["xyz"] = lambda: sys.stdout.write("XYZ\n")
  tbl.get("xyz")()
  # ----
  # 3 項演算子もないが…
  print ("FALSE", "TRUE",)[True]
  # ----
  # 例外処理 (Exception)
  try:
    a = not_exist[0]
  except NameError, e:
    # 例外時
    print "***", e
  except:
    pass
  else:
    pass
  finally:
    # 後処理
    pass

control_structure()

# --------------------------------------------------------------------
# データ操作

def data_manipulation():
  # 文字列操作
  s = "01234" + "56789"
  print s[2:8], len(s)
  # リストの操作
  a = [0, 1, 2, 3, 4, 5,]
  a.append(6)
  a.pop()
  a.append(7)
  a.append(8)
  a.append(9)
  print a[2:8], len(a)
  # todo: 内包表現も
  # 連想配列
  d = {0: "d0", 1: "d1", 2: "d2",}
  d[9] = "d9"
  # .keys() は、無くとも良い
  if 2 in d.keys():
    print d.get(8, "not_found"), len(d)
  # 関数型の扱い
  def func():
    print "dynamic funciton call"
  # Python では、変数と関数は名前空間を共有する
  p = func
  p()

data_manipulation()

# --------------------------------------------------------------------
# 正規表現

def re_operation():
  # http://www.python.jp/doc/nightly/lib/module-re.html
  import re
  # \w = [a-zA-Z0-9_]
  # (?:～) は、参照できないグループ
  # (?P<key>val) は、名前による参照グループ
  re_test = re.compile("\((?:b\w)(?P<foo>dy)\)\s")
  m = re_test.search("head-(body) tail")
  if m:
    print m.group(0)
    print m.groups()
    print m.groupdict()

re_operation()

# --------------------------------------------------------------------
# オブジェクト指向プログラミング

class Hoge(object):
  def __init__(self):
    print "Hoge init"
  def foo(self):
    print "foo"

class Fuga(Hoge):
  def __init__(self):
    print "Fuga init"
    super(type(self), self).__init__()
  def foo(self):
    print "bar"
    super(Fuga, self).foo()

def oop():
  fuga = Fuga()
  fuga.foo()

oop()

# --------------------------------------------------------------------


#  モジュール化, require とか
#  class
#  継承
#  private/public

# --------------------------------------------------------------------
# 関数とスコープ

global_value0 = "global value0 unchanged"
global_value1 = "global value1 unchanged"

# def scope0():
#   print "local0:", global_value0 # 参照は OK だが、これはグローバルなのに、
#   global_value0 = "global value0 changed" # これがローカルなのでエラー。

def scope0():
  global_value0 = "global value0 changed" # これはローカルで、
  print "func:", global_value0 # これもローカルだから OK。

def scope1():
  global global_value1
  global_value1 = "global value1 changed"
  print "func:", global_value1

print "pre:", global_value0
scope0()
print "after:", global_value0

print "pre:", global_value1
scope1()
print "after:", global_value1

# --------------------------------------------------------------------

def python_specific():
  pass


python_specific()
