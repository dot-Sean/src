#!/usr/bin/gosh

; port in Scheme abstracts input and output.

(define (usage rc)
  (format 
    (current-error-port)
    "Usage: ~a regexp file ...\n" *program-name*)
  (exit rc) )

(define (grep re input-port)
  ; with-input-from-port port thunk
  ; set port as the input port and call thunk
  (with-input-from-port
    input-port
    (lambda ()
      ; port-for-each fn reader
      ; port->list does not go. The line info disappear.
      (port-for-each
        (lambda (line)
          (if (rxmatch re line)
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
        ; for each filename
        (for-each 
          (lambda (file)
            ; call-with-input-file string proc
            ; open port with string as filename and call proc
            (call-with-input-file
              file
              (lambda (input-port) (if input-port (grep re input-port)))
              :if-does-not-exist #f ))
          (cdr args) ))))
  0 )
