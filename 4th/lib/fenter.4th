\ 4tH library - FENTER - Copyright 2010 J.L. Bezemer
\ You can redistribute this file and/or modify it under
\ the terms of the GNU General Public License

[UNDEFINED] fenter [IF]
[UNDEFINED] >float [IF] [ABORT] [THEN]
: fenter begin refill drop bl parse-word >float until ;
[THEN]