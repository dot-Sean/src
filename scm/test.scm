#!/usr/bin/gosh

(define (usage rc)
  (format (current-error-port)
   "Usage: ~a regexp file ...\n" *program-name*)
  (exit rc) )

(define (grep re input-port)
  (with-input-from-port
    input-port
    (lambda ()
      (port-for-each
        (lambda
          (line)
          (when (rxmatch re line)
            (format #t "~a:~a: ~a\n"
              (port-name input-port)
              (- (port-current-line input-port) 1)
              line )))
        read-line ))))

(define (main args)
  (set! args (cdr args))
  (if (null? args)
    (usage 1)
    (let ((re (string->regexp (car args))))
      (if (null? (cdr args))
        (grep re (current-input-port))
        (for-each 
          (lambda (file)
            (call-with-input-file
              file
              (lambda (input-port) (grep re input-port)) ))
          (cdr args) ))))
  0 )
