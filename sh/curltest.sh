#!/bin/sh
# -*- coding: euc-jp -*-

echo "むむっ、ではcurl-7から記念カキコ。" | iconv -f euc-jp -t utf8 | curl -F "rspid=index" -F "rspname=knaka@curl" -F "rspaddr=" -F "rspcmnt=<-;type=text/plain" http://www.ayutaya.com/home/knaka/onposted.php
