#!/bin/sh

# How to call python without /usr/bin/env

"exec" "python" "$0" "$@"

import sys
for arg in sys.argv:
  print arg
