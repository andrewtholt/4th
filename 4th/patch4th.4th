\ 4tH source patcher - Copyright 2008, 2012 J.L. Bezemer
\ You can redistribute this file and/or modify it under
\ the terms of the GNU General Public License

include lib/ncoding.4th                \ for selected structure members
include lib/scanfile.4th               \ for SCAN-FILE
include lib/argopen.4th                \ for ARG-OPEN
include lib/row.4th                    \ for ROW
include lib/startend.4th               \ for STARTS?
include lib/parsname.4th               \ for PARSE-NAME
include lib/padding.4th                \ for padding the fields
include lib/leading.4th                \ for -LEADING

\ ***
\ Data section
\ ***

256 constant #size                     \ size of array; assume all tokens used
150 constant #available                \ how many tokens are still available
 32 constant /mnemonic                 \ the size of a name_4th[] mnemonic
 12 constant /cmds_mask                \ the width of a cmds_4th.h column
 12 constant /save_marg                \ left margin of save_4th()
 19 constant /load_marg                \ left margin of load_4th()
 13 constant /name_mask                \ the width of a name_4th[] column
  5 constant #name_cols                \ the number of name_4th[] columns
char ~ constant tilde                  \ ASCII code of ~
[hex] 362 [decimal] constant version#  \ 4tH version for this script
                                       \ all comp_4th() types
0 enum _CONS_ enum _IMME_ constant _WORD_
                                       \ check for correct 4tH version
version# 4th# - [if] [abort] [then]
                                       \ structure for a word
struct
  width +field name                    \ the name of the word
   nell +field length                  \ the length of the word
     16 +field token                   \ C macro for the token
      1 +field datatype                \ datatype of the word
     32 +field fixedparm               \ any fixed parameter (e.g. constant)
   nell +field symbol                  \ number of symboltable entries
   nell +field correction              \ any allocation corrections
     16 +field delimiter               \ any delimiters (e.g. strings)
     32 +field cfunction               \ the C function of an immediate word
end-struct /word
                                       \ structure for a token
struct
    16 +field tname                    \ the name of the token
     1 +field tparm                    \ does it take any parameters
  nell +field tcode                    \ numeric value of the token
    32 +field tmnemo                   \ mnemonic of name_4th[]
end-struct /token

#size /mnemonic * string mnemonics does> swap /mnemonic * + ;
#size /word * string words does> swap /word * + ;
#size /token * string tokens does> swap /token * + ;
#size string temp                      \ string for premature read string
#size string #using                    \ string for temporary formatting
                                       \ translation table for booleans
create booleans
  ," yes" true ,
  ," no"  false ,
  NULL ,                               \ look it up straight away
does> 2 string-key row 0= abort" Bad boolean" nip nip cell+ @c ;
                                       \ translation table for datatypes
create datatypes
  ," constant"  _CONS_ ,
  ," immediate" _IMME_ ,
  ," word"      _WORD_ ,
  NULL ,                               \ look it up straight away
does> 2 string-key row 0= abort" Bad datatype" nip nip cell+ @c ;

variable #user-words                   \ number of defined words
variable #user-tokens                  \ number of defined tokens
variable #mnemonics                    \ number of defined mnemonics

\ ***
\ Generic words
\ ***
                                       ( a1 n1 a2 n2 -- a1 n1 f)
: marker? tib count -leading 2over starts? nip nip ;
: "," [char] , emit ;                  ( --)
: restore-line temp count type cr ;    ( --)
: save-line 0 parse temp place ;       ( --)
: ?number number error? abort" Bad number" ;
: .DONE ." .. done" cr ;               ( --)
: .tib 0 parse type cr ;               ( ..)
: .all begin refill while .tib repeat ;
                                       \ copies everything up to marker
: >marker                              ( a n --) 
  begin
    refill                             \ get new line
  while                                \ compare it to marker
    marker? 0=                         \ marker found?
  while                                \ if marker not found
    .tib                               \ print the line
  repeat 2drop                         \ drop marker
;

: skip>marker                          ( a n --)
  begin
    refill                             \ get new line
  while                                \ compare it to marker
    marker? 0=                         \ marker found?
  while                                \ if marker not found
  repeat 2drop                         \ drop marker
;
                                       \ inserts parameter tokens
: io-user                              ( n --)
  >r #user-tokens @ 0 ?do              \ save margin
    i tokens -> tparm c@               \ get the parameter
    if                                 \ if it is set
      j spaces                         \ write margin spaces and the token
      ." case (" i tokens -> tname count type ." ):" cr
    then
  loop .tib r> drop                    \ write line in tib
;

\ ***
\ This subsystem reads the initial definitions
\ ***
                                       \ read word from file
: read-word                            ( n -- n+1)
  >r                                   \ save index
  tilde parse tuck r@ words -> name place
  r@ words -> length n!                \ copy data to structure
  tilde parse r@ words -> token place
  tilde parse datatypes r@ words -> datatype c!
  tilde parse r@ words -> fixedparm place
  tilde parse ?number r@ words -> symbol n!
  tilde parse ?number r@ words -> correction n!
  tilde parse r@ words -> delimiter place
  tilde parse r@ words -> Cfunction place
  r> 1+                               \ increase index
;
                                      \ read a token from file
: read-token                          ( n -- n+1)
  >r                                  \ save index
  tilde parse r@ tokens -> tname place
  tilde parse booleans r@ tokens -> tparm c!
  tilde parse r@ tokens -> tmnemo place
  r> 1+                               \ increase index
;
                                      \ read tokens from file
: read-tokens                         ( h -- h)
  s" [tokens]" scan-file 0= abort" Cannot find [tokens]" 2drop
  0 begin refill while tib count -trailing nip while read-token repeat
  dup #available > abort" Too many tokens" 
  dup #user-tokens ! . ." tokens read" cr
;
                                      \ read words from file
: read-words                          ( h -- h)
  s" [words]" scan-file 0= abort" Cannot find [words]" 2drop
  0 begin refill while tib count -trailing nip while read-word repeat
  dup #user-words ! . ." words read" cr
;

\ ***
\ This subsystem patches cmds_4th.h
\ ***
                                       \ read current tokens 
: read-cmds                            ( -- n)
  0 begin                              \ start with 0
    tib count s" /* ranges */" starts? 0=
  while                                \ all tokens read
    2drop parse-name nip               \ if not an empty line
    if parse-name 2drop parse-name ?number max then
    refill 0= abort" Cannot find /* ranges */"
  repeat                               \ take the higher token
  2drop save-line                      \ save /* ranges */ line
;
                                       \ assign number to new tokens
: scan-cmds                            ( --)
  s" #define NOOP" scan-file 0= abort" Cannot find NOOP token" 2drop
  read-cmds #user-tokens @ 0 ?do 1+ dup i tokens -> tcode n! loop drop
;
                                       \ terminate cmds_4th.h properly
: cmds-lastword                        ( --)
  restore-line                         \ write saved line
  ." #define LastWord4th  " #user-tokens @ 1- tokens -> tname count type cr
  s" #define LastWord4th" scan-file 0= abort" Cannot find LastWord4th" 2drop
;                                      \ update LastWord4th
                                       \ write the user tokens
: cmds-user                            ( --)
  #user-tokens @ 0 ?do                 \ add all user tokens
    ." #define " i tokens -> tname count tuck type
    /cmds_mask swap - i tokens -> tcode n@ swap .r cr
  loop cr
;
                                       \ write new cmds_4th.h
: write-cmds                           ( --)
  s" cmds_4th.h" output open error? abort" Cannot open cmds_4th.h" dup use
  s" /* ranges */" >marker cmds-user cmds-lastword .all close
;
                                       \ open cmds_4th.txt file
: cmds_4th                             ( --)
  s" cmds_4th.txt" input open error? abort" Cannot open cmds_4th.txt"
  dup use scan-cmds dup rewind abort" Cannot rewind cmds_4th.txt"
  write-cmds close .DONE               \ write tokens and signal we're done
;

\ ***
\ This subsystem patches save_4th.c
\ ***
                                       \ write the new save_4th.c
: write-save                           ( --)
  s" save_4th.c" output open error? abort" Cannot open save_4th.c"
  dup use s" case (CALL):" >marker /save_marg io-user .all close
;                                      \ search marker and insert tokens
                                       \ open save_4th.txt file
: save_4th                             ( --)
  s" save_4th.txt" input open error? abort" Cannot open save_4th.txt"
  dup use write-save close .DONE       \ write new file and done!
;

\ ***
\ This subsystem patches load_4th.c
\ ***
                                       \ write the new save_4th.c
: write-load                           ( --)
  s" load_4th.c" output open error? abort" Cannot open load_4th.c"
  dup use s" case (CALL):" >marker /load_marg io-user .all close
;                                      \ search marker and insert tokens
                                       \ open load_4th.txt file
: load_4th                             ( --)
  s" load_4th.txt" input open error? abort" Cannot open load_4th.txt"
  dup use write-load close .DONE       \ write new file and done
;

\ ***
\ This subsystem patches name_4th.c
\ ***
                                       \ get the system defined mnemonics
: get-mnemonics                        ( -- n)
  0 >r begin                           \ reset count
    refill                             \ get a new line
  while                                \ when not end-of -file
    tib count -leading -trailing s" };" compare
  while                                \ when not end-of function()
    begin parse-name dup while r@ mnemonics place r> 1+ >r repeat
    2drop                              \ add mnemonic to the table
  repeat save-line s" ," r@ 1- mnemonics +place r> 
;                                      \ save the final mnemonic
                                       \ add the user mnemonics
: add-mnemonics                        ( n --)
  #user-tokens @ tuck 0 ?do            \ for all user mnemonics
    dup i tokens -> tmnemo count rot i + mnemonics dup >r place s" ," r> +place
  loop + #mnemonics !                  \ add them to the table
;                                      \ save total mnemonics
                                       \ format the currently printed mnemonic
: format-mnemonic                      ( n1 -- a n2)
  #name_cols mod if space else cr 2 spaces then mnemonics count
;                                      \ decide which layout for mnemonic
                                       \ write all mnemonics
: write-mnemonics                      ( --)
  #mnemonics @ 1- dup 0 ?do            \ for all but one mnemonics
    i dup format-mnemonic /name_mask .padding
  loop dup format-mnemonic 1- type cr restore-line
;                                      \ print them
                                       \ controls all mnemonics writing
: name-user                            ( --) 
  get-mnemonics add-mnemonics write-mnemonics
;                                      \ get mnemonics, add the users', write
                                       \ write the new name_4th.c
: write-name                           ( --)
  s" name_4th.c" output open error? abort" Cannot open name_4th.c" dup use
  s" char *name_4th [] = {" >marker 0 parse type name-user close
;
                                       \ open name_4th.txt file
: name_4th                             ( --)
  s" name_4th.txt" input open error? abort" Cannot open name_4th.txt"
  dup use write-name close .DONE       \ write new file and done
;

\ ***
\ This subsystem patches exec_4th.c
\ ***
                                       \ write custom I/O functions
: custom-io                            ( hp ho a n -- hp ho)
  2drop ." /* Custom I/O functions added by 'patch4th' */" cr cr .tib
  s" [vm.support]" >marker cr cr dup use
  s" /* This function is roughly equivalent with Forths <# */" skip>marker
;
                                       \ write standard I/O functions
: standard-io                          ( hp ho a n -- hp ho)
  2drop restore-line dup use
  s" /* This function is roughly equivalent with Forths <# */" >marker
;
                                       \ write the new exec_4th.c
: write-exec                           ( hp ho -- hp ho)
  s" exec_4th.c" output open error? abort" Cannot open exec_4th.c" >r r@ use
  s" #include <time.h>" >marker .tib over use
  s" [vm.include]" scan-file 0= abort" Cannot find [vm.include]" 2drop
  s" [vm.globals]" >marker dup use
  s" static jmp_buf  Thrown;" >marker .tib over use
  s" [vm.io]" >marker dup use
  s" /* This baby simply prints a single character." >marker
  save-line over use refill 0= abort" Cannot find [vm.support]"
  s" [vm.support]" marker? if standard-io else custom-io then .tib
  s" Main routine and the only external." >marker save-line
  ." User code added by 'patch4th'" cr ." */" cr cr cr over use
  s" [vm.vars]" >marker cr cr ." /*" cr restore-line dup use
  s" va_list  Vals;" >marker .tib over use
  s" [vm.extension]" >marker dup use
  s" default:" >marker save-line over use
  s" [immediate.words]" >marker restore-line dup use .all r> close
;
                                       \ open name_4th.txt file
: exec_4th                             ( --)
  s" exec_4th.txt" input open error? abort" Cannot open exec_4th.txt"
  dup use write-exec close .DONE       \ write new file and done
;

\ ***
\ token insertion subsystem
\ ***
                                       \ several formatting words
: .{ spaces ." { " ;                   \ print an aligned curly brace
: >"str" #using >r s| "| r@ place count r@ +place s| "| r> +place ;
: >str count #using place ;            \ copy string to #using
: +, s" ," #using +place ;             \ append a comma to #using
: .padded #using count rot .padding ;  \ print #using with padding
: .blurted #using count type ;         \ print #using without formatting
: .} count type ."  }," cr ;           \ finish the line
                                       \ this word prints a constant token
: .constant
  2 .{ dup words -> length n@ 0 .r "," space
  dup words -> name >"str" +, .blurted space
  dup words -> token >str +, .blurted space
  words -> fixedparm .}
;
                                       \ this word prints an immediate token
: .immediate                           ( i --)
  2 .{ dup words -> length n@ 0 .r ","
  dup words -> symbol n@ 3 .r ","
  dup words -> correction n@ 3 .r "," space
  dup words -> name >"str" +, 15 .padded
  dup words -> delimiter >str +, 7 .padded
  words -> cfunction .}
;
                                       \ this words print a simple word
: .word
  2 .{ dup words -> length n@ 0 .r "," space
  dup words -> name >"str" +, .blurted space
  words -> token .}
;
                                       \ matching methods with types
create methods
  _CONS_ , ' .constant ,
  _IMME_ , ' .immediate ,
  _WORD_ , ' .word ,
  NULL ,
does> 2 num-key row 0= abort" Bad datatype" nip cell+ @c execute ;
                                       \ get the size from the table
: get-size                             ( -- n)
  parse-name 2drop                     \ drop curly brace
  [char] , parse -leading -trailing    \ get the number
  number error? if drop max-n then 0 >in !
;                                      \ check if it is a valid number
                                       \ check if token should be included
: applicable?                          ( t l i -- i t f)
  >r r@ words -> length n@ =           ( t f)
  over r@ words -> datatype c@ = and   ( t f)
  r> -rot                              ( i t f)
;
                                       \ insert tokens at appropriate place
: insert-tokens                        ( t l i -- t l i)
  2dup 2>r width min 1+ swap do
    #user-words @ 0 ?do                \ if a word is applicable
      dup j i applicable? if methods else drop drop then
    loop                               \ apply the appropriate method (print)
  loop 2r>
;                                      \ this checks the table against value
                                       ( t l -- t l i f)
: size? get-size over over > dup >r 0= if insert-tokens then r> .tib ;
                                       \ inner loop of token detection
: next?                                ( l -- l f)
  begin max-n refill while drop size? while drop repeat nip dup max-n <>
;                                      \ drop lower count and create flag
                                       \ outer loop of token detection
: patch-tokens 1 begin next? while 1+ repeat 2drop ;
                                       \ words for patching in tokens
\ ***
\ This subsystem patches comp_4th.c
\ ***
                                       \ write the new comp_4th.c
: write-comp                           ( --) 
  s" comp_4th.c" output open error? abort" Cannot open comp_4th.c" dup use
  s" static Word4th WordList [] =  {"   >marker .tib _WORD_ patch-tokens
  s" static Const4th ConstList [] =  {" >marker .tib _CONS_ patch-tokens
  s" This list contains all immediate words." >marker save-line
  ." User code added by 'patch4th'" cr ." */" cr cr cr
  >r >r dup use r> r> .all cr cr ." /*" cr restore-line over use
  s" static Immed4th ImmedList [] = {"  >marker .tib _IMME_ patch-tokens
  over use .all close
;
                                       \ open comp_4th.txt file
: comp_4th                             ( --)
  s" comp_4th.txt" input open error? abort" Cannot open comp_4th.txt"
  dup use write-comp close .DONE       \ write new file and done
;

\ ***
\ This is the control subsystem that monitors all patching
\ ***
                                       \ main word
: patch-4th                            ( --)
  argn 2 < abort" Usage: patch4th patch-file"
  ." Opening " 1 dup args type cr input swap arg-open
  ." .. " read-tokens                  \ read tokens
  ." .. " read-words                   \ read words
  ." Processing cmds_4th.txt" cr cmds_4th
  ." Processing save_4th.txt" cr save_4th
  ." Processing load_4th.txt" cr load_4th
  ." Processing name_4th.txt" cr name_4th 
  ." Processing exec_4th.txt" cr exec_4th 
  ." Processing comp_4th.txt" cr comp_4th     
  ." Closing " 1 args type cr close    \ close file
  .DONE                                \ signal all done
;

patch-4th
