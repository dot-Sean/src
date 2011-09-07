#!/usr/bin/env ruby

# an iterator is a function which takes a block as an argument
def my_while(cond)
  if (! cond)
    return
  end
  yield
  retry
end

i = 0
while (i < 10)
  print "#{i}, "
  i = i + 1
end
print "\n"

i = 0
my_while (i < 10) do
  print "#{i}, "
  i = i + 1
end
print "\n"


