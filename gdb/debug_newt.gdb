# break
# run
# continue
# print
# step
# next
# set
# finish

echo ----------------------------------------------------------------------\n

define show_argv
  if argv
    set var ($i = 0)
    while ($i < argc)
      printf "argv[%d]: %s\n", $i, argv[$i]
      set var ($i ++)
    end
  end
end

break newt.c:main

command 1
  # 注意、すごい量
  #info variables
  echo *** cp0\n
  show language
  echo *** cp1\n
  info frame
  echo *** cp2\n
  show_argv
end  

#break newt.c:foo

break newt.c:foo if psz

break newt.c:foo

run hoge fuga

echo ----------------------------------------------------------------------\n
