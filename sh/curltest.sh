#!/bin/sh
# -*- coding: euc-jp -*-

echo "���á��Ǥ�curl-7���鵭ǰ��������" | iconv -f euc-jp -t utf8 | curl -F "rspid=index" -F "rspname=knaka@curl" -F "rspaddr=" -F "rspcmnt=<-;type=text/plain" http://www.ayutaya.com/home/knaka/onposted.php
