\  OPG Formula Translation   
\  Formula Translation using Operator Precedence Grammar
\ =========================================================
\  This is a implementation of Formula Translation.  It will
\  translate Fortran-style assignments `varname=expr` and
\  expressions `expr` to Forth.
\  An segment between |bars| will be treated as normal Forth.

\ Original Code by Wil Baden 2000-05-15
\ 4tH version David Johnson and Hans Bezemer, 2011-06 
\   (Comments below are from Wil Baden's original code but
\      have been modified to reflect the current 4tH version.)

\  The resulting translations are the natural expansions.

\      s" a-b-c-d"  Ftran
\        a F@  b F@  F-  c F@  F-  d F@  F-

\      s" a*b-c*d" Ftran
\        a F@  b F@  F*  c F@  d F@  F*  F-

\      s" (a-b)*(c-d)" Ftran
\        a F@  b F@  F-  c F@  d F@  F-  F*

\      s" x = -1" Ftran
\        s" -1E0" s>float  x F!

\      s" x = (-b - SQRT (b * |FDUP| - 4*a*c)) / (2*a)" Ftran
\        b F@ FNEGATE b F@  FDUP F*
\        s" 4E0" s>float a F@ F*  c F@  F*  F-  FSQRT  F-
\        s" 2E0" s>float a F@  F*  F/  x F!

\  If a function doesn't begin with `F` an `F` prefix will be added 
\   (or as defined in the compiler options below).

\  All numbers are floating point, but this default can be changed with  
\  the 4tH words: Forth-Math ( -- )   and   Standard-Math ( -- ).
\  For example:
\                   Standard-Math
\                   s" 123*(a-b)/c" Ftran           gives:
\                     123  a @  b @  -  *  c @  /

\  Variables begin with a letter, continue with letters and digits, 
\  and are not followed by a left parenthesis mark.  Function-calls
\  have the same form but are followed by a left parenthesis mark.

\  The operators are:

\      +    -    *    /    ^

\  Assignments are made with `=`.  Multiple arguments of a
\  function are separated by commas.

\  Spaces are deleted before translation, except between `|`
\  and `|`.

\  This program uses Julian V. Noble's concept but not his implementation.
\  Thanks to Marcel Hendrix for his ideas for extending the system.
\ ======================================================================

[UNDEFINED] ftran [IF] 
 
[UNDEFINED] CHAR-MATCH [IF] include lib/chmatch.4th  [THEN]
[UNDEFINED] STACK      [IF] include lib/stack.4th    [THEN]
[UNDEFINED] BETWEEN    [IF] include lib/range.4th    [THEN]
[UNDEFINED] ROW        [IF] include lib/row.4th      [THEN]
[UNDEFINED] U<         [IF] include lib/ansdbl.4th   [THEN]
[UNDEFINED] IS-DIGIT   [IF] include lib/istype.4th   [THEN]
[UNDEFINED] SCAN       [IF] include lib/scanskip.4th [THEN]
[UNDEFINED] /SPLIT     [IF] include lib/split.4th    [THEN]

 
\  == Buffer Size == 
256 constant opg_size 
 
opg_size        string workspace$  
opg_size        string result$      
 
VARIABLE Parenthesis-Count 
VARIABLE Literal-State 
 
 1 CONSTANT Left-Paren 
 2 CONSTANT Right-Paren 
 8 CONSTANT Negation 
 9 CONSTANT Function-Call 
10 CONSTANT Op-Dummy 
 
\  Look up keys for parentheses 
char | constant key_bar     
char (  constant key_lparen  
char )  constant key_rparen  
 
\  Look up keys for mathmatical equations 
char +  constant  kplus 
char -  constant  kminus 
char *  constant  kmultiply 
char /  constant  kdivide 
char ^  constant  kpower 
char .  constant  kdecimal 
char ,  constant  kcomma 
char =  constant  kequal 
     0  constant  kerror 


variable math-type
: forth-math  ( -- ) 0  math-type ! ;
: standard-math ( -- )  1 math-type ! ;
: do-type  ( -- a n ) math-type @ cells  + @c  count ;

\ ===>          ==Forth-Math==     ==Standard-Math==
create 'store'     ," F!"              ," !"     does> do-type ;
create 'fetch'     ," F@"              ," @"     does> do-type ;
create 'plus'      ," F+"              ," +"     does> do-type ;
create 'minus'     ," F-"              ," -"     does> do-type ;
create 'multiply'  ," F*"              ," *"     does> do-type ;
create 'divide'    ," F/"              ," /"     does> do-type ;
create 'power'     ," F**"             ," ^"     does> do-type ;
create 'FN_delim'  ," F"               ,"  "     does> do-type ;
create 'negate'    ," FNEGATE "        ,"  "     does> do-type ;
create '$literal'  ,| s" |             ,"  "     does> do-type ;
create 'E$>float'  ,| E0" s>float|     ,"  "     does> do-type ;
create '$>float'   ,| " s>float|       ,"  "     does> do-type ;
create 'prefix'    ," Ff"              ,"  "     does> do-type ;


forth-math  \ set as default

\ ===4tH's Is-a-Number parser from Hans Bezemer=======
           s" +-" sconstant 'sign' 
   s" 0123456789" sconstant 'digits' 
         s" EeDd" sconstant 'exponent' 
           char . constant  'point' 

 : is-a-number ( a1 n1 -- a2 n2 f )
    'sign'   char-match drop
    'point'  char-equal >r
    'digits' char-match r> swap >r >r 
    'digits'   skip-while r> 0=
    if 'point' char-equal if 'digits' skip-while then then
    'exponent' char-match
    if 'sign'  char-match if 'digits' char-match r> and >r then then
    'digits' skip-while r>  ;


\  ========Is-an-Identifier===========================================
\  Is-an-Identifier          ( a1 n1 -- a2 n2 f )
\      An identifier is a letter followed by letters and digits.
\      Used in `Translate-OO and`Translate-Formula`.
\ ====================================================================
 : Is-an-Identifier  ( a1 n1 -- a2 n2 f ) 
    over c@ is-alpha >r 
    begin  dup if over c@ is-alnum else dup then 
    while  chop repeat r> ; 
 
 
\  ========Op-Stack Operations===========================================
 30 CONSTANT Op-Stack-Size 
 Op-Stack-Size 1+ array Op-Stack
 Op-Stack stack 
 : Op-Push ( n -- )  Op-Stack >a ; 
 : Op-Top  ( -- n )  Op-Stack a@ ; 
 : Op-Pop  ( -- n )  Op-Stack a> ;
 : Op-Drop  ( -- )   Op-Stack a> drop  ; 
 : Op-Stack-Depth ( -- n )  Op-Stack adepth ; 
 : Op-Stack-Clear ( -- )  Op-Stack stack ;


\  ========Application Tools==============================================  
: Callable ( a1 n1  -- a2 n2 ) 
     'FN_delim' pad place 
     'prefix' char-match drop pad +place 
     pad count ; 
 
: Translate-Operation   ( a n -- ) 
     result$ +place  s"  " result$ +place ; 
 
: Op-Store   ( a n -- ) 
    Translate-Operation 
   'store' Translate-Operation ; 
 
: Op-Fetch    ( a n -- ) 
    Translate-Operation 
   'fetch' Translate-Operation ; 
 
: Op-literal ( a n -- ) 
    2dup '$literal'  result$  +place 
    result$ +place 
    'exponent' skip-until 
    'exponent' char-match >r 2drop 
    r> if '$>float' else 'E$>float' then 
    result$ +place 
    s"  " result$ +place ; 
 

\  ========Operators=================================================
\  Op-Code                       ( a n -- a n code )
\      Pick up code for operator.  Used in `Apply-Operators`.

\  Operator-Precedence           ( code -- precedence )
\      Get the precedence of an operator.  Used in
\      `Apply-Operators`.

\  Code-Operation               ( code -- )
\      Determine what to do with the operator.  Used in
\      `Apply-Operators`.

\  Apply-Operators              ( a1 n1 -- a2 n2 )
\      Use operator precedence to select operators.
\      Used in `Translate-Operand-Operator`.
\ ===================================================================
create Op-Code 
   key_rparen , 2 , 
        kplus , 3 , 
       kminus , 4 , 
    kmultiply , 5 , 
      kdivide , 6 , 
       kpower , 7 , 
       kcomma , 0 , 
         null , 
does>
  over if
    >r over c@ r> 2 num-key row
    if cell+ @c else ." Illegal operator" abort then nip
  else drop 0
  then ;


 \ Precedence 
   -1  constant  p_BTmark   \ Bottom Mark 
    2  constant  p_comma    \ Termination or Comma 
    1  constant  p_LParen   \ Left Paren 
    1  constant  p_RParen 
    3  constant  p_Plus 
    3  constant  p_Minus 
    4  constant  p_Times 
    4  constant  p_Divide 
    5  constant  p_Power 
    3  constant  p_Negate 
    1  constant  p_FCall    \ Function-Call 
    0  Constant  p_Dummy
 
create Operator-Precedence 
     p_BTmark ,   p_comma ,   p_LParen ,    p_RParen , 
     p_Plus ,     p_Minus ,   p_Times ,     p_Divide ,
     p_Power ,    p_Negate ,  p_FCall ,     p_Dummy ,
does>                        ( n1 -- n2 ) \ code -- precedence
   swap dup -1 10 between    \ table is indexed from -1 
   if 1+ cells + @c  else 2drop TRUE ABORT" Invalid Operation" 
   then ; 

: -Parenthesis ( -- ) -1 Parenthesis-Count +! ; 
: +Parenthesis ( -- )  1 Parenthesis-Count +! ; 
: DoContinue   ( -- n )  0 ; 
: DoParenCnt ( -- n )  -Parenthesis  DoContinue ; 
: DoPlus ( -- a n )  'plus' ; 
: DoMInus ( -- a n )  'minus' ; 
: DoMultiply ( -- a n )  'multiply' ; 
: DoDivide ( -- a n )  'divide' ; 
: DoPower ( -- a n )  'power' ; 
: DoNegate ( -- a n )  'negate' ; 
: DoFunc ( -- a n )    Op-Drop Op-Top Op-Drop Op-Top -Parenthesis Callable ; 

create Code-Operation
     ' DoParenCnt ,   ' DoContinue ,   ' DoPlus ,    ' DoMinus ,
     ' DoMultiply ,   ' DoDivide ,     ' DoPower ,   ' DoNegate ,
     ' DoFunc ,
does>                        ( n -- )
   swap dup 1 9 between      \ table is indexed from 1 
   if  1- cells + @c execute else 2drop TRUE ABORT" Invalid Operator" 
   then  DUP if Translate-Operation else DROP then ; 
 
: Apply-Operators   ( a1 n1 -- a2 n2 ) 
   BEGIN Op-Code                      ( str len code ) 
      DUP 2SWAP SWAP >R >R            ( code code )  ( str len ) 
      >R Operator-Precedence >R       ( -- )  ( . . . precedence ) 
         BEGIN Op-Top Operator-Precedence R@  >= 
         WHILE Op-Top Code-Operation Op-Drop 
         REPEAT 
      R> DROP R> R> R> SWAP           ( code str len )  ( -- ) 
      DUP IF chop THEN 
      ROT 
      DUP Right-Paren = 
   WHILE DROP Op-Drop REPEAT 
   DUP if Op-Push else DROP then ; 

 
\ ========Translate Operand and Operator====================       
\  Translate-OO   ( a1 n1 -- a2 n2 )
\      Pick up an operand and an operator.  Used in
\      `Translate-Expression`.
\ ==========================================================
: Is-function  ( a1 n1 -- a2 n2)        
         Op-Dummy Op-Push 
         /split     ( a+k n-k a k)
         Op-Push Op-Push Function-Call Op-Push   ( a+k n-k) 
         +Parenthesis 
         chop ; 

: Is-variable  ( a1 n1 -- a2 n2)         
           swap >R >R R@  -  Op-Fetch  R> R> swap 
           Apply-Operators ;

: Func-left-paren? ( a1 n1 -- a2 n2 f) 
      2DUP
      Is-an-Identifier  >r r@ IF 
         DUP DUP IF DROP OVER C@ key_lparen  = THEN
         IF  Is-function  ELSE  Is-variable THEN 
      ELSE 2DROP THEN r> ;       

: Number? ( a1 n1 -- a2 n2 f)
   2DUP Is-a-Number >r  r@ IF   ( a n a+k n-k) 
      swap >R >R R@ - Op-Literal R> R> swap 
      Apply-Operators 
   ELSE 2DROP THEN r> ; 

: Left-paren?  ( a1 n1 -- a2 n2 f)
      OVER C@ key_lparen = >r   r@ IF 
        Op-Dummy Op-Push Left-Paren Op-Push 
        +Parenthesis
        chop 
      THEN  r> ;
 
: Minus?  ( a1 n1 -- a2 n2 f)
     OVER C@ kminus = >r  r@ IF 
      Negation Op-Push 
      chop 
   THEN r> ;

: Plus? ( a1 n1 -- a2 n2 f)
     OVER C@ kplus = DUP IF DROP DUP 1 > THEN >r  r@ IF 
        chop 
     THEN  r> ;

: Forth?  ( a1 n1 -- a2 n2 f)
   OVER C@ key_bar =  >r  r@ IF 
      chop 
      2DUP key_bar  SCAN /SPLIT 
      2SWAP SWAP >R >R Translate-Operation R> R> SWAP 
      DUP IF chop THEN 
      Apply-Operators 
   THEN r> ;

: Oops  ( -- )
      CR TYPE CR 
   TRUE ABORT" Illegal Operand " ; 
    

create translate? 
     ' Func-left-paren? ,    ' Number? ,   ' Left-paren? ,
     ' Minus? ,              ' Plus? ,     ' Forth? ,
     ' Oops ,
does> swap cells + @c execute ;

6 constant lastentry
: Trans-OO ( a1 n1 -- a2 n2 )
     0  begin dup  >r translate? r> swap  
        if lastentry +  then  1+  dup lastentry > 
     until drop  ; 


\ ========Translate Formula=========================================
\  Translate-Formula              ( a n -- )
\      Translate the formula.  Used in `FTRAN`.

\  Translate-Expression           ( a n -- )
\      Translate the expression. Used in `Translate-Formula`.
\ ===================================================================
: Translate-Expression   ( a n -- ) 
   BEGIN DUP WHILE 
     Trans-OO 
   REPEAT 2DROP 
   Parenthesis-Count @ ABORT" Unmatched Parens " ; 

 
: Translate-Formula  ( a n -- ) 
    0 Parenthesis-Count ! 
    Op-Stack-Clear
    2DUP Is-an-Identifier 
    DUP IF DROP DUP 
       DUP IF DROP OVER C@ kequal  = THEN 
    THEN 
    IF 
      /SPLIT Op-Push Op-Push -1 Op-Push 
      chop 
      Translate-Expression 
      Op-Top -1 = 0= ABORT" Invalid Expression " 
      Op-Drop Op-Top Op-Drop Op-Top Op-Store 
    ELSE 2DROP 
      -1 Op-Push 
      Translate-Expression 
    THEN 
     Op-Stack-Depth 0= ABORT" Invalid Formula " ; 

 
 \ ========FTRAN==================================
: remove-spaces ( a1 n1 -- a2 n2 ) 
    false Op-Push 
    0 workspace$ c! 
    0 do 
       dup i + dup >r c@      \ Embedded |4tH code| can have spaces. 
       dup key_bar = if Op-Pop 0= Op-Push then  
       bl <>  Op-Top or  if  r@ 1 workspace$ +place then 
       r> drop 
    loop drop 
    Op-Drop workspace$ count ;  


: ftran ( a1 n1 -- a2 n2 ) 
     0 result$ c! 
     remove-spaces 
     translate-formula 
     result$ count ; 
 
[DEFINED] 4TH# [IF]
  hide opg_size
  hide workspace$
  hide result$
  hide Parenthesis-Count
  hide Literal-State
  hide Left-Paren
  hide Right-Paren
  hide Negation
  hide Function-Call
  hide Op-Dummy
  hide key_bar
  hide key_rparen
  hide kplus
  hide kminus
  hide kmultiply
  hide kdivide
  hide kpower
  hide kdecimal
  hide kcomma
  hide kequal
  hide kerror
  hide math-type
  hide do-type
  hide 'store'
  hide 'fetch'
  hide 'plus'
  hide 'minus'
  hide 'multiply'
  hide 'divide'
  hide 'power'
  hide 'FN_delim'
  hide 'negate'
  hide '$literal'
  hide 'E$>float'
  hide '$>float'
  hide 'prefix'
  hide 'sign'
  hide 'digits'
  hide 'exponent'
  hide 'point'
  hide is-a-number
  hide Is-an-Identifier
  hide Op-Stack-Size
  hide Op-Stack
  hide Op-Push
  hide Op-Top
  hide Op-Pop
  hide Op-Drop
  hide Op-Stack-Depth
  hide Op-Stack-Clear
  hide Callable
  hide Translate-Operation
  hide Op-Store
  hide Op-Fetch
  hide Op-literal
  hide Op-Code
  hide p_BTmark
  hide p_comma
  hide p_LParen
  hide p_RParen
  hide p_Plus
  hide p_Minus
  hide p_Times
  hide p_Divide
  hide p_Power
  hide p_Negate
  hide p_FCall
  hide p_Dummy
  hide Operator-Precedence
  hide -Parenthesis
  hide +Parenthesis
  hide DoContinue
  hide DoParenCnt
  hide DoPlus
  hide DoMInus
  hide DoMultiply
  hide DoDivide
  hide DoPower
  hide DoNegate
  hide DoFunc
  hide Code-Operation
  hide Apply-Operators
  hide Is-function
  hide Is-variable
  hide Func-left-paren?
  hide Number?
  hide Left-paren?
  hide Minus?
  hide Plus?
  hide Forth?
  hide Oops
  hide translate?
  hide lastentry
  hide Trans-OO
  hide Translate-Expression
  hide Translate-Formula
  hide remove-spaces
[THEN] 
[THEN]
