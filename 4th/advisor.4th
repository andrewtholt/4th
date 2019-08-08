[pragma] ignorenumbers                 ( it's not a calculator)
include lib/interprt.4th

\ In this part all the functions that the interpreter should know are
\ defined. In this case the ADVISOR program of Prof. Ting.
\ All that follows is his, except for some very minor changes.

: yes   CR ." I am glad to hear that."
        CR
        ;

: no    CR ." I am sorry about that."
        CR ." maybe we can brighten your visit a bit."
        CR
        ;

: question
        CR ." Any more problems you want to solve?"
        CR ." What kind ( sex, job, money, health ) ?"
        CR
        ;

: sex   CR ." Is your problem TOO MUCH or TOO LITTLE?"
        CR
        ;

: too  ;                                ( noop for syntax smoothness )

: much  CR ." You call that a problem?!! I SHOULD have that problem."
        CR ." If it really bothers you, take a cold shower."
        question
        ;

: little
        CR ." Why are you here!"
        CR ." You should be in Tokyo or New York of Amsterdam or"
        CR ." some place with some action."
        question
        ;

: health
        CR ." My advise to you is:"
        CR ."      1. Take two tablets of aspirin."
        CR ."      2. Drink plenty of fluids."
        CR ."      3. Go to bed (along) ."
        question
        ;

: job   CR ." I can sympathize with you."
        CR ." I have to work very long every day with no pay."
        CR ." My advise to you, is to open a rental computer store."
        question
        ;

: money
        CR ." Sorry!  I am broke too."
        CR ." Why don't you sell encyclopedias or marry"
        CR ." someone rich or stop eating, so you won't "
        CR ." need so much money?"
        question
        ;

: _quit quit ;

\ Now the Interpreter begins. In the DICTIONARY the links are made between
\ the interpreter and the program. First the string that triggers the word,
\ second the link of the corresponding word.

create wordlist
  ," yes"      ' yes ,
  ," no"       ' no  ,
  ," question" ' question ,
  ," sex"      ' sex ,
  ," too"      ' too ,
  ," much"     ' much ,
  ," little"   ' little ,
  ," health"   ' health ,
  ," job"      ' job ,
  ," money"    ' money ,
  ," exit"     ' _quit ,
  NULL ,

wordlist to dictionary

:noname CR ." I'm warning you, never say '" type ." ' again!" question ;
        is NotFound

\ This is the interface between the program and the interpreter. Not
\ very interesting, I guess.

: Advisor
        CR ." Hello!  My name is Creating Computer."
        CR ." Hi there!"
        CR ." Are you enjoying yourself here?"
        CR REFILL DROP INTERPRET
        CR ." Say!"
        CR ." I can solved all kinds of problems except those dealing"
        CR ." with Greece.  What kind of problems do you have"
        CR ." ( sex, health, money or job )?"
        CR begin refill drop interpret again
        ;

[DEFINED] 4TH# [IF] advisor [THEN]

