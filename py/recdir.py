#!/usr/bin/python

import os

def listdir_recursive(dir):
  ret = []
  try:
    for file in \
     map(lambda file: os.path.join(dir, file), os.listdir(dir)):
      if os.path.isdir(file):
        ret.append(file + "/")
        ret = ret + listdir_recursive(file)
      else:
        ret.append(file)
  except OSError:
    pass
  return ret 

def listdir_recursive2(dir):
  try:
    return reduce(
     lambda list, file:
      os.path.isdir(file)
       and ((list.append(file + "/"), list,)[-1] + listdir_recursive2(file))
       or (list.append(file), list,)[-1],
     [[]] + map(lambda file: os.path.join(dir, file), os.listdir(dir))
    )
  except OSError:
    return []

def listdir_recursive3(dir):
  try:
    return reduce(lambda list, file: os.path.isdir(file) and ((list.append(file + "/"), list,)[-1] + listdir_recursive3(file)) or (list.append(file), list,)[-1], [[]] + map(lambda file: os.path.join(dir, file), os.listdir(dir)))
  except OSError:
    return []

if __name__ == "__main__":
  import sys
  if len(sys.argv) >= 2:
    dir = sys.argv[1]
    #print listdir_recursive(dir)
    #print listdir_recursive2(dir)
    print listdir_recursive3(dir)
