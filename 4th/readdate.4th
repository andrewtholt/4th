\ 4tH date showcase decoding program - Copyright 2013 J.L. Bezemer
\ You can redistribute this file and/or modify it under
\ the terms of the GNU General Public License

include lib/todate.4th                 \ for S>DATE
include lib/m3todate.4th               \ for LOG>DATE
include lib/ustodate.4th               \ for USA>DATE
include lib/chars.4th                  \ for '-'
include lib/scanskip.4th               \ for SPLIT
include lib/time.4th                   \ for JDATE
                                       \ format an ISO 8601 date
: date>s 10000 * swap 100 * + +  <# # # '-' hold # # '-' hold # # # # #> ;
                                       \ decode a date
: Date>                                ( a1 n1 -- a2 n2)
  2dup [char] , split 2nip number error?
  if                                   \ not a number, so it is a long format
    ." Maybe it's a 'normal' date?" cr \ check for 'normal' dates
    drop 2dup s>date >r over over + 2 = r> tuck 1970 = and
    if                                 \ check for 'common log' like dates
      ." No, maybe a 'common log' date?" cr
      drop drop drop 2dup log>date
      if                               \ check for Asian formatted dates
        ." No, maybe some Asian format?" cr
        drop drop drop 2dup asian>date
        if                             \ check for American dates
          ." Last attempt: maybe an American date.." cr
          drop drop drop 2dup usa>date
          if                           \ no success, so repeat the string
            ." I give up! Are you sure it is a valid date?" cr
            drop drop drop exit        \ which the user entered
          then
        then
      then
    then
  else                                 \ decode numeric dates
    dup 45000 <                        \ assume more recent dates, so
    if                                 \ this has to be an Excel serial date
      ." I think it's an Excel serial date.." cr
      xls>jday jdate 
    else                               \ this could be a 'flat' ISO 8601 date
      ." I think it's a 'flat' ISO 8601 date.." cr
      n>date
    then
  then date>s 2nip
;

: EnterDate                            ( --)
  ." Enter a date, no matter in which (standard) format. Note I have" cr
  ." a slight bias towards ISO and European dates. Furthermore I assume" cr
  ." you're using a recent date. Just in case you're entering something" cr
  ." that is open to interpretation. I don't do exotic formats like" cr
  ." POSIX, Julian or ordinal dates. Enter your date, please:" cr
  refill drop 0 parse cr Date> cr ." This is what I made out of it: " type cr
;

EnterDate