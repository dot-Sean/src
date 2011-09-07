#! /usr/bin/ruby
# /home/tetsu/src/ruby/hack/io/iops.rb
# Created: May 26,1998 Tuesday 03:32:43
# Author: tetsu(WATANABE Tetsuya)
# $Id: iops.rb,v 1.1 1998/05/26 19:37:09 tetsu Exp $
# usage:

def random_read(dev, offset)
  begin
    d = File.open(dev)
  rescue
    STDERR.print "can not open \"#{dev}\"\n"
    return
  end
  srand(Seed)
  1.upto(Loop) do |i|
    d.pos = ((rand(Seek) + offset) / Size).to_i * Size
    dummy = d.read(Size)
    if dummy.length != Size
      STDERR.print "read length \"#{dummy.length}\"\n"
    end
  end
  d.close
end

def sequential_read(dev, offset)
  begin
    d = File.open(dev)
  rescue
    STDERR.print "can not open \"#{dev}\"\n"
    return
  end
  1.upto(Loop) do |i|
    d.pos = i * Size + offset
    dummy = d.read(Size)
    if dummy.length != Size
      STDERR.print "read length \"#{dummy.length}\"\n"
    end
  end
  d.close
end

Seed = if ARGV.size > 0 then ARGV.shift.to_i else 0 end
KB = 1024
MB = KB * 1024
Loop = 1000
Seek = 5000 * MB
Size = 4 * KB
Offset = 0 * MB

for disk in ['sda']
  dev = '/dev/' + disk
  startTime = Time.now
  sequential_read(dev, 0)
  t = Time.now - startTime
  printf("%s %6.3f %6.2f\n", dev, t, Loop / t)

  startTime = Time.now
  random_read(dev, Seek)
  t = Time.now - startTime
  printf("%s %6.3f %6.2f\n", dev, t, Loop / t)
end

exit
