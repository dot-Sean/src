#!/usr/bin/env ruby
st = "\033[7m" # Escape sequence for reverse starting
ed = "\033[m" # Escape sequence for reverse ending
re = /#{$*.shift()}/
while gets()
  if ~ re
    sw = 2
    case sw
      when 0
        gsub!(re, st + $& + ed)
      when 1
        gsub!(re, "#{st}\\0#{ed}")
      else
        gsub!(re) do |str|
          st + str + ed
        end
    end
    print
  end
end

