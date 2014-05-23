\ Small Basic by Herbert Schildt, 1988
\ debugged, optimized, enhanced and converted to 4tH by J.L. Bezemer, 2009-2013

include lib/istype.4th                 \ for IS-ALPHA
include lib/row.4th                    \ for ROW
include lib/enter.4th                  \ for ENTER
include lib/choose.4th                 \ for CHOOSE
include lib/stack.4th                  \ for STACK
include lib/escape.4th                 \ for S>ESCAPE
\ include lib/anstools.4th

   16 constant #for                    \ maximum nesting of FORs
   32 constant #gosub                  \ maximum nesting of GOSUBs
   64 constant #user                   \ maximum number of stack elements
  768 constant #label                  \ maximum number of labels
  256 constant #element                \ maximum number of array elements
16384 constant /program                \ maximum size of a uBASIC program
    4 constant /for                    \ maximum size of a FOR stack frame
                                       \ character constants
  8 constant /tab                      \ size of a tab
 10 constant lf                        \ ASCII of lf
  9 constant tab                       \ ASCII of tab
 13 constant <cr>                      \ ASCII of cr
  0 constant <null>                    \ ASCII of \0

      #user 1+ array dstack            \ user stack
     #gosub 1+ array gstack            \ GOSUB stack
#for /for * 1+ array fstack            \ FOR stack

#element array element                 \ single array of uBasic

variable prog                          \ pointer to current execution

96 string  token                       \ holding current token
 1 string  token_type                  \ holding current token type
 1 string  tok                         \ holding current token representation
 
/program buffer: program               \ program source buffer

26 array variables                     \ internal variables
                                       \ label structure
struct
  field: name                          \ name of label
  field: location                      \ location of label
end-struct /label
                                       \ label table
#label /label * array label_table does> swap /label * + ;
                                       \ index the label table
defer level2                           \ define level2
                                       \ ** token types **
  0 enum {NONE}                        \ undetermined
    enum {DELIMITER}                   \ is a delimiter
    enum {VARIABLE}                    \ is a variable
    enum {NUMBER}                      \ is a number
    enum {KEYWORD}                     \ is a keyword
constant {QUOTE}                       \ is a quoted string
                                       \ ** constants for commands **
  0 enum 'PRINT'                       \ PRINT
    enum 'INPUT'                       \ INPUT
    enum 'IF'                          \ IF
    enum 'THEN'                        \ THEN
    enum 'ELSE'                        \ ELSE
    enum 'ENDIF'                       \ ENDIF
    enum 'FOR'                         \ FOR
    enum 'NEXT'                        \ NEXT
    enum 'STEP'                        \ STEP
    enum 'BREAK'                       \ BREAK
    enum 'CONTINUE'                    \ CONTINUE
    enum 'WHILE'                       \ WHILE
    enum 'UNTIL'                       \ UNTIL
    enum 'TO'                          \ TO
    enum 'GOTO'                        \ GOTO
    enum 'EOS'                         \ End of statement
    enum 'EOL'                         \ End of line
    enum 'FINISHED'                    \ End of program
    enum 'GOSUB'                       \ GOSUB
    enum 'RETURN'                      \ RETURN
    enum 'REM'                         \ REM
    enum 'LET'                         \ LET
    enum 'PUSH'                        \ PUSH
    enum 'POP'                         \ POP()
    enum 'TOS'                         \ TOS()
    enum 'RND'                         \ RND()
    enum 'ABS'                         \ ABS()
    enum 'NOOP'                        \ NOOP
constant 'END'                         \ END
                                       \ ** mapping tokens to keywords **
create keyword?
  ," print"    'PRINT' ,
  ," input"    'INPUT' ,
  ," if"       'IF' ,
  ," then"     'THEN' ,
  ," else"     'ELSE' ,
  ," endif"    'ENDIF' ,
  ," goto"     'GOTO' ,
  ," for"      'FOR' ,
  ," next"     'NEXT' ,
  ," do"       'FOR' ,
  ," loop"     'NEXT' ,
  ," step"     'STEP' ,
  ," break"    'BREAK' ,
  ," continue" 'CONTINUE' ,
  ," while"    'WHILE' ,
  ," until"    'UNTIL' ,
  ," to"       'TO' ,
  ," gosub"    'GOSUB' ,
  ," return"   'RETURN' ,
  ," rem"      'REM' ,
  ," let"      'LET' ,
  ," push"     'PUSH' ,
  ," pop"      'POP' ,
  ," rnd"      'RND' ,
  ," abs"      'ABS' ,
  ," tos"      'TOS' ,
  ," stop"     'END' ,
  ," end"      'END' ,
  NULL ,
does> 2 string-key row 2nip >r r@ if cell+ @c then r> ;
                                       \ ** error constants **
  1 enum E.FINISHED                    \ program finished
    enum E.NOFOR                       \ previous FOR expected
    enum E.ASGMTEXP                    \ assignment expected
    enum E.MANYLBL                     \ too many labels
    enum E.DUPLBL                      \ duplicate label
    enum E.UDEFLBL                     \ undefined label
    enum E.BIGNUM                      \ integer out of range
    enum E.NOGOSUB                     \ previous GOSUB expected
    enum E.NESTFOR                     \ FOR nesting too deep
    enum E.NESTSUB                     \ GOSUB nesting too deep
    enum E.KEYEXP                      \ keyword expected
    enum E.MISSING                     \ unbalanced delimiters
    enum E.SYNTAX                      \ syntax error
    enum E.EXPREXP                     \ expression expected
    enum E.NOTVAR                      \ not a variable
    enum E.NOTFUNC                     \ not a function
    enum E.STEMPTY                     \ stack empty
constant E.STFULL                      \ stack full
                                       \ determine error line and position
: line#                                ( -- n1 n2)
  program 0 dup >r                     \ initialize loop
  begin
    r@ #label <                        \ are we within range?
  while
    r@ label_table -> name @           \ label entry not empty?
  while
    r@ label_table -> location @ prog @ <
  while                                \ did program stop at this line?
    drop drop                          \ drop label and location
    r@ label_table -> location @       \ get new location
    r@ label_table -> name @           \ get new label
    r> 1+ >r                           \ increment index
  repeat
  r> drop prog @ rot - swap            ( position line)
;
                                       \ ** error messages **
create .error                          ( --)
  ," System failure"
  ," OK"
  ," NEXT, CONTINUE or BREAK without FOR"
  ," Assignment expected"
  ," Too many labels"
  ," Duplicate label"
  ," Undefined label"
  ," Number too big"
  ," RETURN without GOSUB"
  ," Too many nested FOR loops"
  ," Too many nested GOSUBs"
  ," ENDIF or NEXT expected"
  ," Unbalanced delimiters"
  ," Nonsense in BASIC"
  ," Expression expected"
  ," Not a variable"
  ," Not a function"
  ," Stack empty"
  ," Stack full"
does>                                  \ format message number
  over 0 max cells + @c cr count rot dup 0>
  if 1- 36 base ! . decimal else drop then
  type ." , " line# 0 .r [char] : emit 1- . cr
;                                      \ determine line and position

: n< < ;                               \ less-than operands
: n> > ;                               \ greater-than operands
: n= = ;                               \ compare operands
: n# <> ;                              \ not equal operands
: n- - ;                               \ substract operands
: n+ + ;                               \ add operands
: n* * ;                               \ multiply operands
: n/ / ;                               \ divide operands
: n% mod ;                             \ modula operands
: n^ 0 max dup if over swap 1- 0 ?do over * loop nip else drop drop 1 then ;
                                       \ exponent operands
create arith                           \ map operators to words
  char < , ' n< ,
  char > , ' n> ,
  char = , ' n= ,
  char # , ' n# ,
  char - , ' n- ,
  char + , ' n+ ,
  char * , ' n* ,
  char / , ' n/ ,
  char % , ' n% ,
  char ^ , ' n^ ,                      \ automate operand execution
  NULL ,                               ( n1 n2 c -- n3)
does> 2 num-key row rot drop if cell+ @c execute else drop drop then ;

offset delims                          \ all delimiters
  bl c, char ; c, char , c, char + c, char - c, char < c, char > c, char / c,
  char * c, char % c, char ^ c, char = c, char ( c, char ) c, tab c, <cr>  c,
  <null> c, lf c, char # c, char : c,  \ there are 20 delimiters
                                       ( c -- f)
: isdelim 20 begin dup while over over 1- delims <> while 1- repeat nip 0<> ;
: iswhite dup dup bl = swap tab = rot <cr> = or or ;
: skipwhite prog @ begin dup c@ iswhite while char+ repeat prog ! ;
: token_type= token_type c@ = ;        ( -- f)
: tok@ tok c@ ;                        ( -- n)
: stoken token count ;                 ( -- a n)
: ctoken token c@ ;                    ( -- c)
: putback stoken negate prog +! drop ; ( --)
: copy>character token c! 0 token char+ c! tok c! 1 prog +! {DELIMITER} ;
: done? tok@ dup 'EOL' = over 'FINISHED' = rot 'EOS' = or or ;
: .number dup abs <# #s sign #> ;      ( n -- a n)

: find_eol                             ( --)
  prog @ begin dup c@ while dup c@ lf <> while char+ repeat
  dup c@ if char+ then prog !
;
                                       \ using the FOR and GOSUB stacks
: fpush                                ( tar loc step var --)
  fstack adepth #for /for * <          \ stack within range?
  if /for 0 do fstack >a loop else E.NESTFOR throw then
;

: fpop                                 ( -- tar loc step var)
  fstack adepth 0>                     \ stack within range?
  if /for 0 do fstack a> loop else E.NOFOR throw then
;
                                       ( n --)
: gpush gstack adepth #gosub < if gstack >a else E.NESTSUB throw then ;
: gpop  gstack adepth 0> if gstack a> else E.NOGOSUB throw then ;
                                       \ main parser routines
: copy>delimiter                       ( --)
  0 token prog @                       \ setup pointers and terminator
  begin                                \ start scanning
    dup c@ isdelim 0=                  \ stop when a delimiter is found
  while                                \ if not, copy and increment pointers
    over over c@ swap c! char+ swap char+ swap
  repeat prog ! c!                     \ save values, terminate token
;

: ="                                   \ quoted string routine
  0 token prog 1 over +! @             \ setup pointers and terminator
  begin                                \ skip the first quote
    dup c@ dup [char] " <>             \ stop when a quote is found
  while
    lf = if E.MISSING throw then       \ error when EOL is found
    over over c@ swap c!               \ if not, copy character
    char+ swap char+ swap              \ and increment pointers
  repeat                               \ get next character
  drop char+ prog ! c! {QUOTE}         \ skip final quote, terminate token
;                                      \ and signal the type of token found
                                       ( -- n)
: =:  'EOS' [char] : copy>character ;
: =lf 'EOL' lf copy>character ;
: =null 0 token c! 'FINISHED' tok c! {DELIMITER} ;
: =delim 0 token prog @ c@ over c! char+ c! 1 prog +! {DELIMITER} ;
: =digit copy>delimiter {NUMBER} ;     ( -- n)
: =array copy>delimiter {VARIABLE} ;   ( -- n) 

create bnf                             \ translate chars to parser actions
  0 , ' =null , lf , ' =lf , char : , ' =: ,  char + , ' =delim ,
  char - , ' =delim ,   char * , ' =delim ,   char ^ , ' =delim ,
  char / , ' =delim ,   char % , ' =delim ,   char = , ' =delim ,
  char ; , ' =delim ,   char ( , ' =delim ,   char ) , ' =delim ,
  char , , ' =delim ,   char > , ' =delim ,   char < , ' =delim ,
  char # , ' =delim ,   char " , ' ="     ,   char 0 , ' =digit ,
  char 1 , ' =digit ,   char 2 , ' =digit ,   char 3 , ' =digit ,
  char 4 , ' =digit ,   char 5 , ' =digit ,   char 6 , ' =digit ,
  char 7 , ' =digit ,   char 8 , ' =digit ,   char 9 , ' =digit ,
  char @ , ' =array ,   NULL ,
does> 2 num-key row if cell+ @c execute else drop {NONE} then ;

: get_token                            ( --)
  'NOOP' tok c! skipwhite              \ skip all leading white space
  prog @ c@ bnf dup {NONE} =           \ not found in the table above?
  if                                   \ if so,
    swap is-alpha                      \ is it an alpha character?
    if                                 \ if so,
      drop copy>delimiter              \ copy all upto the delimiter
      stoken keyword?                  \ see if it is a keyword or var
      if tok c! {KEYWORD} else drop {VARIABLE} then
    else                               \ is it a variable or command
      0 token c!                       \ terminate whatever is in the token
    then
  else                                 \ if found in the table
    nip                                \ drop the character
  then token_type c!                   \ update the token_type
;

: ctoken> get_token ctoken ;           ( -- c)
: get_exp 0 ctoken> if level2 putback else E.EXPREXP throw then ;
                                       ( -- n)
: exec_function                        ( xt -- n2)
  ctoken> [char] ( = {DELIMITER} token_type= and
  if execute ctoken> [char] ) = {DELIMITER} token_type= and if exit then then
  E.MISSING throw
;
                                       \ function list
: (pop) dstack adepth 0> if dstack a> else E.STEMPTY throw then ;
: (tos) dstack adepth 0> if dstack a@ else E.STEMPTY throw then ;
: (random) get_exp choose ;            ( -- n)
: (abs) get_exp abs ;                  ( -- n)

: (array)                              ( -- v)
  get_exp dup -1 > over #element < and
  if cells element + else E.NOTVAR throw then
;                                      \ check if in bounds

create function?                       ( a1 n1 -- n)
  ," @"   ' (array) ,                  \ array index
  ," rnd" ' (random) ,                 \ random value
  ," abs" ' (abs) ,                    \ absolute value
  ," tos" ' (tos) ,                    \ get top of stack
  ," pop" ' (pop) ,                    \ pop value from stack
  NULL ,
does>
  2 string-key row 2nip if cell+ @c exec_function else E.NOTFUNC throw then
;

: get_var                              ( a n -- v)
  1 = if                               \ if it is a single character
    c@ dup is-alpha                    \ if it is alphabetic
    if bl or [char] a - cells variables + exit
    else [char] @ = if stoken function? exit then
    then                               \ either an array or variable
  then
  E.NOTVAR throw                       \ otherwise it is not a variable
;
                                       ( a1 n1 -- n2)
: skip_var get_token {VARIABLE} token_type= 0= if putback then ;
: var= stoken get_var ctoken> [char] = = ;
: get_step tok@ 'STEP' = if drop get_exp else putback then ;
: assignment get_token var= if get_exp swap ! else E.ASGMTEXP throw then ;
: label_init #label 0 ?do 0 i label_table -> name ! loop ;
                                       \ skip until a matching NEXT
: skip_next                            ( --)
  1 begin                              \ initialize level 1
    get_token tok@ >r                  \ get next token
    r@ 'FINISHED' = if E.KEYEXP throw then
    r@ 'REM' = if find_eol then        \ skip any comments
    r@ 'FOR'  = if 1+ then             \ if FOR, increment level
    r> 'NEXT' = if 1- then dup 0=      \ matching NEXT found?
  until drop skip_var                  \ skip any variable
;
                                       \ skip until a matching ENDIF or ELSE
: skip_endif                           ( --)
  1 begin                              \ initialize level 1
    get_token tok@ >r                  \ get next token
    r@ 'FINISHED' = if E.KEYEXP throw then
    r@ 'REM' = if find_eol then        \ skip any comments
    r@ 'IF'  = if 1+ then              \ if IF, increment level
    r@ 'ELSE' = over 1 = and if 1- then
    r> 'ENDIF' = if 1- then dup 0=     \ matching ELSE or ENDIF found?
  until drop
;

: get_next_label                       ( n1 -- n2)
  >r 0                                 \ setup counter, save string
  begin
     dup dup #label <                  \ table full?
  while                                \ entry empty?
     drop dup label_table -> name @ dup 
  while                                \ label already defined?
     r@ = if E.DUPLBL throw then 1+
  repeat
  drop r> drop                         \ cleanup
  dup #label = if E.MANYLBL throw then 
;                                      \ table full, exit

: scan_labels                          ( --)
  label_init prog @                    \ save prog and init labels
  begin                                \ see if the next token is a number
    get_token {NUMBER} token_type=
    if                                 \ if so, add it to the label table
      stoken number dup get_next_label dup >r
      label_table -> name ! prog @ r>
      label_table -> location !
    then                               \ we don't need the rest of the line
    tok@ dup 'EOL' <> if find_eol then
    'FINISHED' =                       \ are we finished yet?
  until prog !                         \ if so, restore prog
;

: find_label                           ( n -- a)
  >r 0 begin                           \ setup counter, save string
    dup #label <                       \ within range?
  while                                \ compare labels
    dup label_table -> name @ r@ <>    \ get the name of the label
  while                                \ if found, exit loop
    1+                                 \ next entry
  repeat r> drop                       \ discard the string
  dup #label < if label_table -> location @ else E.UDEFLBL throw then
;                                      \ beyond range: signal label not found

: exec_print                           ( --)
  0 true begin                         \ setup len and delimiter flag
    get_token done? 0=                 \ if we're not finished
  while                                \ single PRINT always prints CR
    drop {QUOTE} token_type=           \ it is a quoted string?
    if stoken s>escape else putback get_exp .number then tuck type +
    ctoken> >r r@ [char] , =
    if                                 \ are we dealing with a comma?
      /tab over over mod - dup spaces +
    else                               \ calculate and issue the spaces
      r@ [char] ; = done? or 0= if E.SYNTAX throw then
    then                               \ trailing chars means syntax error
    r@ [char] , <> r> [char] ; <> and dup 
  until                                \ no ; or , there is more coming
                                       \ issue a linefeed if needed
  done? if if cr then else E.SYNTAX throw then drop
;                                      \ trailing chars means syntax error

: exec_if                              ( --)
  get_exp 0= get_token tok@ 'THEN' <> if putback then
  if get_token done? if skip_endif else find_eol then then
;                                      \ check for THEN

: exec_for                             ( --)
  get_token {VARIABLE} token_type=     \ FOR x= form?
  if                                   \ at least an initialization
    var= if                            ( v f -- v)
      get_exp over !                   \ get value and save in variable
      get_token tok@ 'TO' =            \ get the TO keyword, if found
      if                               \ abort if no iterations left
        get_exp get_token 1 get_step >r over @ over r@ 0< if swap then >
        if r> drop drop drop skip_next exit then
      else                             \ TO missing? Only initialize variable
        0 get_step dup >r 0< if (error) else max-n then
      then prog @ rot r>               \ STEP keyword used?
    else                               \ if so, accept any value else assume 0
      E.ASGMTEXP throw                 \ no assignment found, throw error
    then
  else                                 \ no init, probably a DO
    putback 0 prog @ (error) false     \ create fake FOR stack frame:
  then swap fpush                      \ dummy location FALSE-flag DO-flag
;                                      \ push the FOR frame

: exec_next                            ( --)
  fpop dup 0<                          \ fake FOR frame (DO)?
  if                                   \ if so, don't waste any time
    >r dup >r                          \ set up for next iteration
  else                                 \ if true FOR frame, increment variable
    over over +! >r >r over r'@ @ r@ 0< if swap then <
  then                                 \ compare value and limit  

  if                                   \ if loop ended, drop frame
    r> r> drop drop drop drop skip_var \ and ignore any variable
  else                                 \ if not, jump back
    dup prog ! r> r> fpush             \ and push frame again
  then
;

: exec_input                           ( --)
  get_token {QUOTE} token_type=        \ keyword followed by string?
  if                                   \ if so, type it and get variable
    stoken type ctoken> dup [char] , = swap [char] ; = or
    if get_token else E.SYNTAX throw then
  else                                 \ no separator, then syntax error
    ." ? "                             \ print only a question mark
  then enter stoken get_var !          \ get value, store it in the variable
;

: exec_push                            ( --)
  begin                                \ get expression, push it on the stack
    get_exp dstack adepth #user < if dstack >a else E.STFULL throw then
    ctoken> [char] , <>                \ repeat when a comma is found
  until done? 0= if E.SYNTAX throw then
;                                      \ trailing chars means syntax error
                                       ( --)
: exec_goto get_exp find_label prog ! ;
: exec_gosub get_exp find_label prog dup @ gpush ! ;
: exec_return gpop prog ! ;            \ return from GOSUB
: exec_break fpop /for 0 do drop loop skip_next ;
: exec_while get_exp 0= if exec_break then ;
: exec_until get_exp if exec_break then ;
: bye E.FINISHED throw ;               ( --)
: unary [char] - = if negate then ;    ( n1 c -- n2)
: number? number error? if E.BIGNUM throw then ;
: variable? get_var @ ;
                                       \ resolve a primitive
create primitive                       ( a1 n1 n2 -- n3)
  {VARIABLE} , ' variable? ,
  {KEYWORD}  , ' function? ,           \ it can only be a function
  {NUMBER}   , ' number?   ,
  NULL ,
does>
  2 num-key row if nip cell+ @c execute get_token else E.SYNTAX throw then
;
                                       ( n1 -- n2)
: level7                               \ parenthesis found?
  {DELIMITER} token_type= ctoken [char] ( = and
  if                                   \ evaluate and get next parenthesis
    get_token level2 ctoken [char] ) =
    if get_token else E.MISSING throw then
  else                                 \ error if no parenthesis found
    drop stoken token_type c@ primitive
  then                                 \ must be a primitive
;
                                       \ resolve unary -
: level6                               ( n1 -- n2)
  {DELIMITER} token_type= ctoken dup [char] + = swap [char] - = or and
  if ctoken get_token else 0 then >r level7 r> dup if unary else drop then
;                                      \ resolve power
                                       ( n1 -- n2)
: level5 level6 ctoken [char] ^ = if get_token 0 level5 [char] ^ arith then ;
                                       \ resolve div, mul and mod
: level4                               ( n1 -- n2)
  level5 0 begin                       \ setup loop
    ctoken dup [char] * = over [char] / = or over [char] % = or
  while                                \ repeat until all word done
    >r get_token level5 tuck r> arith swap
  repeat drop drop                     \ drop operator and 'hold' value
;
                                       \ resolve addition and substraction
: level3                               ( n1 -- n2)
  level4 0 begin                       \ setup loop
    ctoken dup [char] + = over [char] - = or
  while                                \ repeat until all word done
    >r get_token level4 tuck r> arith swap
  repeat drop drop                     \ drop operator and 'hold' value
;
                                       \ resolve logical operators
:noname                                ( n1 -- n2)
  level3 0 begin                       \ setup loop
    ctoken dup [char] # = over [char] = = or
    over [char] < = or over [char] > = or
  while                                \ repeat until all word done
    >r get_token level3 tuck r> arith swap
  repeat drop drop                     \ drop operator and 'hold' value
; is level2                            \ we've finally defined it!
                                       \ map tokens to words
: load_program                         ( a1 n1 a2 n2 --)
  input open error? abort" File loading error"
  >r r@ use 2dup accept r> close       \ signal loading error
  tuck = abort" Out of memory" >string \ signal memory full
;

create keyword
  'PRINT'    , ' exec_print ,
  'GOTO'     , ' exec_goto ,
  'IF'       , ' exec_if ,
  'FOR'      , ' exec_for ,
  'NEXT'     , ' exec_next ,
  'CONTINUE' , ' exec_next ,
  'BREAK'    , ' exec_break ,
  'WHILE'    , ' exec_while ,
  'UNTIL'    , ' exec_until ,
  'INPUT'    , ' exec_input ,
  'GOSUB'    , ' exec_gosub ,
  'RETURN'   , ' exec_return ,
  'PUSH'     , ' exec_push ,
  'ELSE'     , ' skip_endif ,
  'REM'      , ' find_eol ,
  'LET'      , ' assignment ,
  'END'      , ' bye ,
  'FINISHED' , ' bye ,
  NULL ,                               \ match keyword with word
does> 2 num-key row if nip cell+ @c execute else drop drop then ;
                                       \ if not listed, ignore
: interpret                            ( --)
  get_token {VARIABLE} token_type=     \ if it's a variable, assign it
  if putback assignment else tok@ keyword then
;                                      \ else assume it is a keyword

: ubasic                               ( --)
  argn 2 < abort" Usage: ubasic source-file" randomize
  program /program 1 args load_program \ load program, init stacks
  dstack stack gstack stack fstack stack
  program prog ! ['] scan_labels catch dup 0=
  if begin drop ['] interpret catch dup until then .error
;                                      \ enter interpretation loop

ubasic
