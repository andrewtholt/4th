\ 4tH library - COMBSORT with different end - Copyright 2011 J.L. Bezemer
\ You can redistribute this file and/or modify it under
\ the terms of the GNU General Public License

[UNDEFINED] sort [IF]
include lib/instsort.4th               \ obviously, no sort was included yet
aka sort insertionsort                 \ rename insertionsort
hide sort                              \ now forget the old name
                                       \ note PRECEDES is already defined
: sort                                 ( a n --)
  dup >r                               \ save count on the stack
  begin
    dup 8 >                            \ check if maximum gap reached
  while
    10 13 */ over over                 ( a g a g)
    begin                              ( a g a g)
      rot dup r@ <                     ( a a g g f)
    while                              ( a a g g)
      swap >r swap >r swap             ( g a)
      over cells r@ + over             ( g a g+a a)
      over @ over @ 2dup precedes      ( g a g+a a [g+a] [a] f)
      if >r swap ! r> swap ! else drop drop drop drop then
      cell+ swap 1+ r> r>              ( a+1 g+1 a g)
    repeat                             ( a+1 a g g+1)
    drop rot drop                      ( a g)
  repeat drop r>                       ( a n)
  insertionsort                        ( --)
;
[THEN]
