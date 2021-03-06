\ 4tH library - STRING STACK - Copyright 2011,2013 J.L. Bezemer
\ You can redistribute this file and/or modify it under
\ the terms of the GNU General Public License

[UNDEFINED] s@ [IF]
  0 enum CSE.NOERRS                    \ No errors
    enum CSE.FULL                      \ Stack full
constant CSE.EMPTY                     \ Stack empty

[UNDEFINED] /cstack [IF]
  8192 constant /cstack                \ size of cstack
[THEN]

/cstack buffer: cstack                 \ allocate cstack buffer

          cstack constant cs0          \ low memory cstack
cstack /cstack + constant cs^          \ high memory cstack

[UNDEFINED] 4TH# [IF]
  CSE.NOERRS value s.error             \ error variable
         cs^ value csp                 \ cstack pointer
[THEN]
                                       ( --)
: s.clear CSE.NOERRS to s.error cs^ to csp ;

: >s                                   ( a n --)
  csp over 1+ - dup cs0 < 
  if drop 2drop CSE.FULL to s.error else dup to csp place then
;
                                       ( -- a n)
: s> 
  csp dup cs^ < if count 2dup 1+ + to csp else 0 CSE.EMPTY to s.error then
;

: s@ s> over to csp ;                  ( -- a n)
: s.free csp cs0 - ;                   ( -- n)
: s.used cs^ csp - ;                   ( -- n)

[DEFINED] 4TH# [IF]
  hide cstack
  hide /cstack
  hide cs0
  hide cs^
  hide csp
[THEN]
[THEN]