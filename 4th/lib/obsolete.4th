\ 4tH library - CORE EXT Obsolete - Copyright 2007 J.L. Bezemer
\ You can redistribute this file and/or modify it under
\ the terms of the GNU General Public License

[UNDEFINED] EXPECT [IF]
variable #tib
variable span

/tib #tib !
: expect 1- accept span ! ;
: query cin stdin use refill drop use ;
[THEN]