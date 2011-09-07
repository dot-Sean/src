#!/usr/bin/ruby
# -*- coding: utf-8 -*-

BEGIN {
  print "はじまるよ\n"
}

END {
  print "おわるよ\n"
}

# --------------------------------------------------------------------
# 入出力。Ruby のブロックは、リソースのスコープが一目瞭然ですばらしいな

def io()
  filename = "/tmp/ruby-test"
  open(filename, "w") { |output|
    output.write("Hello, World!\n")
    output.write("Foo Bar\n")
  }
  IO.popen("/bin/cat -n #{filename}") { |input|
    #while (line = input.gets)
    #  print line
    #end
    input.readlines.each { |line|
      print line
    }
  }
end

# --------------------------------------------------------------------
# 制御構造は式になる。primitive 以外は method + block を使った方が綺麗

def control_structure
  if true then
    ;
  elsif false then
    ;
  else
    ;
  end
  loop { # これは新スコープ。loop は、ブロック付きで呼び出されるメソッド
    print "Looping in a block.\n"
    break
  }
  while true do # while true do はスコープを作らない。いわゆる制御構造
    print "Looping with control structure.\n"
    break
  end
  (1 .. 3).each { |i|
    print i.to_s + "\n"
  }
  for i in ["A", "B", "C",] do
    print i << "\n"
  end
  # 後置できます
  print "postpisition\n" if true
  i = 0
  for i in (0 .. 9) do
    # switch できます。
    case i + 1
    when 0 .. 2 then
      i += 1
      p "foo"
      redo # 条件チェックなしでもう一度
    when 3 .. 4, 5 .. 6 then
      p "bar"
      next
    else
      ;
    end
    p i
  end
  # Ruby の「イテレータ」とは、ぶっちゃけ yield を使うメソッドのこと
  def my_while(cond, s)
    return if ! cond
    yield s # クロージャ呼び出し
    retry # イテレータ引数を再評価し、イテレータを再実行
  end
  i = 0
  # なるほど、たしかにRubyのブロックはクロージャだ。イテレータ
  # my_while() はメソッドだから呼び出し元のスタックにはアクセスできない
  # けれど、そこからyieldで呼ばれるブロックはクロージャだからアクセスし
  # 放題なわけだ。
  my_while(i < 10, "hoge") { |s|
    i = i + 1
    if i == 5 then
      next # yield 脱出
    end
    # Python 式の format も使えるのか
    print "%s: %d\n" % [s, i,]
  }
  # 3 項演算はこんな感じ。制御構造も式
  print "result0: " << ((true)? "TRUE": "FALSE") << "\n"
  print "result1: " << (if true then "TRUE" else "FALSE" end) << "\n"
  # 例外処理
  begin
    raise "hoge"
  rescue Exception then
    p "cp0"
  rescue
    p "cp1"
  else
    p "cp2"
  ensure # いわゆる finally か
    p "cp3"
  end
end

control_structure

#if true then; a = 123; end; print a # OK 
#loop { b = 123; break; }; print b # NG

# --------------------------------------------------------------------
# データ操作
def data_manipulation
  # 文字列操作
  # http://www.ruby-lang.org/ja/man/html/String.html
  s = "01234" + "56789"
  print "#{s[2 .. 8]}, #{s.length}\n"
  print "#{s[2 .. -2]}, #{s.length}\n"
  print "#{s[2, 7]}, #{s.length}\n"
  print "d: #{s}\n"
  print "d: #{s[/0+([1-2]+)3+([4-5]+)6+([7-8]*)9/, 2]}\n"
  # リスト操作
  # http://www.ruby-lang.org/ja/man/html/Array.html
  a = [0, 1, 2, 3, 4, 5,]
  a << 6 # a.push(6) でも同じ
  a.pop()
  a += [7, 8, 9,]
  p a[2 .. 8], a.size # length でも可
  # 連想配列のような、ペアの検索もできる
  d = [[2, 234,], [3, 345,], [4, 456,],]
  p d.assoc(3)
  # 連想配列 (ハッシュ)
  #d = Hash[
  # *[
  #  2, 2 ** 2,
  #  3, 3 ** 2,
  # ]
  #]
  d = {
   2 => 2 ** 2,
   3 => 3 ** 2,
   :id0 => "hoge",
   :id1 => "fuga",
   "id0" => "HOGE",
   "id1" => "FUGA",
  }
  d[9] = "d9"
  # each_key や each_value では、それぞれ
  d.each { |key, val|
    print "d: #{key.inspect} #{val}\n"
  }
  if d.has_key?(2) then
    print "#{d.fetch(2, "not_found")}\n"
  end
  # 関数ポインタの扱い
  def foo(s)
    print "Called #{s}\n"
  end
  m = :main.method("foo") # :foo でも可だが、
   # 多分中では結局文字列比較してるだろう
  m.call("Hello")
end

data_manipulation

# --------------------------------------------------------------------
# 正規表現

def re_operation()
  # Regexp 型リテラル
  re_test = /\((?:b\w)(dy)\)\s/
  print "re_operation: "
  p re_test
  re_test =~ "head-(body) tail"
  p $~
  if (m = re_test.match("head-(body) tail")) then
    p m.to_a
  end
end

re_operation

# --------------------------------------------------------------------
# オブジェクト指向プログラミング



# --------------------------------------------------------------------
# ?

# --------------------------------------------------------------------
# 関数とスコープ

# ローカル変数
# インスタンス変数
# クラス変数
# グローバル変数
# 疑似変数
# 定数

ConstantValue = 123 # 大文字で始まる

# Python で言うところの dir()
s = "string"
print "%s\n" % [s.methods.sort.join(" "),]
