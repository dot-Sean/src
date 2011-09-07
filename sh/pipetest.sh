#!/bin/bash
# -*- coding: utf-8 -*-
# http://tldp.org/LDP/abs/html/

# 値を参照する必要がなければ d1 でも可。d3 と d7 がまとも。

# つまり、以下のいずれか
#  - 普通に sub process の while read に流し込む
#  - main process で走らせるために、後ろから流し込む
#  - 配列で受け渡す → array, spaces_in_files.sh も参照

# --------------------------------------------------------------------
# Not work (cannot get the values in the loop outside which)

lastline="(null)"
seq 10 19 | while read i
do
  echo d1: "$i"
done | while read i
do
  lastline="$i"
done
echo d: "$lastline"
# --------------------------------------------------------------------
# Use nameless pipe (must remove pipe, mendoi)

lastline="(null)"
pipe0=`mktemp /tmp/XXXXXX`
rm -f $pipe0
mkfifo $pipe0
seq 20 29 | while read i
do
  echo d2: "$i"
done > $pipe0 &
while read i
do
  lastline="$i"
done < $pipe0
echo d: "$lastline"
rm -f $pipe0
# --------------------------------------------------------------------
# Use process substitution (reverse order) 比較的素直だし、同時に走る

lastline="(null)"
while read i
do
  echo dd: $i
  lastline="$i"
done < <(
  seq 30 39 | while read i
  do
    echo d3: "$i"
  done
)
echo d: "$lastline"
# --------------------------------------------------------------------
# Use process substitution & redirection to stdin (stdin must to be fixed.
# fd 3 is available?)

lastline="(null)"
exec 3>&0 < <(
  seq 40 49 | while read i
  do
    echo d4: "$i"
  done
) 
while read i
do
  lastline="$i"
done
exec 0<&3 3<&-
echo d: "$lastline"
# --------------------------------------------------------------------
# Use process substitution & redirection to 3 (good! fd 3 is available?)

lastline="(null)"
exec 3< <(
  seq 50 59 | while read i
  do
    echo d5: "$i"
  done
) 
while read i
do
  lastline="$i"
done <&3
echo d: "$lastline"

# --------------------------------------------------------------------

# Use process substituion & array for lines

lastline="(null)"
lines=()
while read -r line
do
  lines[${#lines[@]}]="$line"
done < <(
  seq 60 69 | while read i
  do
    echo d6: "$i"
  done
)
for line in "${lines[@]}"
do
  lastline="$line"
done
echo d: "$lastline"

# --------------------------------------------------------------------

# sub process 終了後に main process が走ることに注意

function readlines () { IFS=$'\n' read -d $'\0' -a "$1"; }
readlines lines < <(
  seq 70 79 | while read i
  do
    echo d7: "$i"
  done
)
for line in "${lines[@]}"
do
  lastline="$line"
done
echo d: "$lastline"
