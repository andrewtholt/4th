\ Copyright http://wiki.forthfreak.net/index.cgi?HigherOrderFunctions
\ Copyright 4tH version 2005, J.L. Bezemer
\ HigherOrderFunctions

[UNDEFINED] foreach [IF]
: foreach ( 'f addr count -- )
  bounds do
    I @ over execute
  loop drop ;

: .cells ( addr n -- )
  :noname . ; rot rot foreach ;

\ where : f ( n -- m )
: map ( 'f addr count -- )
  cells bounds do
    I @ over execute I !
  loop drop ;

\ where : f ( st n -- st' )
: zip ( st 'f addr count -- st' )
  cells bounds do
    I @ swap dup >r execute r>
  loop drop ;
[THEN]
