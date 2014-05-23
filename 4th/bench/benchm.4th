\ BENCHMARK PROGRAM FOR PFE                   duz 17:13 11/09/93
\ Modified for 4tH, hbe 11/04/05

include lib/timer.4th

\ Eratosthenes sieve (Byte-benchmark)         duz 11:38 10/07/94

8190 CONSTANT SIZE
SIZE STRING FLAGS

: DO-PRIME  FLAGS SIZE 1 FILL
            0 SIZE 0
            DO  FLAGS I + C@
                IF  I DUP + 3 + DUP I +
                    BEGIN   DUP SIZE <
                    WHILE   0 OVER FLAGS + C! OVER +
                    REPEAT  DROP DROP 1+
                THEN
            LOOP ;
: BENCHMARK 0 1000 0 DO DROP DO-PRIME LOOP
            . ." Primes " ;
\ Other Benchmarks                            duz 18:52 09/06/93

\ Most popular 1 million loops:
: SIMPLE    100000000 0 DO  LOOP ;

\ This one was discussed in comp.lang.forth:
: INNER     10000 0 DO 123456789 DROP LOOP ;
: OUTER     10000 0 DO INNER LOOP ;

\ Tests nesting speed. Recursive fibonacci function:
: FIB       DUP 1 >
            IF  DUP 1- RECURSE  SWAP 2 - RECURSE +  THEN ;

\ Running the benchmarks                      duz 12:25 04/16/95

: {{        timer-reset ;
: }}        .elapsed ;

: ALL-BENCHMARKS
            ." RUNNING 'BENCHMARK': " {{ BENCHMARK }} CR
            ." RUNNING 'SIMPLE':    " {{ SIMPLE    }} CR
            ." RUNNING 'OUTER':     " {{ OUTER     }} CR
            ." RUNNING '25 FIB':    " {{ 25 FIB .  }} CR ;

ALL-BENCHMARKS



