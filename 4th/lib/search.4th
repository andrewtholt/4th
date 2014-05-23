\ 4tH library - SEARCH (STRING) - Copyright 2003,2013 J.L. Bezemer
\ You can redistribute this file and/or modify it under
\ the terms of the GNU General Public License

\ Load COMPARE when needed
[UNDEFINED] compare [IF]
[needs lib/compare.4th]
[THEN]

[UNDEFINED] search [IF]
: search
  swap >r >r over             ( a1 n1 a1)
  over r@ - r> swap           ( a1 n1 a1 n2 n3)
  begin
    dup -1 >                  ( a1 n1 a1 n2 n3 f)
    if                        ( a1 n1 a1 n2 n3)
      -rot 2dup               ( a1 n1 n3 a1 n2 a1 n2)
      r@ over                 ( a1 n1 n3 a1 n2 a1 n2 a2 n2)
      compare                 ( a1 n1 n3 a1 n2 f)
      if                      ( a1 n1 n3 a1 n2)
        swap char+ swap       ( a1 n1 n3 a1+1 n2)
        rot 1- false          ( a1 n1 a1+1 n2 n3 -f)
      else                    ( a1 n1 n3 a1 n2)
        rot +                 ( a1 n1 a1 n2+n3)
        2nip true dup         ( a1 n2+n3 f f)
      then
    else                      ( a1 n1 a1 n2 n3)
      drop 2drop false true
    then                      ( a1 n1 -f f)
  until 
  r> drop
;
[THEN]
