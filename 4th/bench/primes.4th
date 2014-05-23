( primes.f              Simple Prime number generator )

variable lines
5 constant wide

: ?cr lines @ = if cr 0 lines ! else 1 lines +! then ;

: ?prime        ( n1 -- f1 )
                dup 2
                do      dup i mod 0=
                        if      0= leave
                        then
                loop    ;

: .primes       ( -- )
                2 lines !
                cr 1 wide .r 3 wide .r
                512 4
                do      i ?prime
                        if i wide .r 10 ?cr
                        then
                loop   cr ;

.primes

