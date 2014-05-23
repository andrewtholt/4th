\ Copyright 2013, Julian Skidmore (FIGnition)
\ https://sites.google.com/site/libby8dev/home

\ Believed to be in the Public Domain

\ Benchmark (in seconds)

\      Jup-Ace             FIGn
\       (fast)    FIGn    0.9.8
\      -------   -----    -----
\ BM1     0.16    0.02    0.014
\ BM2     0.54    0.09    0.056
\ BM3     7.66    0.41    0.286
\ BM4     6.46    0.47    0.298
\ BM5     6.52    0.51    0.326
\ BM6     7.38    0.64    0.402
\ BM7    12.98    1.27    0.836

( block 0)
: time-bm
  time swap execute
  time swap - 5 spaces .
;

\ usage eg:
\  ' bm1 time-bm

( block 1)
: bm1
  cr ." S"
  10000 0 do loop
  ." E"
;

: bm2
  cr ." S"
  0 begin
    1+ dup 9999 >
  until
  ." E" drop
;

( block 2)
: bm3
  cr ." S"
  0 begin
    1+ dup dup / over
    * over + over -
    drop dup 9999 >
  until ." E"
  drop
;

: bm4
  cr ." S"
  0 begin
    1+ dup 2 / 3
    * 4 + 5 - drop dup
  9999 > until
  ." E" drop
;

( block 3)
: bm5sub ;
: bm5
  cr ." S" 0 begin
    1+ dup 2 / 3
    * 4 + 5 - drop bm5sub
  dup 9999 > until
  ." E" drop
;

: bm6
  cr ." S" 0 begin
   1+ dup 2 / 3 * 4 + 5 -
   drop bm5sub
   5 0 do loop
  dup 9999 > until
  ." E" drop
;


( block 4)
5 array m

: bm7
  cr ." S" 0 begin
   1+ dup 2 / 3 * 4 + 5 -
   drop bm5sub
   5 0 do dup i cells m + ! loop
  dup 9999 > until
  ." E" drop
;

: bm3l 0 10000 0 do i +
  negate i and i or i xor
  loop drop ;

' bm1 time-bm
' bm2 time-bm
' bm3 time-bm
' bm4 time-bm
' bm5 time-bm
' bm6 time-bm
' bm7 time-bm cr
