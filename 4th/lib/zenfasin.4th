\ 4tH library - FASIN FACOS FATAN ZEN - Copyright 2009,2012 J.L. Bezemer
\ You can redistribute this file and/or modify it under
\ the terms of the GNU General Public License

[UNDEFINED] fasin   [IF]
[UNDEFINED] +taylor [IF] include lib/zentaylr.4th [THEN]
[UNDEFINED] fsqrt   [IF] include lib/zenfsqrt.4th [THEN]

: 2degrees 1+ 1+ dup >r -taylor r> 1+ 1+ dup >r +taylor r> ;
: (taylor) 1 2degrees 2degrees 2degrees 2degrees 2degrees drop 2drop 2drop ;
: (fatan) 2dup >taylor (taylor) ;
: dom2 1 s>f 2over 2dup f* 2over f+ fsqrt f+ f/ (fatan) 2dup f+ ;
: dom3 1 s>f 2swap f/ 1570796325 -9 2over f0< if fnegate then 2swap dom2 f- ;
: dom2|3 1 s>f 2over fabs f< if dom3 else dom2 then ;
: fatan 25 -2 2over fabs f< if dom2|3 else (fatan) then ;
: (fasin) 1 s>f 2over 2dup f* 2over 2swap f- fsqrt f+ f/ fatan 2dup f+ ;
: fasin 2dup fabs 1 s>f f= if 1570796325 -9 f* else (fasin) then ;
: facos fasin 1570796325 -9 2swap f- ;

[DEFINED] 4TH# [IF]
  hide 2degrees
  hide (taylor)
  hide (fatan)
  hide (fasin)
  hide dom2|3
  hide dom2
  hide dom3
[THEN]
[THEN]
