\ Minimal Scientific calculator: RPN or "FORTRAN/BASIC" style.  The latter by
\ using Wil Baden's OPG Formula Translator.
 
include lib/zenfloat.4th 
include lib/zenans.4th 
include lib/fpin.4th 
include lib/fpout.4th 
include lib/evaluate.4th
include lib/opgftran.4th 
 
: _+ f+ ; 
: _- f- ; 
: _* f* ; 
: _/ f/ ; 
 
: _.  f.  space ; 
: let [char] : parse ftran evaluate ;
: _quit quit ; 
 
create wordlist 
  ," +"          ' _+ , 
  ," -"          ' _- , 
  ," *"          ' _* , 
  ," /"          ' _/ , 
  ," ."          ' _. , 
  ," quit"       ' _quit , 
  ," let"        ' let , 
  NULL , 
 
wordlist to dictionary                \ assign wordlist to dictionary 
 
\ The interpreter itself 
: mycalc 
  standard-math
  begin                               \ show the prompt and get a command 
    ." OK" cr refill drop             \ interpret and issue oops when needed 
    ['] interpret catch if ." Oops " then 
  again                               \ repeat command loop eternally 
; 
 
mycalc 
