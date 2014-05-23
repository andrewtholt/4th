\ 4tH library - ROLL/PICK (CORE EXT) - Copyright 2003,2011 J.L. Bezemer
\ You can redistribute this file and/or modify it under
\ the terms of the GNU General Public License

[UNDEFINED] ROLL [IF]
: ?dup dup if dup then ;
: pick ?dup if swap >r 1- recurse r> swap else dup then ;
: roll ?dup if swap >r 1- recurse r> swap then ;
[THEN]