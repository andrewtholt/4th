\ 4tH library - FLN FLOG ZEN - Copyright 2008,2012 J.L. Bezemer
\ You can redistribute this file and/or modify it under
\ the terms of the GNU General Public License
\ Ported to ZEN float by David Johnson, 2009

[UNDEFINED] fln   [IF]
[UNDEFINED] ZenFP [IF] [ABORT] [THEN]  \ ONLY works with Zen FP library

FLOAT array epsilon
FLOAT array lbase

: integer
  >r begin 2dup 1 s>f f< while lbase 2@ f* r> 1- >r repeat
  begin 2dup lbase 2@ f< 0= while lbase 2@ f/ r> 1+ >r repeat r>
;

: fraction 
  >r 0 s>f 5 -1 2rot 2dup f*
  begin
    2over epsilon 2@ 2swap f<
  while
    2dup lbase 2@ f< 0=
    if 2swap 2rot 2over f+ 2swap 2rot lbase 2@ f/ then
    2swap 2 s>f f/ 2swap 2dup f*
  repeat 2drop 2drop r>
;

: (log)
  lbase 2! 1 -12 epsilon 2! 2dup f0> 0= abort" Invalid float"
  0 integer fraction s>f f+
;

: fln 271828183 -8 (log) ;
: flog 10 s>f (log) ;

[DEFINED] 4TH# [IF]
hide integer
hide epsilon
hide lbase
hide fraction
[THEN]
[THEN]
