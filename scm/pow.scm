;#!/usr/bin/guile

(define (pow-sub x)
  (if (= x 1) x (* x (pow-sub (- x 1)))))

(define (pow x)
  (if (> x 0) (pow-sub x)))

(display (format #f "~s\n" (pow 4)))
