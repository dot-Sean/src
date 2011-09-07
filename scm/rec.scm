#!/usr/bin/gosh

(define (func l)
  (if (null? l)
    ()
    (let* ((x (car l)))
      (cons
        (cons
          x
          (cond
            ((> x 5) #t)
            (#t #f)
          )
        )
        (func (cdr l))
      )
    )
  )
)

(display (func '(1 2 3 4 5 6 7 8)))