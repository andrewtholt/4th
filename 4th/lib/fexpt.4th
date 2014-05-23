\ 4tH library - FEXP - Copyright 2008,2010 J.L. Bezemer
\ You can redistribute this file and/or modify it under
\ the terms of the GNU General Public License

[UNDEFINED] fexp [IF]
[UNDEFINED] +taylor [IF] include lib/taylor.4th  [THEN]
[UNDEFINED] e       [IF] include lib/fpconst.4th [THEN]

: (!) over * swap 1+ swap ; 

: ^integer               ( float -- integer fraction)
  fdup f>d 2dup d>f f- 1 s>f 2dup d0< -rot dabs d>u
  0 ?do e f* loop if 1 s>f fswap f/ then fswap
;

: ^fraction              ( integer fraction -- float)
  1 dup dup s>f fswap fover
  begin over 13 < while (!) dup +taylor repeat
  drop drop fdrop fdrop f*
;

: fexp ^integer ^fraction ;

[DEFINED] 4TH# [IF]
hide (!)
hide ^integer
hide ^fraction
[THEN]
[THEN]
