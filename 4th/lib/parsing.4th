\ 4tH library - PARSING - Copyright 2009, 2014 J.L. Bezemer
\ You can redistribute this file and/or modify it under
\ the terms of the GNU General Public License

[UNDEFINED] "parse" [IF]
defer (noquote?)                       ( a n -- f)
                                       \ generic parser
: (parse)                              ( c -- a n)
  dup parse dup                        \ save delimiter and parse
  if                                   \ is string not empty?
    over c@ [char] " =                 \ is the first character a quote?
    if                                 ( n1 a2 n2)
      begin 2dup (noquote?) while >r over parse chars + over - dup r> = until
      2dup 1- chars + c@ [char] " = if 1- then chop 0 max
    then                               \ remove quotes and normalize length
  then rot drop                        \ drop the delimiter
;

\ Perform a normal parse, but take quoted fields
\ with embedded delimiters into account
                                       ( c -- a n)
: "parse" [: 1- chars + c@ [char] " <> ;] is (noquote?) (parse) ;

\ Perform a normal parse, but take quoted fields 
\ with embedded delimiters and escaped quotes into account

: "parse\"                             ( c -- a n)
  [: 1- 2dup chars + c@ [char] " =
  if dup if 1- chars + c@ [char] \ = exit then then 2drop true ;] is (noquote?)
  (parse)                              \ return false on unescaped quote
;

\ Perform a nearly RFC 4180 compliant parse and take quoted fields
\ with embedded delimiters and quotes into account

: parse-csv                            ( c -- a n)
  [: 0 -rot bounds ?do i c@ [char] " = if 1+ then loop 1 and ;] is (noquote?)
  (parse)
;                                      \ return false on even number of quotes

\ perform a user defined parse, but leave a false flag when EOL is detected
: (parse?) >in @ >r execute >in @ r> > ;
: parse? [: parse ;] (parse?) ;        ( c -- a n f)
: "parse"? ['] "parse" (parse?) ;      ( c -- a n f)
: "parse\"? ['] "parse\" (parse?) ;    ( c -- a n f)
: parse-csv? ['] parse-csv (parse?) ;  ( c -- a n f)

[DEFINED] 4TH# [IF]
  hide (noquote?)
  hide (parse)
[THEN]
[THEN]
