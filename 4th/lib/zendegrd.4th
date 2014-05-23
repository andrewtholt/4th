\ 4tH library - Degrees/Radians conversion - Copyright 2011,2012 J.L. Bezemer
\ You can redistribute this file and/or modify it under
\ the terms of the GNU General Public License

[UNDEFINED] deg>rad [IF]
[UNDEFINED] ZenFP [IF] [ABORT] [THEN]  \ ONLY works with Zen FP library
: deg>rad 1745329251 -11 f* ;
: rad>deg 572957795 -7 f* ;
[THEN]