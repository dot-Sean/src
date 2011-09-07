import popen2

pinfo = popen2.Popen4("od /bin/bash")
#print "d: rc: %d" % (rc,)
for line in pinfo.fromchild.readlines():
  print line
rc = pinfo.wait()

