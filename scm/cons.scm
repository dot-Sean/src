(define (func x)
  (if (> x 0)
    (cons 'x (func (- x 1)))
  )
)

(display (func 3))
