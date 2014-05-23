\ 4tH library - Degrees/Radians conversion - Copyright 2011,2012 J.L. Bezemer
\ You can redistribute this file and/or modify it under
\ the terms of the GNU General Public License

[UNDEFINED] deg>rad [IF]
[UNDEFINED] pi      [IF] include lib/fpconst.4th [THEN]
: deg>rad pi f* 180 s>f f/ ;
: rad>deg 180 s>f f* pi f/ ;
[THEN]