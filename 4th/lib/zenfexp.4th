\ 4tH library - FEXP ZEN - Copyright 2009,2011 J.L. Bezemer
\ You can redistribute this file and/or modify it under
\ the terms of the GNU General Public License

[UNDEFINED] fexp [IF]
[UNDEFINED] +taylor [IF] include lib/zentaylr.4th [THEN]
[UNDEFINED] ftrunc  [IF] include lib/zentrunc.4th [THEN]

: (!) over * swap 1+ swap ;

: ^integer               ( float -- integer fraction)
  2dup ftrunc 2dup 2dup f0< >r f>s >r f- 1 s>f r> abs
  0 ?do 271828182 -8 f* loop r> if 1 s>f 2swap f/ then 2swap
;

: ^fraction              ( integer fraction -- float)
  1 dup >r >r r@ s>f 2swap 2over
  begin r@ 13 < while r> r> (!) >r r@ swap >r +taylor repeat
  r> r> drop drop 2drop 2drop f*
;

: fexp ^integer ^fraction ;

[DEFINED] 4TH# [IF]
hide (!)
hide ^integer
hide ^fraction
[THEN]
[THEN]
