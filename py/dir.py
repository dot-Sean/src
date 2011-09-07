#!/usr/bin/python

import dircache
path = "/etc/"
files = dircache.listdir(path)
dircache.annotate(path, files)
files = map(lambda file: path + file, files)
print files

