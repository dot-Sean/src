#!/usr/bin/env tcl

# function reference
# http://www.sra.co.jp/tb/tclman/

proc foo {a {b 1024}} {
  if {"$a" == "bar"} {
    error "Bar!"
  }
  puts "$a and $b"
  puts {$a and $b}
  puts [format "%s (%d)" $a [expr $b * 2]]
}

proc main {argv0 argc argv} {
  set x 256
  foo "hoge" $x
  foo "fuga"
  puts "--------"
  if {$x < 256} {
    puts "AAA"
  } elseif {$x == 256} {
    puts "BBB"
  } else {
    puts "CCC"
  }
  puts "--------"
  for {set i 0} {$i < 10} {incr i} {
    if {$i < 3} {
      continue
    } elseif {$i >= 7} {
      break
    }
    puts -nonewline $i
  }
  puts ""
  puts "--------"
  if [catch {foo "bar"} emsg] {
    puts "$emsg" 
  }
  puts "--------"
  set x 1024
  switch [expr $x * 2] {
    2048 {
      puts "d: bingo"
    }
    default {
      puts "default"
    }
  }
  puts "--------"
  set a0("apple") "APPLE"
  set a0("banana") "BANANA"
  set a0("candy") "CANDY"
  parray a0
  array set a1 {
    "xylophone" "XYLOPHONE"
    "yosemite" "YOSEMITE"
    "zephyranthus" "ZEPHYRANTHUS"
  }
  parray a1
  puts "--------"
  set l {"Don" "Tako" "Su"}
  foreach i $l {
    puts stdout "$i"
  }
  lappend l "Poo"
  puts [lindex $l 3]
  puts [lsort $l]
  puts "--------"
  set s ""
  set delim ""
  set s "$s$delim$argv0"
  set delim ", "
  for {set i 0} {$i < $argc} {incr i} {
    set s [format "$s$delim%s" [lindex $argv $i]]
  }
  puts "argv: $s"
  puts "--------"
  set s "abc"
  if {[string compare -nocase $s "ABC"] == 0} {
    puts "matched"
  } else {
    puts "not matched"
  }
  # http://www.sra.co.jp/tb/tclman/string
  puts [string toupper $s]
  puts [string length $s]
  puts [split "/usr/X11R6/lib/" "/"]
  append s "def"
  puts "$s"
}

main $argv0 $argc $argv
