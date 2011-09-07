#!/bin/bash
# -*- coding: utf-8 -*-

# function へ、配列で渡し、戻すことができる。global なしに

for i in "$@"
do
  echo d0: $i
done
echo

files=("$@")
for file in "${files[@]}"
do
  echo d1: $file
done
echo

# Be sure that the "while" statement is run by subprocess
find . -name "*.txt" | while read file
do
  echo d2: $file
done
echo

files0=(*.txt)
for file in "${files0[@]}"
do
  echo d3: $file
done
echo

function array_append () { eval "$1[\${#$1[@]}]="\$2""; }

files1=()
while read line
do
  files1[${#files1[@]}]="$line"
done < <(find . -name "*.txt")
for file in "${files1[@]}"
do
  echo d4: $file
done
echo

function rename () {
  while read line
  do
    echo ${line/txt/hoge}
  done
}

#alias readlines="IFS=$'\n' read -d '' -a"

IFS: Internal Field Seprator
function readlines () { IFS=$'\n' read -d $'\0' -a "$1"; }

#files2=("${files1[@]/txt/hoge}")
#_IFS=$IFS; IFS=$'\n'; files2=($(find . -name "*.txt" | rename)); IFS=$_IFS
#IFS=$'\n' read -d $'\0' -a files2 < <(find . -name "*.txt" | rename)
#IFS=$'\n' read -d $'\0' -a files2 <<< "$(find . -name "*.txt" | rename)"
#readlines files2 < <(find . -name "*.txt" | rename)
#readlines files2 <<< "$(find . -name "*.txt" | rename)"
IFS=$'\n' read -d "" -a files2 < <(find . -name "*.txt" | rename)
for file in "${files2[@]}"
do
  echo d6: $file
done
echo

for str in ${files2[0]}
do
  echo d7: $str
done
echo

function putit () {
  local head=$1
  local -a files3=("${@:2}")
  for file in "${files3[@]}"
  do
    echo $head $file
  done
}

putit "d8:" "${files2[@]}"
echo

echo "d9:" "${files3[@]}"
echo

_IFS=$IFS; IFS=$'\n' # Not inherited by sub processes
# Waits until subprocess finishes
for line in $(
  for i in `seq 5`
  do
    echo $i hoge
    #sleep 1
  done
)
do
  echo d10: $line
done
IFS="$_IFS"
echo
