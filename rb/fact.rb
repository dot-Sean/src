#!/usr/bin/ruby

print begin
  m = 1
  (1..(ARGV[0].to_i)).each { |n|
    m *= n
  }
  m
end
