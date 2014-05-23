\ 4tH library - Hashing - Copyright 2009 J.L. Bezemer
\ You can redistribute this file and/or modify it under
\ the terms of the GNU General Public License
\ ---
\ See: http://www.cse.yorku.ca/~oz/hash.html

[UNDEFINED] (hash) [IF]
: (djb2) dup 5 lshift + + ;            ( c n1 -- n2)
: (sdbm) dup >r 6 lshift r@ 16 lshift + + r> - ;
: (hash) 2swap bounds ?do over i c@ -rot execute loop nip ;
: djb2 ['] (djb2) 5381 (hash) ;        ( a n -- n2)
: sdbm ['] (sdbm) 0 (hash) ;           ( a n -- n2)

[DEFINED] 4th# [IF]
hide (djb2)
hide (sdbm)
[THEN]
[THEN]
