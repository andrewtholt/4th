\ 4tH library - ANS FILE - Copyright 2006,2012 J.L. Bezemer
\ You can redistribute this file and/or modify it under
\ the terms of the GNU General Public License

[UNDEFINED] r/o [IF]
         input constant r/o            \ read-only fam
        output constant w/o            \ write-only fam
input output + constant r/w            \ read-write fam

[IGNORE] bin                           ( --)

: (read) accept ;                      ( a n1 -- n2)
: (readln) refill ;                    ( -- f)
: (write) type ;                       ( a n --)
: (writeln) type cr ;                  ( a n --)
: (close) close ;                      ( h --)
: (tell) tell ;                        ( h -- n)
: (flush) sync ;                       ( --)
: (create) 2dup output open close ;    ( a n --)
: (io) swap cin >r cout >r use catch 0<> r> use r> use ;
                                       ( h xt -- i*x f)
: file-size                            ( h -- n f)
  dup tell >r (error) over seek        \ save position and seek eof
  if -1 else dup tell then r> rot      \ now tell the position and adjust
  seek over or 0<                      \ return file to its old position
;

: read-line                            ( addr n1 h -- n2 f1 f2)
  >in @ >r source 2>r                  \ save current buffer
  >r 1+ source! r>                     \ adjust and set new buffer
  ['] (readln) (io)                    \ do I/O
  0 parse nip -rot                     \ get characters read
  2r> source! r> >in !                 \ restore buffer
;

\ Note that FILE-SIZE, REPOSITION-FILE and FILE-POSITION usually take
\ an unsigned double number. If this library is used for porting
\ purposes, do not forget to apply S>D and D>S when needed!

: open-file open error? ;              ( a n fam -- h f)
: close-file ['] (close) catch 0<> ;   ( h -- f)
: file-position ['] (tell) catch 0<> ; ( h -- n f)
: read-file ['] (read) (io) ;          ( a n1 h -- n2 f)
: write-file ['] (write) (io) ;        ( a n h -- f)
: flush-file ['] (flush) (io) ;        ( h -- f)
: write-line ['] (writeln) (io) ;      ( a n h -- f)
: file-status input open error? dup 0= if over close then ;

: create-file                          ( a n fam -- h f)
  dup >r input output + =              \ if opened in read/write mode
  if ['] (create) catch if 2drop r> true exit then then
  r> open-file                         \ quickly create a file before opening
;

aka seek reposition-file               ( n h -- f)

[DEFINED] 4TH# [IF]
  hide (read)
  hide (readln)
  hide (write)
  hide (writeln)
  hide (close)
  hide (tell)
  hide (flush)
  hide (create)
  hide (io)
[THEN]
[THEN]
