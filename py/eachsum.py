#!/usr/bin/python

# map, recuce
# and, or
# (exp1, exp2, ..., expN)[-1]

a = (
 (1, 2, 3, 4,),
 (5, 6, 7, 8,),
)

print map(lambda l: reduce(lambda a, b: a + b, l), a)
