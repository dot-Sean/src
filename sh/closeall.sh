#!/bin/sh
for fd in `seq 3 \`ulimit -n\``; do eval "exec $fd>&-"; done; echo hoge
