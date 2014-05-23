\ 4tH library - FLS FFS - Copyright 2011 J.L. Bezemer
\ You can redistribute this file and/or modify it under
\ the terms of the GNU General Public License

\ An implementation of the BSD ffs() and fls() functions.

\ Bits are numbered starting from 1, starting at the right-most (least
\ significant) bit. A return value of zero from any of these words means
\ that the argument was zero.

[UNDEFINED] firstbit [IF]
: firstbit                             ( n1 -- n2)
  dup if 1 swap begin dup 1 and 0= while swap 1+ swap 1 rshift repeat drop then
;

: lastbit                              ( n1 -- n2)
  dup if 1 swap begin dup 1 <> while swap 1+ swap 1 rshift repeat drop then
;
[THEN]