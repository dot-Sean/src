#!/usr/bin/gosh

(map (lambda (s) (display s) (display "\n")) (list
  (null? ()) ; #t
  (list? '(a b c)) ; #t
  (pair? (cons 'a 'b)) ; #t
  (pair? #t) ; #f
))
