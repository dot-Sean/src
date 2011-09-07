#!/usr/bin/ruby
# -*- coding: utf-8 -*-

val = 100

l0 = lambda { |x, y|
  return [x ** 2, y ** 2, val,]
}

val = 200

p l0

p l0.call(2, 3)

# --------------------------------------------------------------------

p0 = proc { |x, y|
  return [x ** 2, y ** 2, val,]
}

val = 300

p p0

p p0.call(3, 4)

# --------------------------------------------------------------------

val = 350

p1 = Proc.new { |x, y|
  #return [x ** 2, y ** 2, val,] # ブロック内での return で LocalJumpError
  [x ** 2, y ** 2, val,] # 現スコープの参照 "val" に束縛
}

val = 400

p p1

p p1.call(4, 5)

# --------------------------------------------------------------------

def get_the_proc(val)
  return Proc.new { |x, y|
    [x ** 2, y ** 2, val,]
  }
end

p2 = get_the_proc(500) # 呼び出しで作られるスタック上の参照 "val" に束
 # 縛されるのであって、評価された値の "val" に束縛されるのではない
p3 = get_the_proc(600) # 同様。C の "static" でもあれば、変化するだろう

p p2

p p2.call(5, 6)

p p3

p p3.call(6, 7)
