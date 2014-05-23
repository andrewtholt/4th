\ -- KISS generator --
\ http://objectmix.com/fortran/385655-random_number-intrinsic-gfortran.html
\ Algorithm 2007 by George Marsaglia
\ 4tH version 2009, Bill Cook

[UNDEFINED] kiss [IF]
variable x
variable y
variable z
variable w

max-n constant MAX-KISS

: m ( k n ** m ) over swap shift xor ;
: znew z @ dup 65535 and 18000 * swap -16 shift + dup z ! ;
: wnew w @ dup 65535 and 30903 * swap -16 shift + dup w ! ;

: seed4! w ! z ! y ! x ! ;
: seed4@ x @ y @ z @ w @ ;

: cong x @ 69069 * 1327217885 + dup x ! ;
: shr3 y @ 13 m -17 m 5 m dup y ! ;
: mwc znew 16 shift wnew + ;
: kiss mwc cong + shr3 + ;

: randomize time x ! cong y ! shr3 z ! cong w ! ;

[UNDEFINED] random [IF]
aka kiss random
MAX-KISS constant MAX-RAND
[THEN]

[DEFINED] 4th# [IF]
hide m
hide znew
hide wnew
[THEN]
[THEN]
