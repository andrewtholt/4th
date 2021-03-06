\ FRACOUT.F

\ Simple fixed-point output with optional thousands
\ separator.

\ Common or separate floating-point stack.

\ Does not support NAN/INF, negative-zero etc.


[UNDEFINED] F.R   [IF]
[UNDEFINED] SIGN. [IF] include lib/fpdot.4th [THEN]

0 VALUE COMMAS

\ Convert real number r to string c-addr u in fixed-point
\ notation with n places right of the decimal point.
: (F.) ( F: r -- ) ( n -- c-addr u )
  0 MAX  DUP >R  0 ?DO 10 S>F F* LOOP
  <#. ( round)  FDUP F0< ( sign) R> SWAP >R >R
  FABS  R> 0 ?DO #. LOOP
  [CHAR] . HOLD
  COMMAS IF  #,S. ELSE  #S. THEN
  R> SIGN.  #>. ;

\ Display real number r in fixed-point notation right-
\ justified in a field width u with n places right of
\ the decimal point.
: F.R ( F: r -- ) ( n u -- )
  >R (F.) R> OVER - SPACES TYPE ;

[THEN]


