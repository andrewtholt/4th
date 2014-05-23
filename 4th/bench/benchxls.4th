\ 4tH BENCH, XLS version - Copyright 2004,2012 J.L. Bezemer
\ You can redistribute this file and/or modify it under
\ the terms of the GNU General Public License

include lib/timer.4th
include lib/msxls2-w.4th

variable lines                         \ prime program from Forth

: test mod 0= ;
: pprint dup 5 .r lines @ dup 0= if cr drop 4 else 1- then lines ! ;
: ptest dup 2/ 2
  do dup i test
     if 0 leave then
  1 +loop
  dup if pprint else drop then drop ;
: prime cr 4 lines ! do i ptest 1 +loop cr ;

: "4tH#"
  base @ hex 4th# <# # # [char] . hold # [char] V hold bl hold
  [char] H hold [char] t hold [char] 4 hold #> rot base !
;

: chart                                \ shows all previous tests
  s" Platform"       XLStype s" OS"          XLStype s" Forth"       XLStype
  s" Compiler"       XLStype s" Cell (bits)" XLStype s" Time (secs)" XLStype XLScr
  s" Spectrum 48K"   XLStype s" ZX-BASIC"    XLStype s" Artic Forth" XLStype
  s" Z80 assembler"  XLStype 16 XLS.         3230 XLS. XLScr
  s" Sun Sp Ultra1"  XLStype s" Solaris"     XLStype s" 4tH V3.2"    XLStype
  s" GCC"            XLStype 32 XLS.         18 XLS. XLScr
  s" RS/6000 250"    XLStype s" AIX V3"      XLStype s" 4tH V3.2"    XLStype
  s" XL C V1.3"      XLStype 32 XLS.         30 XLS. XLScr
  s" P5/600"         XLStype s" DOS V5"      XLStype s" 4tH V3.3"    XLStype
  s" DJGPP V2.72"    XLStype 32 XLS.         5 XLS.  XLScr
  s" P5/600"         XLStype s" Win 3.1"     XLStype s" 4tH V3.3"    XLStype
  s" Turbo C++ V3.0" XLStype 32 XLS.         6 XLS.  XLScr
  s" P5/166"         XLStype s" DOS V5"      XLStype s" 4tH V3.2"    XLStype
  s" DJGPP V2.72"    XLStype 32 XLS.         9 XLS.  XLScr
  s" P5/166"         XLStype s" Win 3.1"     XLStype s" 4tH V3.2"    XLStype
  s" Turbo C++ V3.0" XLStype 32 XLS.         21 XLS. XLScr
  s" 486/33"         XLStype s" DOS V5"      XLStype s" 4tH V3.2"    XLStype
  s" Turbo C V2.0"   XLStype 32 XLS.         165 XLS. XLScr
  s" 486/33"         XLStype s" DOS V5"      XLStype s" 4tH V3.2"    XLStype
  s" DJGPP V2.72"    XLStype 32 XLS.         71 XLS. XLScr
  s" 486/33"         XLStype s" DOS V5"      XLStype s" FPC V3.55"   XLStype
  s" 8086 assembler" XLStype 16 XLS.         29 XLS. XLScr
  s" 486/33"         XLStype s" DOS V5"      XLStype s" PFE V09.12"  XLStype
  s" Unknown"        XLStype 32 XLS.         45 XLS. XLScr
  s" 486/33"         XLStype s" DOS V5"      XLStype s" CForth"      XLStype
  s" Turbo C V2.0"   XLStype 16 XLS.         686 XLS. XLScr
  s" 486/66"         XLStype s" DOS V5"      XLStype s" NIB Forth"   XLStype
  s" Unknown"        XLStype 16 XLS.         655 XLS. XLScr
  s" 486/66"         XLStype s" Win V3.1"    XLStype s" AtLast"      XLStype
  s" Turbo C++ V3.0" XLStype 16 XLS.         308 XLS. XLScr
  s" 486/66"         XLStype s" Win V3.1"    XLStype s" 4tH V3.2"    XLStype
  s" Turbo C++ V3.0" XLStype 32 XLS.         83 XLS. XLScr
  s" 486/66"         XLStype s" DOS V5"      XLStype s" CForth"      XLStype
  s" Turbo C V2.0"   XLStype 16 XLS.         345 XLS. XLScr
  s" 486/66"         XLStype s" DOS V5"      XLStype s" 4tH V3.2"    XLStype
  s" Turbo C V2.0"   XLStype 32 XLS.         82 XLS. XLScr
  s" THIS COMPUTER"  XLStype s" Unknown"     XLStype "4tH#"          XLStype
  s" Unknown"        XLStype /cell 8 * XLS.
;

: do-sieve                             \ execute the sieve test
  timer-reset 9999 2 prime cr          \ reset the timer and open file
  s" bench.xls"  XLSopen abort" Can't open bench.xls"
  chart .elapsed XLSclose              \ write the chart and close the file
;

' XLS. is timer-stop
do-sieve

