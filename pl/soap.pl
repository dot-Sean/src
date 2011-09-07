#!/usr/bin/perl

use strict;
use SOAP::Lite;

my $oSoap = SOAP::Lite
 ->uri('urn:SoapEx')
 ->proxy('http://www.hippo2000.info/cgi-bin/soapEx.cgi')
 ->new();

print "square measure: ",
 0 + $oSoap->calcArea(5, 10, 10, 15)->result(), "\n";

