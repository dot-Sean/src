;#!/usr/bin/gosh

; libc -> scheme lib
; http://www.shiro.dreamhost.com/scheme/gauche/man/gauche-refj_297.html

(display
  (format #f
    "~a is ~s.\n"
    (string-append "The" " " "answer")
    (+ 2 3) ))
