\ 4tH library - FLN FLOG - Copyright 2008, 2012 J.L. Bezemer
\ You can redistribute this file and/or modify it under
\ the terms of the GNU General Public License

\ In order to preserve memory, it will abort rather than to
\ include the entire floating point emulation library again.

[UNDEFINED] fln   [IF]
  [DEFINED] ZenFP [IF] [ABORT] [THEN]
[UNDEFINED] e     [IF] include lib/fpconst.4th [THEN]
[UNDEFINED] f10** [IF] include lib/fpow10.4th  [THEN]

FLOAT array epsilon
FLOAT array lbase

: >integer begin fdup 1 u>f f< while lbase f@ f* 1- repeat ;
: integer> begin fdup lbase f@ f< 0= while lbase f@ f/ 1+ repeat ;

: fraction 
  0 u>f 1 u>f f2/ frot fdup f*
  begin
    fover epsilon f@ fswap f<
  while
    fdup lbase f@ f< 0=
    if fswap frot fover f+ fswap frot lbase f@ f/ then
    fswap f2/ fswap fdup f*
  repeat fdrop fdrop
;

: (log)                                \ set epsilon to 1e-24
  lbase f! 1 u>f 12 f10** f**2 f/ epsilon f!
  fdup f0> 0= if FE.INVALID ferror ! exit then
  0 >integer integer> fraction s>f f+
;

: fln e (log) ;
: flog 10 u>f (log) ;

[DEFINED] 4TH# [IF]
hide >integer
hide integer>
hide epsilon
hide lbase
hide fraction
[THEN]
[THEN]


