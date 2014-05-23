\ DOC
\ (*
\ From: mentink@wronz.org.nz
\ Subject: Benchmarks
\ Date: 6 Jul 93 09:42:13 +1200
\ Lines: 35

\         Hi out there.

\ Since I am interested in embedded control forths, I am very interested in
\ collecting basic benchmarks of various forths running on various
\ platforms.

\ The simple benchmark I use ( because you can type it in quickly ) to check
\ out a forth is :

\ : INNER 1000 0 DO 34 DROP LOOP ;
\ : BENCH 1000 0 DO INNER LOOP 7 EMIT ;

\ For example executing BENCH on most PC forths ( on my 20Mhz 386 ) run's in
\ approx 5 secs.

\ EFORTH, PYGMY, QUICKFORTH etc and other direct-treaded forths fall into
\ this catorgory.

\ Other Forth's ( that will remain nameless ) have been known to run up to
\ 5 times slower than this.

\ I would be interested in hearing from people who are running forth in embedded
\ systems and letting me know the results of this simple test.

\ My embedded system ( eforth on a H8 micro 10mhz ) runs in 15 seconds.

\ N.B This is a SIMPLE benchmark to give you an idear of the basic ( NEXT and
\ stack performance ) speed of a forth system.

\ ---------------------------------------------------------------------------
\ Bernie Mentink
\ email:wronz.org.nz
\ ---------------------------------------------------------------------------
\ *)
\ ENDDOC

[DEFINED] 4TH# [IF]
[NEEDS lib/timer.4th]
:noname 10 * . ." milliseconds " cr ; is timer-stop
[THEN]

: INNER         1000 0 DO  34 DROP  LOOP ;
: BENCH         TIMER-RESET  1000 0 DO INNER LOOP  .ELAPSED ;
: BENCH*100     TIMER-RESET  100000 0 DO INNER LOOP  .ELAPSED ;

CR .( 0.136 seconds for iForth [66 Mhz 80486] )
CR .( 0.181 seconds for iForth [50 Mhz 80486] )
CR .( ForthCMP [native code / Tom Almy] on 80486/33: 0.21 seconds)
CR .( 0.240 for Penio Penev's pForth on 100 MHz R5000 [Crimson])
CR .( 0.35 for David N. William's Forth on 25 MHz 68040 [NeXT])
CR .( Mops: Mac Centris 610 20MHz 68LC040 - 0.35 sec)
CR .( 0.660 for Penio Penev's pForth on 33 MHz R3000 [Indigo])
CR .( 0.715 seconds for iForth [33 Mhz 80386] )
CR .( 0.74 for David N. William's Forth on 25 MHz 68030 [AMIGA])
CR .( Mops: Mac IIci 25Mhz 68030 - 0.75 sec)
CR .( 25 MHz 68030 Amiga 3000 : 0.80 secs)
CR .( Mach2 Forth, v2.14, on Mac IIci [25 MHz 68030] - 0.81 seconds)
CR .( 1.663 for tForth [20 MHz T8 transputer] )
CR .( 2.03 for F-PC 3.55 [33 Mhz 80386] )
CR .( 7.16 MHz 68000 Amiga 1000 : 7.06 secs)

[DEFINED] 4TH# [IF]
cr cr bench*100
[THEN]

