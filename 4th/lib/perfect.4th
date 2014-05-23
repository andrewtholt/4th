\ Taken from http://rosettacode.org 
\ 4tH version 2010,2011 Hans Bezemer

[DEFINED] perfect? [IF]
: perfect? 1 over 2/ 1+ 2 ?do over i mod 0= if i + then loop = ;
[THEN]
