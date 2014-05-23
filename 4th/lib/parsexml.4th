\ 4tH library - PARSE XML - Copyright 2011,2014 J.L. Bezemer
\ You can redistribute this file and/or modify it under
\ the terms of the GNU General Public License

[UNDEFINED] skip-tag [IF]
[UNDEFINED] COMPARE [IF]
[NEEDS lib/compare.4th]
[THEN]

[UNDEFINED] 2OVER [IF]
[NEEDS lib/anscore.4th]
[THEN]

[UNDEFINED] '>' [IF]
[NEEDS lib/chars.4th]
[THEN]
                                       \ this doesn't do an automatic REFILL
: parse-tag                            ( -- a n)
  bl omit >in @ >r '>' parse dup
  if over c@ '<' =                     \ only adjust >IN if not end of buffer
    if 1+ else 2drop r@ >in ! '<' parse 2dup chars + c@ if -1 >in +! then then
  then r> drop
;                                      \ parse a tag, get next line if needed
                                       ( -- a n)
: next-tag begin parse-tag dup if exit then refill while 2drop repeat ;
                                       \ check for a tag
: check-tag                            ( a n --)
  next-tag 2dup 2>r compare
  if cout stdout use 2r> type ."  not expected here" cr use else 2r> 2drop then
;
                                       \ find a tag
: search-tag                           ( a n --)
  begin next-tag dup while 2over 2over compare while 2drop repeat 2drop 2drop
;
                                       \ check whether a tag is there
: expect-tag next-tag compare 0= ;     ( a n -- f)
: skip-tag next-tag 2drop ;            ( --)
[THEN]                                 \ skip a tag
