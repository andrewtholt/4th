\ 4tH library - YIELD - Copyright 2014 J.L. Bezemer
\ You can redistribute this file and/or modify it under
\ the terms of the GNU General Public License

[UNDEFINED] yield [IF]
: yield r> r> swap >r >r ;             \ remember that ; compiles EXIT!
: grab r> r> drop >r ;                 \ so add a [FORCE] when using it as
[THEN]                                 \ the last word in a definition