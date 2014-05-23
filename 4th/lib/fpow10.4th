\ 4tH library - F**2 F10** 1/F - Copyright 2012 J.L. Bezemer
\ You can redistribute this file and/or modify it under
\ the terms of the GNU General Public License

\ Library for quickly scaling ANS FP numbers. F10** scales
\ from 1e0 up to 1e24 in five FP operations or less.

[UNDEFINED] me>f  [IF]                 \ dummy definition for Zen FP
  [DEFINED] ZenFP [IF] [IGNORE] me>f [ELSE]
[UNDEFINED] float [IF] [ABORT]       [THEN]
: u>f u>d d>f ;                        ( u -- f)
: f**2 fdup f* ;                       ( f -- f')
: 1/f 1 u>f fswap f/ ;                 ( f -- 1/f)
                                       ( n -- f)
create f10** 10 , 100 , 10000 , 100000000 ,
does> 
  over 9 > if                          \ compute 1e10 - 1e24 with floats
    swap 9 - swap 1 u>f 4 bounds       \ adjust exponent accordingly
    do dup if dup 1 and if i @c u>f f* then 2/ else leave then loop
    drop 1000000000 u>f f* exit        \ scale by 1e9 and exit
  then drop 1 swap 0 ?do 10 * loop u>f \ compute 1e0 - 1e9 with integers
;

: me>f dup 0< if 1 u>f abs f10** f/ else f10** then s>f f* ;
[THEN]
[THEN]