\ 4tH library - YES/NO? - Copyright 2010 J.L. Bezemer
\ You can redistribute this file and/or modify it under
\ the terms of the GNU General Public License

[UNDEFINED] yes/no? [IF]
: yes/no?                              ( a n -- f)
  false dup >r                         \ save flag and setup dummy address
  begin                                \ display mesage and get Y/N answer
    begin drop 2dup type ."  (y/n)? " refill bl parse-word 0<> rot and until
    c@ bl or dup [char] y =            \ was 'y' answered, if so set flag
    if r> 0= dup >r else dup [char] n = then
  until drop 2drop r>                  \ check if 'y' or 'n' was entered
;                                      \ otherwise repeat the procedure
[THEN]

\ s" Do you want to play again" yes/no? . cr depth .

