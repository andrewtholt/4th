\ Copyright BYTE magazine
\ (* The Sieve of Eratosthanes, compiled *) /


DECIMAL

8192   CONSTANT size
size string flags

: DO-PRIME
        flags size 1 FILL
        0 size 0
        DO      flags I + C@
                IF   I DUP +  3 +  DUP  I +
                     BEGIN      DUP size <
                     WHILE      0 OVER flags + C!
                                OVER +
                     REPEAT
                     DROP DROP 1+
             THEN
        LOOP ;

: PRIMES
        ." Going to do 25 iterations."
        0  25 0 DO DROP
                    DO-PRIME
                 LOOP
        CR .    ." primes found," ;

        CR ." Enter PRIMES to test."

                        \ (* End of Information *)
CR PRIMES CR
