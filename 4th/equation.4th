\ 4tH equation solver - Copyright 2007,2009 J.L. Bezemer
\ You can redistribute this file and/or modify it under
\ the terms of the GNU General Public License

1 constant BadTerm                     \ an invalid term has been entered
false value right?                     \ are we on the right side?
variable Snum                          \ variable holding numbers
variable Sx                            \ variable holding x terms
                                       \ apply sign
: ?negate if negate then ;             ( n f -- n | -n)
: ?sign swap ?negate false swap ;      ( f n -- -f n | -f -n)
: ?error catch if ." Invalid equation" cr quit then ;
: .intermediate over over 0 .r ." x = " . cr ;
: .solution /mod ." x = " 0 .r dup if ." , remainder " . else drop then cr ;
: prompt ." Enter an equation (e.g. 2x - 10 = 0)" cr cr refill drop ;
: +n right? 0= ?negate ?sign Snum +! ; ( n --)
: +x right? ?negate ?sign Sx +! ;      ( n --)
: x? 1- 2dup chars + c@ [char] x = ;   ( a1 n1 -- a1 n1-1 f)
: negative? dup if over c@ [char] - = dup >r if chop then r> else false then ;
: #x negative? >r dup if number else 2drop 1 then r> ?negate ;
: c= >r 1 = swap c@ r> = and ;         ( a n c -- f)
: is-minus [char] - c= tuck if 0= then swap 0= ;
: is-plus [char] + c= 0= ;             ( a n -- f)
: is-number number error? dup >r if drop else +n then r> ;
: is-equal [char] = c= dup if dup to right? then 0= ;
: is-x x? if #x error? if drop else +x false exit then else 2drop then true ;
                                       \ resolve term
: term                                 ( a n --)
  2>r                                  \ throw term on stack
  2r@ is-minus if                      \ is it a minus sign
    2r@ is-plus if                     \ is it a plus sign
      2r@ is-x if                      \ is it an x term
        2r@ is-number if               \ is it a number
          2r@ is-equal if BadTerm throw then
        then                           \ if not, it is an illegal term
      then
    then
  then 2r> 2drop                       \ clear the return stack
;
                                       \ decompose all terms
: decompose false begin bl parse-word dup while term repeat 2drop drop ;
: solve 0 dup Sx ! Snum ! decompose Snum @ Sx @ .intermediate .solution ;
: equation prompt ['] solve ?error ;   ( --)
                                       \ prompt for an equation and solve it
equation