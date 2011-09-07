#!/usr/bin/ruby

def reduce(enum, sum)
  enum.each { |value| sum = yield(sum, value) }
  sum
end

p reduce([4, 2, 3, 1, 3, 1,], []) { |l, e| (l.include?(e))? l: l << e }

# --------------------------------------------------------------------

module Enumerable
  def reduce(sum)
    each { |value| sum = yield(sum, value) }
    sum
  end
end

p [4, 2, 3, 1, 3, 1,].reduce([]) { |l, e| (l.include?(e))? l: l << e }
