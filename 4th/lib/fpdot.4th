\ Written by Ed.
\ Believed to be in the Public Domain

[UNDEFINED] SIGN. [IF]
[UNDEFINED] FDUP  [IF] [ABORT] [THEN]

\ Floating-point pictured numeric output operators
: <#. ( F: r1 -- r2 )  FROUND <# ;
: #. ( F: r1 -- r2 )  10 S>F F/ FDUP FLOOR FSWAP FOVER F-
  10 S>F F* FROUND F>S  [CHAR] 0 + HOLD ;
: #S. ( F: r1 -- r2 )  BEGIN #. FDUP F0= UNTIL ;
: #>. ( F: r -- ) ( c-addr u )  FDROP 0 #> ;
: SIGN. ( flag -- )  IF [CHAR] - HOLD THEN ;

\ Like #S. but inserts commas after each 3 digits
: #,S. ( F: r1 -- r2 )
  0  BEGIN  >R  #.  FDUP F0= 0= WHILE
    R> 1+  DUP 3 = IF  [CHAR] , HOLD  DROP 0 THEN
  REPEAT  R> DROP ;

[THEN]