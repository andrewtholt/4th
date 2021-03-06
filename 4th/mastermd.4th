\ Taken from http://rosettacode.org 
\ 4tH version 2010, Hans Bezemer

include lib/choose.4th
include lib/range.4th

4 constant /hidden
/hidden string hidden

: ok? ( str -- ? )
  dup /hidden <> if 2drop false exit then
  1 9 lshift 1- -rot
  bounds do
    i c@ [char] 1  -
    dup 0 9 within 0= if 2drop false leave else
    1 swap lshift over and
    dup 0= if nip leave else
    xor then then
  loop 0<> ;
 
: init
  begin
    hidden /hidden bounds do 9 choose [char] 1 + i c! loop
    hidden /hidden ok?
  until ;
 
: check? ( addr -- solved? )
  0
  /hidden 0 do
    over i + c@
    /hidden 0 do
      dup hidden i + c@ = if     swap
        i j = if 8 else 1 then + swap
      then
    loop drop
  loop nip
  8 /mod tuck ."  => " . ." black, " . ." white" cr
  /hidden = ;
 
: guess: ( "1234" -- )
  init ." Guess the 4 unique digits, 1-9." cr
  begin
    ." Code: " refill drop bl parse 2dup ok? 0=
    if 2drop ." Bad guess! (4 unique digits, 1-9)" cr false else drop check? then
  until cr ." You guessed it!" cr ;

guess: