\ 4tH binary to .h file converter - Copyright 2007 J.L. Bezemer
\ You can redistribute this file and/or modify it under
\ the terms of the GNU General Public License

\ This file is geared toward the conversion of 4tH HX bytecode.
\ In order to convert other binary files, just change 'unit' to 'char'.
s" static unit " sconstant header      \ declaration header

include lib/argopen.4th                \ use ARG-OPEN word
include lib/ulcase.4th                 \ case conversion

     9 constant /line                  \ number of bytes per line
char ' constant quote                  \ single quote character
char , constant colon                  \ single colon character

/line string line                      \ input buffer

: .char ." '\x" <# # # #> s>lower type quote emit ;
: .char, .char colon emit space ;      ( n --)
: ?c@ dup if 1- chars + c@ else 2drop 0 then ;
: ?char if ?c@ .char else 2drop then ; ( a n f --)
: .header header type 1 args type ."  [] = {" cr ;
: .footer ." };" cr ;                  ( --)
: ?bounds space space over 0<> and if 1- then bounds ;
: read over over accept tuck <> ;      ( a n1 -- a n2 f)
: .line >r 2dup r@ ?bounds ?do i c@ .char, loop r@ ?char cr r> ;
: .lines hex begin line /line read .line until ;
: Usage argn 4 < abort" Usage: bin2h variable file h-file" ;
: OpenFiles Usage input 2 arg-open output 3 arg-open ;
: Convert Openfiles .header .lines .footer close close ;

Convert
