\ 4tH library - WILDCARD - Copyright 2006,2012 J.L. Bezemer
\ You can redistribute this file and/or modify it under
\ the terms of the GNU General Public License

\ /* Written by Jack Handy - jakkhandy@hotmail.com */
\ int wildcmp (const char *wild, const char *string) {
\   const char *cp = NULL, *mp = NULL;

\   while ((*string) && (*wild != '*')) {
\      if ((*wild != *string) && (*wild != '?')) return 0;
\      wild++; string++;
\   }

\   while (*string) {
\     if (*wild == '*') {
\       if (!*++wild) return 1;
\       mp = wild; cp = string + 1;
\     } else if ((*wild == *string) || (*wild == '?')) {
\       wild++; string++;
\     } else { wild = mp; string = cp++; }
\   }

\   while (*wild == '*') wild++;

\   return !*wild;
\ }

\ Typical use: s" bl?h.*g" s" blah.jpg" wild-match

[UNDEFINED] 2OVER [IF]
include lib/anscore.4th
[THEN]

[UNDEFINED] WILD-MATCH [IF]
[UNDEFINED] '?'        [IF] include lib/chars.4th [THEN]

: s@ 0> if c@ else drop -1 then ;      ( a n -- c)
: 4drop 2drop 2drop ;                  ( a b c d --)
: 4dup 2over 2over ;                   ( a b c d -- a b c d a b c d)
: 2s@ 4dup s@ -rot s@ ;                ( a1 n1 a2 n2 -- a1 n1 a2 n2 c1 c2)
: w@ 2over s@ ;                        ( a n -- c)
: (2chop) chop 2swap ;                 ( a1 n1 a2 n2 -- a2+1 n2-1 a1 n1)
: 2chop (2chop) (2chop) ;              ( a1 n1 a2 n2 -- a1+1 n1-1 a2+1 n2-1)
                                       \ returns true on match, false when not
: wild-match                           ( a1 n1 a2 n2 -- f)
  begin                                ( a1 n1 a2 n2)
    dup 0<> >r w@ '*' <> r> and        ( a1 n1 a2 n2 f)
  while                                ( a1 n1 a2 n2)
    2s@ <> if w@ '?' <> if 4drop false exit then then 2chop 
  repeat 4dup 2>r 2>r                  ( a1+y n1-y a2+x n2-x)
  
  begin                                ( a1 n1 a2 n2)
    dup                                ( a1 n1 a2 n2 f)
  while                                ( a1 n1 a2 n2)
    w@ '*' = if                        ( a1 n1 a2 n2 f)
      2>r chop dup 2r> rot 0=          ( a1+1 n1-1 a2 n2)
      if 2r> 2r> 4drop 4drop true exit then
      4dup chop 2r> 2r> 4drop 2>r 2>r  ( a1+1 n1-1 a2 n2)
    else                               ( a1 n1 a2 n2)
      2s@ = >r w@ '?' = r> or          ( a1 n1 a2 n2 f)
      if 2chop else 4drop 2r> 2r> 2dup chop 2>r 2over 2>r then
    then                               ( a1 n1 a2 n2)
  repeat 2r> 2r> 4drop 2drop           ( a1 n1)
                                       ( f)
  begin 2dup s@ '*' = while chop repeat nip 0=
;

[DEFINED] 4TH# [IF]
  hide 2chop
  hide (2chop)
  hide w@
  hide 2s@
  hide 4dup
  hide 4drop
  hide s@
[THEN]
[THEN]
