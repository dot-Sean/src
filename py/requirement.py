ver = {}
requires = {}
required = {}

standalone = []
requires_nothing = []
not_required_by_anything = []
other = []
done = []

rep = {
  "gnome/gnome-desktop": "desktop/gnome-desktop",
  "matchbox/Xsettings-client": "matchbox/xsettings-client",
  "bootstrap/libmusicbrainz": "bootstrap/musicbrainz",
}

for line in open("/tmp/req.log").readlines():
  line = line.strip()
  if not line:
    continue
  if line[0] != "-":
    (name, version,) = line.split(" ", 1)
    if name in rep.keys():
      name = rep[name]
    ver[name] = version
    #print "d:", name, version
  else:
    line = line[1:]
    (name1, dummy, name2,) = line.split(" ", 2)
    if not requires.has_key(name1):
      requires[name1] = []
    if not name2 in requires[name1]:
      requires[name1].append(name2)

for name1 in requires.keys():
  for name2 in requires[name1]:
    if not required.has_key(name2):
      required[name2] = []
    if not name1 in required[name2]:
      required[name2].append(name1)

for name in ver.keys():
  if not requires.has_key(name) and not required.has_key(name):
    standalone.append(name)
  elif not requires.has_key(name) and required.has_key(name):
    requires_nothing.append(name)
  elif requires.has_key(name) and not required.has_key(name):
    not_required_by_anything.append(name)
  else:
    other.append(name)

def show(name1):
  if requires.has_key(name1):
    for name2 in requires[name1]:
      if not name2 in done:
        show(name2)
  if not name1 in done:
    print "%s %s" % (name1, ver[name1])
    if requires.has_key(name1):
      for name in requires[name1]:
        print "  requires: %s" % (name,)
    if required.has_key(name1):
      for name in required[name1]:
        print "  required by: %s" % (name,)
    done.append(name1)

print "\n*** Requires nothing and not required by anything"
for name in standalone:
  show(name)

print "\n*** Requires nothing"
for name in requires_nothing:
  show(name)

print "\n*** Others"
for name in other + not_required_by_anything:
  show(name)
