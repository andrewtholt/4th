\ 4tH library - DOUBLE SHARP - Copyright 2009,2012 J.L. Bezemer
\ You can redistribute this file and/or modify it under
\ the terms of the GNU General Public License

[UNDEFINED] num>char [IF]
[UNDEFINED] mu/mod [IF] [NEEDS lib/mixed.4th] [THEN]

/hold 2 * constant /dhold
/dhold string dholdbuf
dholdbuf /dhold + constant dholdend
variable hld

: num>char dup 9 > if 7 + then [char] 0 + ;
: dhold hld -1 over +! @ c! ;
: <d# dholdend hld ! ;
: d#> 2drop hld @ dholdend over - ;
: dsign rot 0< if [char] - dhold then ;
: d# base @ mu/mod rot num>char dhold ;
: d#s begin d# 2dup or 0= until ;

[DEFINED] 4TH# [IF]
  hide hld
  hide dholdbuf
  hide dholdend
[THEN]
[THEN]
