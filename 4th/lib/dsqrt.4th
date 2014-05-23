\ dsqrt.4th --- written by Hugh Aguilar --- copyright (c) 2009, BSD license

[UNDEFINED] dsqrt  [IF]
[UNDEFINED] um/mod [IF] include lib/mixed.4th [THEN]    

: dsqrt ( Darg -- Uroot )                           \ square root
    2dup d0= if drop exit then
    2dup d2/ 1 >r
    begin 2dup d0= 0= while d2/ d2/ r> 2* >r  repeat
    2drop r>
    begin >r                                        \ -- Darg r: -- estimate
        2dup r@ um/mod nip r@ + 1 rshift            \ -- Darg root
        dup r> - abs 2 <
    until nip nip ;                                 \ -- Darg root
[THEN]

