#!/usr/bin/python

print reduce(lambda l, e: (e in l) and l or (l.append(e), l,)[-1], [4, 2, 3, 1, 3, 1,], [])
