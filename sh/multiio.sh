#!/bin/bash
# -*- coding: utf-8 -*-

pids=""

(for i in $(seq 1000); do echo d1: $i; sleep 1; done > /tmp/test1.txt) &
pids="$pids $!"

(for i in $(seq 1000); do echo d2: $i; sleep 1; done > /tmp/test2.txt) &
pids="$pids $!"

byebye() {
  for pid in $pids
  do
    kill $pid
  done
}

trap "byebye" 1 2 13 15

sleep 10
byebye
