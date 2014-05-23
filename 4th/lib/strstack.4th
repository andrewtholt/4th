\ 4tH library - STRING STACK - Copyright 2004,2012 J.L. Bezemer
\ You can redistribute this file and/or modify it under
\ the terms of the GNU General Public License

[UNDEFINED] N! [IF]
INCLUDE lib/ncoding.4th
[THEN]

[UNDEFINED] STRING-STACK [IF]
1 nells +constant +sp
2 nells +constant +s0
8 nells +constant +slack

: s@ n@ n@ count ;                        ( s -- a n)
: s> dup n@ tuck nell- swap n! n@ count ; ( s -- a n)
                                          \ initialize the stack
: string-stack                            ( a n --)
  chars over + over over over             ( a s0 a s0 a)
  +sp n! +s0 tuck n! swap n!              ( --)
;
                                          \ put a string on the stack
: >s                                      ( a n s --)
  over 1+ chars over +sp n@ swap -        ( a n s p)
  over n@ nell+ dup >r +slack over >      ( a n s p f)
  if drop 2dup +s0 n@ swap 1+ chars - then
  >r -rot r@ place r@ over                ( s p s)
  +sp n! r> r@ n! r> swap n!              ( --)
;

[DEFINED] 4TH# [IF]
  hide +sp
  hide +s0
  hide +slack
[THEN]
[THEN]
