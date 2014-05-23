\ 4tH library - Constants - Copyright 2006,2013 J.L. Bezemer
\ You can redistribute this file and/or modify it under
\ the terms of the GNU General Public License

[UNDEFINED] 10K [IF]
10000 constant 10K                     ( scaling constant )
[THEN]

[UNDEFINED] unit-bits [IF]
8 constant unit-bits                   ( bits per unit )
[THEN]

[UNDEFINED] char-bits [IF]
unit-bits /char * constant char-bits   ( bits per char )
[THEN]

[UNDEFINED] cell-bits [IF]
unit-bits /cell * constant cell-bits   ( bits per cell )
[THEN]

[UNDEFINED] highbit [IF]
(error) constant highbit               ( highbit in cell) 
[THEN]

[UNDEFINED] lowbits [IF]
max-n constant lowbits                 ( lowbits in cell)
[THEN]

[UNDEFINED] NULL [IF]
-1 constant NULL                       ( NULL pointer)
[THEN]

[UNDEFINED] +UL [IF]                   ( cast for unsigned 32 bits numbers)
[hex] 7fffffff 1+ +constant +UL [decimal]
[THEN]