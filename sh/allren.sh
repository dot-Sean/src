#!/bin/sh

find . -name "*.html" -exec sh -c 'nm={}; mv -f $nm ${nm/%.html/.htm}' \;
