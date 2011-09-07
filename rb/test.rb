#!/usr/bin/ruby

if true
  puts "Hello"
end

a = ["hoge", "fuga", "foo", "bar",]

a.each { |e|
  puts e if /o/ =~ e
}
