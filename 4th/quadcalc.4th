\ 4tH Quadratic Equation Calculator - Copyright 2007,2009 J.L. Bezemer
\ You can redistribute this file and/or modify it under
\ the terms of the GNU General Public License

\ Reasonably reliable between -13 < x < 13
\ Will OVERFLOW if used beyond specifications
\ and return INCORRECT results!

include lib/math.4th
include lib/fraction.4th

: factor? over over dup * * max-n 100 [/] < ;
: factor dup 0= if 10000 else 1 begin factor? while 10 * repeat then ;
: scale dup 0< abort" Unsolvable equation" factor dup dup * swap 2* ;  
: b*b-4ac rot * 2* 2* swap dup * swap - ;
: -b/2a 2* swap negate swap v/ ;       ( b a -- v)
: sqrt/2a scale >r * sqrt swap r> * v/ ;
: .answer over over - ." x- = " v. cr ." x+ = " + v. cr ;
: term [char] , parse-word number ;    ( --n)
: terms term dup 0= abort" A cannot be zero" term term ;
: parms ." Ax^2 + Bx + C = 0" cr cr ." Enter A, B, C: " refill drop terms ; 
: quadra parms >r over over r> b*b-4ac >r over -b/2a swap r> sqrt/2a .answer ;

quadra
