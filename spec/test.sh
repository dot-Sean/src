log=/tmp/rpmtest.log
make rpms
if rpm -q rpmtest
then
  sudo rpm -e rpmtest
fi
rm -f $log
touch $log
sudo rpm -Uvh ~/rpm/RPMS/noarch/rpmtest-1.0-1.noarch.rpm 2>&1 > /dev/null | tee -a $log
echo @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ | tee -a $log
echo @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
sudo rpm -Uvh ~/rpm/RPMS/noarch/rpmtest-1.1-1.noarch.rpm 2>&1 > /dev/null | tee -a $log
echo @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ | tee -a $log
sudo rpm -e rpmtest 2>&1 > /dev/null | tee -a $log
echo "Log output has been put out to $log."

