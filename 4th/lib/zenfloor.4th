\ 4tH library - FLOOR ZEN - Copyright 2009,2012 J.L. Bezemer
\ You can redistribute this file and/or modify it under
\ the terms of the GNU General Public License
\ include lib/zenfloat.4th

[UNDEFINED] floor [IF]
[UNDEFINED] ZenFP [IF] [ABORT] [THEN]  \ ONLY works with Zen FP library
: floor
  dup 0< if                            \ exponent < zero?
    2dup abs 0 ?do 10 / loop >r        \ set exponent to zero
    over 0< r@ swap >r s>f f- f0= 0= r> and r> swap if 1- then s>f
  then                                 \ check on remainder
;
[THEN]

\  10   3 floor f. cr
\  20  -1 floor f. cr
\  31  -1 floor f. cr
\   0 s>f floor f. cr
\  -4 s>f floor f. cr
\ -51  -1 floor f. cr
\ -60  -1 floor f. cr
\ -70   3 floor f. cr
