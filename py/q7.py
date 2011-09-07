#!/usr/bin/python
import Image
import sys
img = Image.open("oxygen.png")
for x in range(0, img.size[0], 7):
  (r, g, b, dummy,) = img.getpixel((x, img.size[1] / 2,))
  if r == g and g == b:
    sys.stdout.write(chr(r))


for i in [105, 110, 116, 101, 103, 114, 105, 116, 121]:
  sys.stdout.write(chr(i))

# http://www.pythonchallenge.com/pc/def/integrity.html
