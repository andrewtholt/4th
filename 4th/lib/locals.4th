\ 4tH library - LOCALS - Copyright 2005 J.L. Bezemer
\ You can redistribute this file and/or modify it under
\ the terms of the GNU General Public License

\ Typical use:
\ : subtract
\   locals{ enum a enum b }
\     b $ @ a $ @ - . cr
\     hide a hide b
\   end-locals
\ ; 
\ 5 2 subtract

[undefined] $ [if]
[undefined] #locals [if]
512 constant #locals
[then]

\ private declarations
#locals array (locals)                 \ locals stack

(locals) dup                           \ initialize both pointers
value |local                           \ bottom of stack frame
value local|                           \ top of stack frame

\ public declarations
0 constant locals{                     ( -- 0)
                                       \ loads locals from stack
: }                                    ( n --)
  dup >r 0 ?do local| i cells + ! loop r>
  cells dup cell+ swap local| + tuck ! \ save # allocated cells
  local| to |local cell+ to local|     \ update stack pointers
;
                                       \ fetches local variable
: $ cells |local + ;                   ( n -- x)
: end-locals |local to local| local| dup cell- @ - (locals) max to |local ;
                                       \ drops stack frame
[defined] 4th# [if]
hide (locals)
hide |local
hide local|
[then]
[then]
