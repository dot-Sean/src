#!/usr/bin/python

# List Comprehension（リストの内包表現）

l = range(1, 6)

print zip(l, map(lambda x: x * x, l))
print [ (x, x * x) for x in l ]

print map(None, filter(lambda x: 4 >= x >= 2, l), map(lambda x: x * x, filter(lambda x: 4 >= x >= 2, l)))
print [ (x, x * x) for x in l if 4 >= x >= 2 ]

a = [ 1, 2, 3 ]
b = [ 10, 100, 1000 ]

print [ x * y for x in a for y in b ]
print [ a[i] * b[i] for i in range(len(a)) ]
