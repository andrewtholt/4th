\ 4tH library - ZEN FP I/O - Copyright 2009,2011 J.L. Bezemer
\ You can redistribute this file and/or modify it under
\ the terms of the GNU General Public License

[UNDEFINED] >float [IF]                \ ONLY supports "e", no decimal point
[UNDEFINED] ZenFP  [IF] [ABORT] [THEN] \ ONLY works with Zen FP library
: >float                               ( a n -- f bool)
  2dup bounds                          \ set up loop, scan for "e"
  begin dup c@ bl or [char] e <> while over over <> while char+ repeat nip
  >r over r@ swap - tuck 1+ - r> char+ \ construct strings and convert
  swap dup 0> if number else drop dup xor then
  >r number error? r> error? rot or dup if nip nip then 0= 
;                                      \ return numbers and flag
                                       ( a n -- f)
: s>float >float 0= abort" Bad float" ;
                                       \ print an FP number in fixed format
: f.                                   ( f --)
  over 0= if dup xor then              \ fix zero
  >r dup abs s>d                       \ save exponent
  <# r@ 0 max 0 ?do [char] 0 hold loop
  r@ 0< if                             \ save any trailing zeros needed
    r@ negate 0 max 0 ?do # loop [char] . hold
  then                                 \ generate actual number
  r> drop #s sign #> type space        \ and print the whole number
;
[THEN]