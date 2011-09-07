#!/usr/bin/perl
# -*- coding: utf-8 -*-

$debug = 1;

if ($debug) { use Data::Dumper; }

@a = ("hoge", "fuga");

# ハッシュ (連想配列) 即値
%b = ("foo" => "FOO", "bar" => "BAR");

print Dumper(\@a) if $debug;
print Dumper(\%b) if $debug;
