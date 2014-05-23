\ 0: Initial release 11/07/2002, Brad Eckert
\ 1: Made 4tH version, Hans Bezemer
\ 2: Converted to real FP constants

[UNDEFINED] PI [IF]
[UNDEFINED] S>FLOAT [IF] [ABORT] [THEN]
[UNDEFINED] ZenFP   [IF] fclear  [THEN]
FLOAT array PI s" 3.1415926535897932384626433832795" s>float PI f! DOES> f@ ;
FLOAT array E  s" 2.7182818284590452353602874713527" s>float E  f! DOES> f@ ;
[THEN]