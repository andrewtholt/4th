\ 4tH library - ENTER - Copyright 2003,2008 J.L. Bezemer
\ You can redistribute this file and/or modify it under
\ the terms of the GNU General Public License

[UNDEFINED] enter [IF]
: enter
  begin
    refill drop bl parse-word          ( a n)
    number error?                      ( n f)
  while                                ( n)
    drop                               ( --)
  repeat                               ( n)
;
[THEN]
