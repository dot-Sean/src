#!/bin/sh

python <<'EOF'
class Complex:
  def __init__(self, r, i):
    self.r = r
    self.i = i
  def __repr__(self):
    return "(%d%+dj)" % (self.r, self.i,)
  def __add__(self, other):
    return Complex(self.r + other.r, self.i + other.i)
print Complex(-2, 1) + Complex(5, -3)
EOF
