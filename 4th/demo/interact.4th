\ Interpreter example - (c) 1996,2008 HanSoft & Partners

true constant ignorenumbers            \ ignore numbers 
[needs lib/interprt.4th]
                                       \ define the 'NotFound'
:noname 2drop ." Not found!" cr ; is NotFound
                                       \ is mandatory too! 
: test ." test " ;                     \ dummy executables
: this ." This " ;                     \ part of the test interpreter
: a    ." a " ;
: is_  ." is " ;

create wordset                         \ dummy dictionary
  ," test" ' test ,                    \ must be assigned
  ," this" ' this ,                    \ to dictionary
  ," is"   ' is_  ,
  ," a"    ' a    ,
  NULL ,

wordset to dictionary                  \ assign to dictionary

: testit refill drop interpret cr ;    \ read a line and interpret

testit

