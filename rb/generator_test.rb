#!/usr/bin/ruby
# -*- coding: utf-8 -*-

require 'generator'

def count_from(i)
  return (Generator.new { |g|
    while true
      g.yield(i)
      i += 1
    end
  } )
end

count_from(256).each { |i|
  print "#{i}\n"
  if (i > 300)
    break
  end
}
