\ FINPUT.F  version 0.1  2009-05-07

\ A minimum yet compliant Forth-94 implementation of
\ >FLOAT. Works with separate or common stack float
\ models.

\ The code is intended as a model only. No particular
\ effort has been made to optimize for speed or
\ accuracy.

\ This code is PUBLIC DOMAIN.  Use at your own risk.

\ History:

\ 0.1  Replaced .1E F* with 10E F/ for better accuracy.
\      Added conditional to allow leading decimal point
\      on forth text input.
\ 0.1a Adapted to ANS float for 4tH by Hans Bezemer

\ Loading FINPUT v0.1  2009-05-07

[UNDEFINED] >float    [IF]
[UNDEFINED] f+        [IF] [ABORT] [THEN]
[UNDEFINED] >snumber  [IF] include lib/tonumber.4th [THEN]

VARIABLE exp  \ exponent
VARIABLE dpf  \ decimal point

FLOAT array tmp

: getc ( a u -- a' u' c )
  CHOP OVER CHAR- C@ ;

\ get sign
: gets ( a u -- a' u' n|0 )
  DUP IF
    getc  DUP [CHAR] - = IF EXIT THEN
              [CHAR] + <> IF -1 /STRING THEN
  THEN 0 ;

: getdigs ( a u -- a' u' )
  BEGIN  DUP  WHILE
    getc  [CHAR] 0 - max-n and DUP 9 > IF
      DROP  -1 /STRING  EXIT
    THEN
    S>F  tmp F@  10 S>F F*  F+  tmp F!
    dpf @  exp +!
  REPEAT ;

: getmant ( a u -- a' u' flag )
  TUCK getdigs  DUP IF
    OVER C@ [CHAR] . = IF
      -1 dpf !  CHOP  getdigs
    THEN
  THEN ROT OVER - dpf @ + ;

: getexp ( a u -- a' u' )
  DUP IF
    OVER C@ bl or DUP [CHAR] e =
    SWAP [CHAR] d = OR IF CHOP THEN
  THEN
  gets >R  0 -ROT >SNUMBER ROT
  R> IF NEGATE THEN  exp @ +
  BEGIN  DUP IF DUP THEN WHILE  DUP 0<
    IF    1+  tmp F@  10 S>F  F/
    ELSE  1-  tmp F@  10 S>F  F*  THEN  tmp F!
  REPEAT ;

: >FLOAT ( c-addr u -- r true | false )
  0 S>F tmp F!  0 exp !  0 dpf !
  2DUP -TRAILING IF DROP ELSE DROP DUP XOR THEN
  DUP IF
    gets >R true >R getmant
    IF R> DROP getexp DUP >R THEN R>
    IF 2DROP R> DROP FALSE EXIT THEN
  ELSE  0 >R
  THEN  2DROP  tmp F@  R> IF FNEGATE THEN TRUE ;

: S>FLOAT >float 0= abort" Bad float" ;

[DEFINED] 4TH# [IF]
  hide exp
  hide dpf
  hide tmp
  hide getc
  hide gets
  hide getexp
  hide getmant
  hide getdigs
[THEN]
[THEN]


