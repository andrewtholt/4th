include lib/timer.4th
include lib/comus.4th

: count-bits1 ( u1 -- u2 )
  0 swap  ( count integer_being_examined)
  begin
    dup
  while
    1 under+
    dup 1- and
  repeat
  drop
;

: count-bits2 ( u1 -- u2 )
  33 0
  do
    dup 0=  if  drop  i  leave  then
    dup 1- and
  loop ;

[hex]
: count-bits3 ( u1 -- u2 )
      DUP  1 RSHIFT  55555555 AND  -
      33333333 2DUP  AND >R  SWAP  2 RSHIFT AND  R> +
      0F0F0F0F 2DUP  AND >R  SWAP  4 RSHIFT AND  R> +
      00FF00FF 2DUP  AND >R  SWAP  8 RSHIFT AND  R> +
      0000FFFF 2DUP  AND >R  SWAP 10 RSHIFT AND  R> + ;
[decimal]

defer count-bits

: speed  ( xt -- )
  is count-bits
  TIMER-RESET
  999000 0 do
    0
    \ Number of bits set will range from 0 to 9.
    10 0 do
      dup count-bits
      drop
      \ Set & unset bits will alternate (10101...)
      2 lshift  1+
    loop
    drop
  loop
  .ELAPSED cr ;

: test   cr
  ." version 1: "
  ['] count-bits1 speed
  ." version 2: "
  ['] count-bits2 speed
  ." version 3: "
  ['] count-bits3 speed
;

test