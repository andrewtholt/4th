\ 4tH library - PADDING - Copyright 2004 J.L. Bezemer
\ You can redistribute this file and/or modify it under
\ the terms of the GNU General Public License

[UNDEFINED] .padding [IF]
: .filling                             ( a1 n1 n2 c --)
  >r over max over - >r type r>
  begin dup 0> while r@ emit 1- repeat drop r> drop
;

: .padding bl .filling ;               ( a1 n1 n2 --)
                                       \ like +PLACE
: +fill                                ( a n c --)
  rot dup >r swap >r count 2dup  
  chars + >r rot over max dup rot - 
  r> swap r> fill r> place
;

: +pad bl +fill ;                      ( a n --)
[THEN]
