\ Copyright (C) 2001 by Marc Feeley, All Rights Reserved.

\  This is a compiler for the Tiny-C language.  Tiny-C is a
\  considerably stripped down version of C and it is meant as a
\  pedagogical tool for learning about compilers.  The integer global 
\  variables "a" to "z" are predefined and initialized to zero, and it 
\  is not possible to declare new variables.  The compiler reads the 
\  program from standard input and prints out the value of the 
\  variables that are not zero.  The grammar of Tiny-C in EBNF is:

\   <program> ::= <statement> 
\   <statement> ::= "if" <paren_expr> <statement> | 
\                   "if" <paren_expr> <statement> "else" <statement> | 
\                   "while" <paren_expr> <statement> | 
\                   "do" <statement> "while" <paren_expr> ";" | 
\                   "{" { <statement> } "}" | 
\                   <expr> ";" | 
\                   ";" 
\   <paren_expr> ::= "(" <expr> ")" 
\   <expr> ::= <test> | <id> "=" <expr> 
\   <test> ::= <sum> | <sum> "<" <sum> 
\   <sum> ::= <term> | <sum> "+" <term> | <sum> "-" <term> 
\   <term> ::= <id> | <int> | <paren_expr> 
\   <id> ::= "a" | "b" | "c" | "d" | ... | "z" 
\   <int> ::= <an_unsigned_decimal_integer> 

\  Here are a few invocations of the compiler: 

\  % echo "a=b=c=2<3;" | ./a.out 
\  a = 1 
\  b = 1 
\  c = 1 
\  % echo "{ i=1; while (i<100) i=i+i; }" | ./a.out 
\  i = 128 
\  % echo "{ i=125; j=100; while (i-j) if (i<j) j=j-i; else i=i-j; }" | ./a.out 
\  i = 25 
\  j = 25 
\  % echo "{ i=1; do i=i+10; while (i<50); }" | ./a.out 
\  i = 51 
\  % echo "{ i=1; while ((i=i+10)<50) ; }" | ./a.out
\  i = 51 
\  % echo "{ i=7; if (i<5) x=1; if (i<10) y=2; }" | ./a.out 
\  i = 7 
\  y = 2 

\  The compiler does a minimal amount of error checking to help
\  highlight the structure of the compiler. 

\ ---------------------------------------------------------------------------
\ Forth conversion (C) 2006 by Marcel Hendrix.

\ A translation of Marc Feeley's Tiny C compiler.
\ It is somewhat interesting because of the embedded virtual machine.

\ I have added two debugging helpers ( TRUE TO DEBUG? ):

\  1. a utility to show the parsed text
\  2. a decompiling tracer

\ Feel free to alter this code. It is really a stretch
\ to call this a "C compiler" :-)

\ It is probably possible to rewrite this code without using the
\ virtual machine part, as Forth can do this interpretively.

\ Run with MAIN <type some text>^D

\ Stop input by typing ^D  (the EOI character).

\ It is assumed that your Forth has ENUM (Wil Baden's toolchest)
\ and STRUCT (gForth distribution). Words like DOC ENDDOC $"
\ ?ALLOCATE =CELL CLEAR are hopefully obvious.

\ -marcel
\ ---------------------------------------------------------------------------
\ 4tH conversion (C) 2010 by Hans Bezemer.
\ ---------------------------------------------------------------------------

\ *********************
  FALSE CONSTANT DEBUG?
\ *********************

STRUCT
    FIELD: kind 
    FIELD: o1
    FIELD: o2
    FIELD: o3
    FIELD: val
END-STRUCT node%

 2048 constant #paragraph
node% constant /paragraph

[pragma] forcecellheap
[pragma] casesensitive

include lib/istype.4th
include lib/ctos.4th
include lib/compare.4th
include lib/ansmem.4th
include lib/constant.4th
include lib/locals.4th
include lib/argopen.4th

 4 constant ^D
10 constant ^J
13 constant ^M
26 constant ^Z

char { constant '{'
char } constant '}'
char ( constant '('
char ) constant ')'
char + constant '+'
char - constant '-'
char < constant '<'
char ; constant ';'
char = constant '='

\ ---------------------------------------------------------------------------

\ Lexer

0 ENUM DO_SYM     ENUM ELSE_SYM   ENUM IF_SYM     ENUM WHILE_SYM
  ENUM LBRA       ENUM RBRA       ENUM LPAR       ENUM RPAR
  ENUM PLUS       ENUM MINUS      ENUM LESS
  ENUM SEMI       ENUM EQUAL      ENUM INT
  ENUM ID         CONSTANT EOI

CREATE cwords
  ," do" ," else"
  ," if" ," while"
  NULL ,

BL VALUE ch
0  VALUE sym 
0  VALUE int_val 

100 string id_name

1 string next_ch does> dup 1 accept if c@ else drop ^D then to ch ;

: numbers? ( -- ) 
        0 TO int_val                   \ missing overflow check 
        BEGIN   ch is-digit
        WHILE   int_val 10 *  ch [char] 0 - + TO int_val
                next_ch  INT TO sym 
        REPEAT ;

: var? ( -- ) 
        0 id_name c!                   \ missing overflow check
        BEGIN   ch is-lower ch [char] _ = OR
        WHILE   ch c>s id_name +PLACE  next_ch
        REPEAT 
        0 TO sym 
        BEGIN  cwords sym TH @C NULL <>
        WHILE  cwords sym TH @C COUNT id_name COUNT COMPARE
        WHILE  sym 1+ TO sym
               cwords sym TH @C NULL =
               IF
                 id_name COUNT 1 =
                 IF DROP ID TO sym EXIT ELSE ABORT" Expected variable" THEN
               THEN
        REPEAT ; 

: (next_sym) ( -- )
        BEGIN 
                ( CASE statement) ch 
                 BL  OVER = IF DROP  next_ch                     ELSE
                 ^J  OVER = IF DROP  next_ch                     ELSE
                 ^M  OVER = IF DROP  next_ch                     ELSE 
                 ^D  OVER = IF DROP           EOI   TO sym EXIT  ELSE
                 ^Z  OVER = IF DROP           EOI   TO sym EXIT  ELSE
                 '{' OVER = IF DROP  next_ch  LBRA  TO sym EXIT  ELSE 
                 '}' OVER = IF DROP  next_ch  RBRA  TO sym EXIT  ELSE 
                 '(' OVER = IF DROP  next_ch  LPAR  TO sym EXIT  ELSE 
                 ')' OVER = IF DROP  next_ch  RPAR  TO sym EXIT  ELSE 
                 '+' OVER = IF DROP  next_ch  PLUS  TO sym EXIT  ELSE 
                 '-' OVER = IF DROP  next_ch  MINUS TO sym EXIT  ELSE 
                 '<' OVER = IF DROP  next_ch  LESS  TO sym EXIT  ELSE 
                 ';' OVER = IF DROP  next_ch  SEMI  TO sym EXIT  ELSE 
                 '=' OVER = IF DROP  next_ch  EQUAL TO sym EXIT  ELSE 
                     is-digit
                         IF  numbers? EXIT
                         ELSE  ch is-lower 0= ABORT" Syntax error"
                               var?     EXIT 
                         THEN
                DROP THEN THEN THEN THEN THEN THEN THEN THEN THEN THEN THEN THEN THEN THEN
        AGAIN ;

DEBUG? [IF]
: next_sym  ( -- )
  (next_sym)
        ." NEXT_SYM = "
        ( CASE statement) sym 
          DO_SYM    OVER = IF DROP ." do "        ELSE 
          ELSE_SYM  OVER = IF DROP ." else "      ELSE 
          IF_SYM    OVER = IF DROP ." if "        ELSE 
          WHILE_SYM OVER = IF DROP ." while "     ELSE 
          EOI       OVER = IF DROP  ." EOI "      ELSE 
          LBRA      OVER = IF DROP  ." { "        ELSE 
          RBRA      OVER = IF DROP  ." } "        ELSE 
          LPAR      OVER = IF DROP  ." ( "        ELSE 
          RPAR      OVER = IF DROP  ." )"         ELSE 
          PLUS      OVER = IF DROP  ." + "        ELSE 
          MINUS     OVER = IF DROP  ." - "        ELSE 
          LESS      OVER = IF DROP  ." < "        ELSE 
          SEMI      OVER = IF DROP  ." ; "        ELSE 
          EQUAL     OVER = IF DROP  ." = "        ELSE 
          INT       OVER = IF DROP  int_val .     ELSE 
          ID        OVER = IF DROP  id_name count type   ELSE
        DROP THEN THEN THEN THEN THEN THEN THEN THEN THEN THEN THEN THEN THEN THEN THEN THEN CR ;
[ELSE]
        aka (next_sym) next_sym
[THEN]

\ --------------------------------------------------------------------------- 

\ Parser. 

0 ENUM VAR      ENUM CST
  ENUM ADD      ENUM SUB      ENUM LT       ENUM SET
  ENUM IF1      ENUM IF2      ENUM WHILE1   ENUM DO1
  ENUM EMPTY
  ENUM SEQ
  ENUM EXPR1
  CONSTANT PROG

: new_node ( k -- node )
       node% ALLOCATE ABORT" Out of memory"
        ( k ) tuck kind ! ;

DEFER paren_expr ( -- node )  \ forward declaration 

\ <term> ::= <id> | <int> | <paren_expr> 
: term ( -- node )   
        0 LOCALS{ enum x } 
        sym ID  = IF    VAR new_node x $ !
                        id_name C@ [char] a -  x $ @ val !
                        next_sym x $ @ end-locals EXIT
               THEN
        sym INT = IF    CST new_node x $ !
                        int_val  x $ @ val ! 
                        next_sym x $ @ end-locals EXIT
                THEN
        paren_expr end-locals hide x ; 

\ <sum> ::= <term> | <sum> "+" <term> | <sum> "-" <term> 
: sum ( -- node )   
        0 term LOCALS{ enum x enum t } 
        BEGIN   sym PLUS =  sym MINUS = OR 
        WHILE   x $ @ t $ !
                sym PLUS = IF  ADD  ELSE  SUB  THEN new_node x $ !
                next_sym 
                t $ @ x $ @ o1 !
                term  x $ @ o2 ! 
        REPEAT  x $ @ end-locals hide x hide t ; 

\ <test> ::= <sum> | <sum> "<" <sum>
: test ( -- node ) 
        0 sum LOCALS{ enum x enum t }
        sym LESS = IF   x $ @ t $ !
                        LT new_node x $ !
                        next_sym 
                        t $ @  x $ @ o1 ! 
                        sum x $ @ o2 ! 
                THEN x $ @ end-locals hide x hide t ;

\ <expr> ::= <test> | <id> "=" <expr> 
: expr ( -- node )  
        sym ID <> IF  test EXIT  THEN
        0 test LOCALS{ enum x enum t }
        x $ @ kind @ VAR =  sym EQUAL = 
        AND IF  x $ @ t $ !
                SET new_node x $ !
                next_sym 
                t $ @  x $ @ o1 !
                expr x $ @ o2 ! 
         THEN x $ @ end-locals hide x hide t ;

\ <paren_expr> ::= "(" <expr> ")" 
:NONAME ( -- node ) 
        0 LOCALS{ enum x }  
        sym LPAR <> ABORT" Expected ("
        next_sym 
        expr x $ ! 
        sym RPAR <> ABORT" Expected )"
        next_sym 
        x $ @ end-locals hide x
; IS paren_expr 

: statement ( -- node )
        0 0 LOCALS{ enum x enum t }
        \ "if" <paren_expr> <statement> 
        sym IF_SYM =    IF  IF1 new_node x $ ! next_sym
                            paren_expr x $ @ o1 ! 
                            statement  x $ @ o2 ! 
                            \ ... "else" <statement> 
                            sym ELSE_SYM = IF  IF2 x $ @ kind ! next_sym statement x $ @ o3 !  THEN
                            x $ @ end-locals EXIT
                     THEN

        \ "while" <paren_expr> <statement> 
        sym WHILE_SYM = IF  WHILE1 new_node x $ !
                            next_sym  
                            paren_expr x $ @ o1 !
                            statement  x $ @ o2 ! 
                            x $ @ end-locals EXIT
                     THEN

        \ "do" <statement> "while" <paren_expr> ";" 
        sym DO_SYM =    IF  DO1 new_node x $ ! 
                            next_sym  statement x $ @ o1 !
                            sym WHILE_SYM <> ABORT" Expected 'while'"
                            next_sym  paren_expr x $ @ o2 ! 
                            sym SEMI <> ABORT" Expected ;"
                            next_sym 
                            x $ @ end-locals EXIT 
                     THEN

        \ ";" 
        sym SEMI = IF   EMPTY new_node x $ ! next_sym x $ @ end-locals EXIT  THEN

        \ "{" { <statement> } "}"  
        sym LBRA =      IF  EMPTY new_node x $ ! next_sym 
                            BEGIN  sym RBRA <> 
                            WHILE  x $ @ t $ ! SEQ new_node x $ !
                                   t $ @ x $ @ o1 !
                                   statement x $ @ o2 !
                            REPEAT 
                            next_sym x $ @ end-locals EXIT
                     THEN

        \ <expr> ";" 
        EXPR1 new_node x $ !
        expr x $ @ o1 ! 
        sym SEMI <> ABORT" Expected ;"
        next_sym x $ @ end-locals
        hide x hide t ;

0 VALUE root 

\ <program> ::= <statement> 
: PROGRAM ( -- node )   
        PROG new_node TO root
        next_sym 
        statement root o1 !
        sym EOI <> ABORT" Unexpected EOF"
        root ; 

\ --------------------------------------------------------------------------- 

\ Code generator. 

0 ENUM IFETCH
  ENUM ISTORE
  ENUM IPUSH
  ENUM IPOP
  ENUM IADD
  ENUM ISUB
  ENUM ILT
  ENUM JZ
  ENUM JNZ
  ENUM JMP
  CONSTANT HALT

1000 array object

object VALUE =here 

: g    ( code -- )  =here ! =here CELL+ TO =here ;   \ missing overflow check
: hole ( -- here )  =here   =here CELL+ TO =here ;
: fix  ( 'src 'dst -- )      OVER - SWAP ! ;         \ missing overflow check 

: C ( node -- ) 
        0 0 LOCALS{ enum p1 enum p2 enum x }
        ( CASE statement) x $ @ kind @ 
          VAR    OVER = IF DROP  IFETCH g x $ @ val @ g                                     ELSE
          CST    OVER = IF DROP  IPUSH  g x $ @ val @ g                                     ELSE
          ADD    OVER = IF DROP  x $ @ o1 @ c x $ @ o2 @ c  IADD g                          ELSE
          SUB    OVER = IF DROP  x $ @ o1 @ c x $ @ o2 @ c  ISUB g                          ELSE
          LT     OVER = IF DROP  x $ @ o1 @ c x $ @ o2 @ c  ILT  g                          ELSE
          SET    OVER = IF DROP  x $ @ o2 @ c ISTORE g x $ @ o1 @ val @ g                   ELSE
          IF1    OVER = IF DROP  x $ @ o1 @ c JZ g hole p1 $ ! x $ @ o2 @ c p1 $ @ =here fix ELSE
          IF2    OVER = IF DROP  x $ @ o1 @ c JZ g hole p1 $ ! x $ @ o2 @ c JMP g hole p2 $ !
                     p1 $ @ =here fix x $ @ o3 @ c p2 $ @ =here fix                         ELSE
          WHILE1 OVER = IF DROP  =here p1 $ ! x $ @ o1 @ c JZ g hole p2 $ ! x $ @ o2 @ c
                     JMP g hole p1 $ @ fix  p2 $ @ =here fix                               ELSE
          DO1    OVER = IF DROP  =here p1 $ ! x $ @ o1 @ c  x $ @ o2 @ c  JNZ g  hole p1 $ @ fix ELSE
          EMPTY  OVER = IF DROP                                                             ELSE
          SEQ    OVER = IF DROP  x $ @ o1 @ c x $ @ o2 @ c                                  ELSE
          EXPR1  OVER = IF DROP  x $ @ o1 @ c  IPOP g                                       ELSE
          PROG   OVER = IF DROP  x $ @ o1 @ c  HALT g                                       ELSE
        DROP THEN THEN THEN THEN THEN THEN THEN THEN THEN THEN THEN THEN THEN THEN
        end-locals hide x hide p1 hide p2 ;

\ --------------------------------------------------------------------------- 

\ Virtual machine. 

26 ARRAY globals

0 VALUE pc 
0 VALUE sp 

: *pc++  ( -- addr )  pc dup 1+ TO pc @ ;
: --sp   ( -- )       sp CELL- TO sp ;
: pc++   ( -- )       pc CELL+ TO pc ;
: !sp++  ( a -- )     sp tuck ! 1+ TO sp ;
: sp[-2] ( -- addr )  sp CELL- CELL- ; 
: sp[-1] ( -- addr )  sp CELL- ; 

DEBUG? [IF]
: .INS ( code -- ) 
        pc CELL- . 4 SPACES
        ( CASE statement) 
          IFETCH OVER = IF DROP ." IFETCH "  pc @ [char] a + EMIT  ELSE
          ISTORE OVER = IF DROP ." ISTORE "  pc @ [char] a + EMIT  ELSE
          IPUSH  OVER = IF DROP ." IPUSH  "  pc @ .        ELSE
          IPOP   OVER = IF DROP ." IPOP   "  ELSE 
          IADD   OVER = IF DROP ." IADD   "  ELSE 
          ISUB   OVER = IF DROP ." ISUB   "  ELSE 
          ILT    OVER = IF DROP ." ILT    "  ELSE 
          JMP    OVER = IF DROP ." JMP " pc DUP CELL+ SWAP @ + CELL- . ELSE
          JZ     OVER = IF DROP ." JZ  " pc DUP CELL+ SWAP @ + CELL- . ELSE
          JNZ    OVER = IF DROP ." JNZ " pc DUP CELL+ SWAP @ + CELL- . ELSE
          HALT   OVER = IF DROP ." HALT "    ELSE 
                    ." ERROR! "  DUP .
        DROP THEN THEN THEN THEN THEN THEN THEN THEN THEN THEN THEN CR ;
[THEN]

: RUNS ( -- ) 
        object TO pc 
        BEGIN   ( CASE statement) *pc++ DEBUG? [IF]  DUP .INS  [THEN]
                  IFETCH OVER = IF DROP            globals *pc++ th @  !sp++           ELSE
                  ISTORE OVER = IF DROP  sp[-1] @  globals *pc++ th !                  ELSE
                  IPUSH  OVER = IF DROP  *pc++  !sp++                                  ELSE 
                  IPOP   OVER = IF DROP                                     --sp       ELSE 
                  IADD   OVER = IF DROP  sp[-1] @        sp[-2] +!          --sp       ELSE
                  ISUB   OVER = IF DROP  sp[-1] @ negate sp[-2] +!          --sp       ELSE
                  ILT    OVER = IF DROP  sp[-2] @ sp[-1] @ < 1 AND sp[-2] ! --sp       ELSE 
                  JMP    OVER = IF DROP  pc dup @ + TO pc                                   ELSE
                  JZ     OVER = IF DROP  --sp sp @ 0= IF pc @ ELSE 1 CELLS THEN pc + TO pc  ELSE
                  JNZ    OVER = IF DROP  --sp sp @    IF pc @ ELSE 1 CELLS THEN pc + TO pc  ELSE
                  HALT   OVER = IF DROP  EXIT                                          ELSE 
                DROP THEN THEN THEN THEN THEN THEN THEN THEN THEN THEN THEN 
        AGAIN ; 

\ --------------------------------------------------------------------------- 

\ Main program. 

: INITIALIZE ( -- ) 
        BL TO ch  
        26 0 do 0 globals I TH ! LOOP
        object TO =here 
        1000 CELLS ALLOCATE ABORT" Out of memory" TO sp ;

: VPRINT ( -- ) 
        26 0 DO  globals I TH @
                  DUP IF DUP THEN IF [char] a I + EMIT ."  = "  . CR
                    THEN
            LOOP ; 

: FREE-nodes ( node -- )
        DUP o1 @ DUP IF DUP THEN IF  FREE-nodes  THEN
        DUP o2 @ DUP IF DUP THEN IF  FREE-nodes  THEN
        FREE ABORT" Heap error" ;

: EXITIALIZE ( -- ) 
        sp FREE ABORT" Heap error" ;

: MAIN ( -- )

        INITIALIZE 
         PROGRAM C root FREE-nodes
         RUNS  VPRINT
        EXITIALIZE ;

\ 4tH interface

argn 2 < abort" Usage: tinyc filename"
input 1 arg-open main close

\ EOF
