#!/bin/bash
# -*- coding: utf-8 -*-

id=hoge
wait_time=5
test_time=10

# --------------------------------------------------------------------
# Parameters for each nodes

userhost_ap="root@vm-test1.priv"
destshell_ap="ssh -T $userhost_ap"
cmd_ap="/root/run-test"

# --------------------------------------------------------------------
# Send remote scripts

cat <<'EOF' | $destshell_ap "cat > $cmd_ap"
#!/bin/bash
id=$1
wait_time=$2
test_time=$3
logdir=/tmp/dummy/logs/
stdout_log=$logdir/sfa-stdout.txt
stderr_log=$logdir/sfa-stderr.txt
tmpdir=/tmp/data-$id
rm -fr $tmpdir
mkdir $tmpdir
pids=""
sleep $wait_time
# --
sar -A -o $tmpdir/sar 5 10000000 > /dev/null 2>&1 &
pids="$pids $!"
# --
bye() {
  for pid in $pids
  do
    kill $pid
  done
}
trap "bye" 1 2 13 15
sleep $test_time
bye
EOF

# --------------------------------------------------------------------
# Run remote scripts and wait

pids=""

$destshell_ap $cmd_ap $id $wait_time $test_time &
pids="$pids $!"

for pid in $pids
do
  echo Waiting ...
  wait $pid
done

# --------------------------------------------------------------------
# Fetch data

scp -r $userhost_ap:/tmp/data-$id /tmp
