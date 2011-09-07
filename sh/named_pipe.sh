#!/bin/sh

logfile=test.log
rm -f $logfile
mknod $logfile p
while read line
do
  logger $line
done < $logfile &

cat /etc/fstab > $logfile
