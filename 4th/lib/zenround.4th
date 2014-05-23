\ 4tH library - FROUND ZEN - Copyright 2009 J.L. Bezemer
\ You can redistribute this file and/or modify it under
\ the terms of the GNU General Public License
\ include lib/zenfloat.4th

[UNDEFINED] FROUND [IF]
[UNDEFINED] FTRUNC [IF] include lib/zentrunc.4th [THEN]
: fround                               ( f1 -- f2)
  2dup 2dup f>s dup 1 and 0= >r s>f f- fabs 5 -1 f= r> and 0=
  if over 0< 5 -1 rot if fnegate then f+ then ftrunc
;
[THEN]
