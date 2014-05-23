\ 4tH library - Fractional arithmatic - Copyright 1982, Leo Brodie
\ 4tH version - 2006,2012 J.L. Bezemer

[UNDEFINED] 10K [IF] [needs lib/constant.4th] [THEN]
[UNDEFINED] '?' [IF] [needs lib/chars.4th]    [THEN]

[UNDEFINED] v. [IF]
 16384 constant +1

: v* +1 */ ;
: v/ +1 swap */ ;
: v>s 10K v* ;
: s>v 10K v/ ;
: v. v>s dup abs <# # # # # '.' hold #s sign #> type space ;
                                       \ split fraction
: (/v) +1 1- over over invert and -rot and ;
: /v dup 0< if abs (/v) negate swap negate else (/v) swap then ;
                                       ( v1 -- v2 v3)
[DEFINED] 4th# [IF]
  hide (/v)
  hide +1
[THEN]
[THEN]

\ Combinations
\ ============
\ v v  v*  v
\ v c  v*  c
\ c v  v*  c
\ v v  v/  v
\ c c  v/  v
\ c v  v/  c
\ v v  +   v
\ v v  -   v

\ v = fractional value
\ c = cell value