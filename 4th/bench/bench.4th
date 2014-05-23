( Benchmark 1 - Copyright Marcel Hendrix )

: X 30000 0 do loop ;
: XX 5  0 do X loop ;


( Benchmark 3 - Copyright Marcel Hendrix )

: N: ;
: Z 30000 0 do N: N: N: N: N: N: loop ;
: ZZ 5 0 do Z loop ;


( Benchmark 4 - Copyright Marcel Hendrix )

: W1 ;
: W2 W1 ;
: W3 W2 ;
: W4 W3 ;
: W5 W4 ;
: W6 W5 ;
: W 30000 0 do W6 loop ;
: WW 5 0 do W loop ;


( Benchmark 5 - Copyright Marcel Hendrix )

variable LOC
10 constant TEN

: NULL TEN dup LOC swap over ! @ + drop ;
: Y 30000 0 do  NULL loop ;
: YY    5 0 do Z loop ;


( Benchmark 6 - Copyright Marcel Hendrix )

8190 constant size
size string flags

: do-prime
  flags size 1 fill
  0  size 0 do flags i +
               c@ if i dup + 3 +
                     dup i +
                      begin dup size <
                      while 0 over flags + c!
                            over +
                      repeat
                      drop drop 1+
                  then
            loop ( count) drop ;

: rr 10 0 do do-prime loop ;


( Execute tests )

[needs lib/timer.4th]
[needs lib/ansfacil.4th]

: do-test cr ." *** Benchmark from FD March/April 1992, Guy Kelly *** "
          cr ." Empty  : " timer-reset XX .elapsed
          cr ." Thread : -- "
          cr ." Nest1  : " timer-reset ZZ .elapsed
          cr ." Nest2  : " timer-reset WW .elapsed
          cr ." Prims  : " timer-reset YY .elapsed
          cr ." Sieve  : " timer-reset RR .elapsed
          cr ." Loads  : -- "
          cr cr 5000 ms
;

do-test                                \ execute Marcel Hendrix tests

variable lines                         \ prime program from Forth

: test mod 0= ;
: pprint dup 5 .r lines @ dup 0= if cr drop 4 else 1- then lines ! ;
: ptest dup 2/ 2
  do dup i test
     if 0 leave then
  1 +loop
  dup if pprint else drop then drop ;
: prime cr 4 lines ! do i ptest 1 +loop cr ;

: .4th# base @ hex 4th# <# # # [char] . hold # #> type base ! ;

: chart                                \ shows all previous tests
  ." Platform      OS       Forth       Compiler       Cell    Time" cr
  ." --------      --       -----       --------       ------  ----" cr
  ." Spectrum 48K  ZX-BASIC Artic Forth Z80 assembler  16 bit 53:50 mins" cr
  ." Sun Sp Ultra1 Solaris  4tH V3.2    GCC            32 bit  0:18 mins" cr
  ." RS/6000 250   AIX V3   4tH V3.2    XL C V1.3      32 bit  0:30 mins" cr
  ." P5/600        DOS V5   4tH V3.3    DJGPP V2.72    32 bit  0:05 mins" cr
  ." P5/600        Win 3.1  4tH V3.3    Turbo C++ V3.0 32 bit  0:06 mins" cr
  ." P5/166        DOS V5   4tH V3.2    DJGPP V2.72    32 bit  0:09 mins" cr
  ." P5/166        Win 3.1  4tH V3.2    Turbo C++ V3.0 32 bit  0:21 mins" cr
  ." 486/33        DOS V5   4tH V3.2    Turbo C V2.0   32 bit  2:45 mins" cr
  ." 486/33        DOS V5   4tH V3.2    DJGPP V2.72    32 bit  1:11 mins" cr
  ." 486/33        DOS V5   FPC V3.55   8086 assembler 16 bit  0:29 mins" cr
  ." 486/33        DOS V5   PFE V09.12  Unknown        32 bit  0:45 mins" cr
  ." 486/33        DOS V5   CForth      Turbo C V2.0   16 bit 11:26 mins" cr
  ." 486/66        DOS V5   NIB Forth   Unknown        16 bit 10:55 mins" cr
  ." 486/66        Win V3.1 AtLast      Turbo C++ V3.0 16 bit  5:08 mins" cr
  ." 486/66        Win V3.1 4tH V3.2    Turbo C++ V3.0 32 bit  1:23 mins" cr
  ." 486/66        DOS V5   CForth      Turbo C V2.0   16 bit  5:45 mins" cr
  ." 486/66        DOS V5   4tH V3.2    Turbo C V2.0   32 bit  1:22 mins" cr
  ." THIS COMPUTER Unknown  4tH V" .4th# ."    Unknown        "
  /cell 8 * . ." bit  "
;

: do-sieve                             \ execute the sieve test
  timer-reset 9999 1 prime cr
  chart .elapsed cr cr
;

:noname <# # 6 base ! # decimal 58 hold # #> type ."  mins" ; is timer-stop
do-sieve


