def show(obj):
  print "dir(obj):", dir(obj)
  print "obj.__dict__:",
  try:
    print obj.__dict__
  except Exception, msg:
    print
  print "obj.__methods__:",
  try:
    print obj.__methods__
  except:
    print
  print "obj.__members__:",
  try:
    print obj.__members__
  except:
    print
  print

def func():
  import mypyobject
  
  show(mypyobject)
  
  hoge = mypyobject.MyPyObject()
  hoge.set("fuga");
  
  show(hoge)

print "cp0"
func()
print "cp1"
func()
print "cp2"
