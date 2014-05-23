\ 4tH library - ANS counted strings - Copyright 2012 J.L. Bezemer
\ You can redistribute this file and/or modify it under
\ the terms of the GNU General Public License

\ Note these words form an efficient way to handle counted strings, but
\ since they use PLACE and +PLACE they are still ASCIIZ strings - but with
\ a count character.

\ Therefore, when porting ANS Forth programs you will have to take the
\ terminating NULL character into account when allocating string storage
\ space.

\ In short, increase the allocation with one character, just to be sure!

[UNDEFINED] ccount [IF]
: ccount dup char+ swap c@ ;
: cplace over over c! char+ place ;
: +cplace over over c@ + over c! char+ +place ;
[THEN]

\ 32 string Hello
\ s" Hello" Hello cplace s"  world!" Hello +cplace
\ Hello ccount type cr depth .