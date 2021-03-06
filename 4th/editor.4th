\ (c) 1997,2012 J.L. Bezemer - 4tH editor, portions based on:
\ (c) 1983 C.A. Thornton - Specforth editor
\ More details can be found at:
\ http://www.eforth.com.tw/academy/library/figforthguide/editor.htm

[needs lib/interprt.4th]               \ load interpret library

16             constant  tiny          \ tiny version
28             constant  small         \ small version
32             constant  medium        \ medium version
64             constant  large         \ large version
128            constant  huge          \ huge version

\ *** Define the following for your system ***

false          constant  Embedded?     \ compile for embedded version?
true           constant  Multitask?    \ compile for multitasking version?
small          constant  #scr          \ number of screens (see above)
64             constant  c/l           \ characters per line
16             constant  l/scr         \ lines per editing screen

\ *** End of customization ***

c/l  l/scr * constant  c/scr           \ size of an editing screen
#scr c/scr * constant  c/dsk           \ calculate virtual disk size

c/l   1- constant  c/l-                \ last character of line
c/scr 1- constant  c/scr-              \ last character of screen
l/scr 1- constant  l/scr-              \ last line of screen
#scr  1- constant  #scr-               \ last screen

/tib           string    temp          \ editor linebuffer
c/scr          string    WorkSpace     \ editor workspace
c/dsk 1+       string    Screens       \ virtual disk for screens

\ In this section the exceptions are defined

  1 enum #UndefName                    \ word not defined
    enum #BadVariable                  \ illegal variable
    enum #NotFound                     \ string not found
    enum #OffScreen                    \ not on current screen
    enum #NoScreen                     \ no such screen available
    enum #CannotOpen                   \ cannot open file
constant #NoFilename                   \ no filename issued
                                       \ get an argument from the prompt
: argument                             ( -- a n)
  bl parse-word dup 0=                 \ parse the filename
  if #NoFilename throw then            \ if no filename throw exception
;

Embedded? [IF]                         \ returns name of screen file
: filename                             ( -- a n)
  argn 0>                              \ check for arguments
  if 0 args else s" new.scr" then      \ get filename from argument
;
[ELSE]                                 \ returns name of screen file
aka argument filename                  ( -- a n)
[THEN]

variable scr                           \ current screen
variable r#                            \ cursor within current screen

8 constant #variables
#variables array variables

: variable?                            \ is it a valid variable?
  dup                                  ( n n)
  #variables 1- invert and             ( n f)
  if
    #BadVariable throw
  else
    cells variables +                  ( a)
  then
;

\ Here all internal commands are listed
\ and placed inside the dictionary.
\ Checking is done by the routines above.
\ Note: there are aliases!

Multitask? [IF]                        \ multitasking version
: pause_ pause ;                       \ pause command
[THEN]

: +_      + ;                          \ + command
: -_      - ;                          \ - command
: *_      * ;                          \ * command
: /_      / ;                          \ / command
: ._      . ;                          \ . command
: .r_     .r ;                         \ .r command
: drop_   drop ;                       \ drop command
: dup_    dup ;                        \ dup command
: rot_    rot ;                        \ rot command
: /mod_   /mod ;                       \ /mod command
: */_     */ ;                         \ */ command
: */mod_  */mod ;                      \ */mod command
: swap_   swap ;                       \ swap command
: over_   over ;                       \ over command
: !_      variable? ! ;                \ ! command
: +!_     variable? +! ;               \ +! command
: @_      variable? @ ;                \ @ command
: ?_      variable? ? ;                \ ? command
: mod_    mod ;                        \ mod command
: abs_    abs ;                        \ abs command
: negate_ negate ;                     \ negate command
: invert_ invert ;                     \ invert command
: min_    min ;                        \ min command
: max_    max ;                        \ max command
: or_     or ;                         \ or command
: xor_    xor ;                        \ xor command
: and_    and ;                        \ and command
: lshift_ lshift ;                     \ lshift command
: rshift_ rshift ;                     \ rshift command
: inc     1+ ;                         \ inc command
: dec     1- ;                         \ dec command
: 2*_     2* ;                         \ 2* command
: 2/_     2/ ;                         \ 2/ command
: spaces_ spaces ;                     \ spaces command
: emit_   emit ;                       \ emit command
: base!   36 min 2 max base ! ;        \ base command
: decimal_ decimal ;                   \ decimal command
: hex_  hex ;                          \ hex command
: octal_ octal ;                       \ octal command
: binary 2 base! ;                     \ binary command
: depth_ depth ;                       \ depth command
: bye quit ;                           \ quit command
: dummy ;                              \ dummy command
: space_ space ;                       \ space command
: time_ time ;                         \ time command
: cr_ cr ;                             \ cr command
: A. 0 ;                               \ variable A
: B. 1 ;                               \ variable B
: C. 2 ;                               \ variable C
: D. 3 ;                               \ variable D
: E. 4 ;                               \ variable E
: F. 5 ;                               \ variable F
: G. 6 ;                               \ variable G
: H. 7 ;                               \ variable H
: .(_ [char] ) parse type ;            \ .( command
: (_  [char] ) parse 2drop ;           \ ( command
: char_ bl parse-word drop c@ ;        \ char command
                                       \ fill an area with space
: sweep                                \ clear screens area
  0 scr !                              \ make screen 0 current
  0 Screens c/dsk chars + c!           \ terminate screen area
  Screens   c/dsk blank                \ blank screen area
  WorkSpace c/scr blank                \ blank work space
;
                                       \ calculate addres of a block
: block                                ( b -- a)
  dup 0<                               ( b f)
  over #scr- > or                      ( b f)
  if                                   \ check limits
    #NoScreen throw                    \ error if no such block
  else
    c/scr * Screens +                  \ calculate address
  then
;
                                       \ fill workspace with block
: cache                                ( n --)
  block WorkSpace c/scr cmove
;
                                       \ reload current screen
: reload scr @ cache ;                 ( --)
                                       \ perform I/O
: (io)                                 ( m a n -- h)
  rot open error?                      ( h f)
  if #CannotOpen throw                 \ issue message if error  
  else dup use                         ( h)
  then
  Screens c/dsk                        ( h a n)
;
                                       \ open file and redirect output
: (disk) filename (io) ;               ( m -- h a n)
                                       \ load screen area
: load                                 ( --)
  sweep                                \ clear screens
  input (disk)                         ( h a n)
  accept drop close                    ( --)
  reload                               \ load screen 0
;
                                       \ save a textfile
: export                               ( --)
  output argument (io)                 \ get filename and size
  -trailing c/l- + dup c/l mod -       \ save only full lines
  bounds ?do i c/l -trailing type cr c/l +loop
  close                                \ close the file
;
                                       \ save screen area
: save                                 ( --)
  output (disk)                        ( h a n)
  -trailing c/scr- + dup c/scr mod -   \ save only full screens
  type close                           ( --)
;
                                       \ calculate address of a line
: line                                 ( l -- a)
  dup l/scr- invert and                \ check within limits
  if
    #OffScreen throw                   \ error if no such line
  else
    c/l * WorkSpace +                  \ calculate address
  then
;
                                       \ display a line
: .line line c/l type ;                ( l --)
                                       \ list screen
: list                                 ( n --)
  decimal                              ( n)
  cr ." Scr # " .                      ( --)
  l/scr 0 do
    cr i 3 .r space
    i .line
  loop cr
;
                                       \ write workspace back to screen
: flush                                ( --)
  WorkSpace scr @ block c/scr cmove
;
                                       \ embedded version only
Embedded? [IF]                         \ shortcut for save & quit
: wq flush save quit ;                 ( --)
[THEN]
                                       \ flush and refill buffer
: update flush dup cache dup scr ! ;   ( n -- n)
: list_ update list ;                  ( n --)
                                       \ copy from pad to line buffer
: text> 0 parse c/l- min temp place ;  ( --)
: #text temp count ;                   ( -- a n)
                                       \ some computing words
: #locate r# @ c/l /mod ;              ( -- c l)
: #lead #locate line swap ;            ( -- a c)
: #lag #lead dup >r + c/l r> - ;       ( -- a c/l-c)
: -move line c/l cmove ;               ( a l --)
: h_ line c/l -trailing temp place ;   \ hold line in linebuffer
: e_ line c/l blank ;                  \ erase line
: m r# +! cr space #lead type [char] ^ emit #lag type #locate . drop ;
: say 0 m ;                            \ show line
: t_ dup c/l * r# ! dup h_ say ;       \ move line to buffer
: l_ scr @ list say ;                  \ list current screen
: top 0 r# ! ;                         \ move cursor to top
                                       \ spread line
: s_                                   ( l --)
  dup
  1- l/scr- 1- do
    i line i 1+ -move
  -1 +loop
  e_
;
                                       \ delete line
: d_                                   ( l --)
  dup h_ l/scr- dup rot
  do
    i 1+ line i -move
  loop
  e_
;
                                       \ replace line with linebuffer
: r_                                   ( l --)
  #text 2dup                           ( l a cnt a cnt)
  chars + swap                         ( l a a+cnt cnt)
  c/l swap -                           ( l a a+cnt n)
  blank swap                           ( a l)
  -move                                ( --)
;
                                       \ check cursor move
: screen?                              ( n -- n)
  dup r# @ +                           ( n n+r#)
  c/scr- invert and                    ( n f)
  if top #OffScreen throw then         \ restore cursor and issue error msg
;
                                       \ put and insert line
: p_ text> r_ ;                        ( l --)
: i_ dup s_ r_ ;                       ( l --)
: m_ screen? m ;                       \ save cursor move
                                       \ clear workspace and edit screen
: clear                                ( n --)
  update drop                          \ flush buffer
  l/scr 0 do i e_ loop                 \ erase all lines
;
                                       \ copy a screen
: copy                                 ( n1 n2 --)
  block swap block swap                ( a1 a2)
  c/scr cmove                          ( --)
;
                                       \ insert a new screen
: insert                               ( n --)
  dup clear                            ( n1)
  #scr- ?do                            \ move from last to scr#
    i dup 1- block                     ( n2 a1)
    swap block c/scr                   ( a1 a2 n3)
    cmove                              \ move previous screen
  -1 +loop
;
                                       \ match strings and return bool
: -text                                ( a1 n a2 -- f)
  swap dup                             ( a1 a2 n n)
  if                                   ( a1 a2 n)
    over + swap                        ( a1 a2+n a2)
    do                                 ( a1)
      dup c@ i c@ -                    ( a1 f)
      if 0= leave else char+ then      ( f | a1)
    loop                               ( a1)
  else                                 ( a1 a2 n)
    2drop 0=                           ( f)
  then
;
                                       \ match strings and return bool & cursor
: -match                               ( a1 n1 a2 n2 -- f n3)
  2>r 2dup 2r> 2swap over + swap
  do
    2dup i -text
    if >r 2drop r> - i swap - 0 tuck dup leave then
  loop
  2drop swap 0= swap
;
                                       \ find linebuffer in line
: 1line                                ( -- f)
  #lag #text                           ( a1 n1 a2 n2)
  -match r# +!
;
                                       \ find linebuffer in screen
: -find                                ( --)
  begin
    c/scr- r# @ <
    if top #NotFound throw then        \ restore cursor and issue error msg
    1line
  until
;
                                       \ delete chars left of cursor
: delete                               ( n --)
  >r #lag +
  r@ - #lag
  r@ negate
  r# +!
  #lead +
  swap cmove
  r> blank
;
                                       \ safe delete
: .delete delete say ;                 ( n --)
: w_ negate screen? negate .delete ;   ( n --)
: n_ -find say ;                       \ find next & find
: f_ text> n_ ;                        ( --)
: b_ #text nip negate m_ ;             \ backup cursor with find string
: x_ text> -find #text .delete drop ;  \ find and delete text
                                       \ delete all upto find string
: till                                 ( --)
  #lead + text>
  1line 0=
  if
    #NotFound throw
  else
    #lead + swap - .delete
  then
;
                                       \ copy text in at cursor position
: c_                                   ( --)
  text> #text                          ( a1 n1)
  #lag rot                             ( a1 a2 n2 n1)
  over min                             ( a1 a2 n2 n3)
  >r r@ r# +!                          ( a1 a2 n2)
  r@ - >r                              ( a1 a2)
  dup pad r@ cmove                     ( a1 a2)
  pad #lead +                          ( a1 a2 a3 a4+n4)
  r> cmove                             ( a1 a2)
  r> cmove say                         ( --)
;

create wordlist                        \ dictionary
  ," flush"    ' flush    ,            \ editor vocabulary
  ," list"     ' list_    ,
  ," clear"    ' clear    ,
  ," undo"     ' reload   ,
  ," delete"   ' w_       ,
  ," insert"   ' insert   ,
  ," export"   ' export   ,
  ," copy"     ' copy     ,
  ," till"     ' till     ,
  ," top"      ' top      ,
  ," b"        ' b_       ,
  ," c"        ' c_       ,
  ," d"        ' d_       ,
  ," e"        ' e_       ,
  ," f"        ' f_       ,
  ," h"        ' h_       ,
  ," i"        ' i_       ,
  ," l"        ' l_       ,
  ," m"        ' m_       ,
  ," n"        ' n_       ,
  ," p"        ' p_       ,
  ," r"        ' r_       ,
  ," s"        ' s_       ,
  ," t"        ' t_       ,
  ," w"        ' w_       ,
  ," x"        ' x_       ,
  ," +"        ' +_       ,            \ dc vocabulary
  ," th"       ' +_       ,
  ," -"        ' -_       ,
  ," *"        ' *_       ,
  ," /"        ' /_       ,
  ," quit"     ' bye      ,
  ," bye"      ' bye      ,
  ," q"        ' bye      ,
  ," ."        ' ._       ,
  ," .r"       ' .r_      ,
  ," drop"     ' drop_    ,
  ," dup"      ' dup_     ,
  ," rot"      ' rot_     ,
  ," swap"     ' swap_    ,
  ," over"     ' over_    ,
  ," A."       ' A.       ,
  ," B."       ' B.       ,
  ," C."       ' C.       ,
  ," D."       ' D.       ,
  ," E."       ' E.       ,
  ," F."       ' F.       ,
  ," G."       ' G.       ,
  ," H."       ' H.       ,
  ," !"        ' !_       ,
  ," +!"       ' +!_      ,
  ," @"        ' @_       ,
  ," ?"        ' ?_       ,
  ," base!"    ' base!    ,
  ," decimal"  ' decimal_ ,
  ," octal"    ' octal_   ,
  ," hex"      ' hex_     ,
  ," binary"   ' binary   ,
  ," .("       ' .(_      ,
  ," mod"      ' mod_     ,
  ," abs"      ' abs_     ,
  ," negate"   ' negate_  ,
  ," invert"   ' invert_  ,
  ," min"      ' min_     ,
  ," max"      ' max_     ,
  ," or"       ' or_      ,
  ," and"      ' and_     ,
  ," xor"      ' xor_     ,
  ," lshift"   ' lshift_  ,
  ," rshift"   ' rshift_  ,
  ," depth"    ' depth_   ,
  ," cells"    ' dummy    ,
  ," 1+"       ' inc      ,
  ," cell+"    ' inc      ,
  ," 1-"       ' dec      ,
  ," cell-"    ' dec      ,
  ," space"    ' space_   ,
  ," spaces"   ' spaces_  ,
  ," 2*"       ' 2*_      ,
  ," 2/"       ' 2/_      ,
  ," emit"     ' emit_    ,
  ," char"     ' char_    ,
  ," [char]"   ' char_    ,
  ," time"     ' time_    ,
  ," ("        ' (_       ,
  ," /mod"     ' /mod_    ,
  ," */"       ' */_      ,
  ," */mod"    ' */mod_   ,
  ," cr"       ' cr_      ,

Embedded? [IF]                         \ special words embedded version
  ," write"    ' save     ,
  ," wq"       ' wq       ,
[ELSE]
  ," save"     ' save     ,            \ special words standalone version
  ," load"     ' load     ,
[THEN]

Multitask? [IF]
  ," pause"    ' pause_   ,            \ special words multitasking version
[THEN]

  NULL ,

wordlist to dictionary                 \ standard 'abort' word
:noname #UndefName throw ; is NotFound \ for interpret library

\ This is the actual EDITOR program. It features only a
\ message handler and a interpretation-loop.
\ The rest is handled by library routines.

create Message
  ," Exception ignored" 
  ," Undefined name" 
  ," Bad variable" 
  ," Not found" 
  ," Off screen"
  ," No such screen"
  ," Cannot open file"
  ," No filename"
does>                                  \ show error message
  stdout use                           \ force output to screen
  swap 0 max cells + @c                ( n --)
  count type space                     \ print message
;

: HandleException
  catch dup                            \ if we have an exception
  if Message else drop then            \ show a message
;                                      \ ***************************
                                       \ INTERFACE TO C HOST PROGRAM
Embedded? [IF]                         \ ***************************
: initialize ['] load HandleException ;
[ELSE]                                 \ initialization standalone version
: initialize sweep ;                   \ clear screens area
[THEN]

: editor                               \ starts editor
  initialize                           \ initialize editor
  begin                                \ start main loop
    ." OK" cr                          \ show prompt
    refill drop                        \ get command
    ['] interpret HandleException      \ interpret command
  again
;

editor                                 \ start editor
