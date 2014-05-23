\ (*
\  * LANGUAGE    : ANS Forth
\  * PROJECT     : Forth Environments
\  * DESCRIPTION : Test threading speed of `inner interpreter'
\  * CATEGORY    : Benchmarks
\  * AUTHOR      : Marcel Hendrix
\  * LAST CHANGE : October 5th, 1991 MHX
\  *)




\        NEEDS -miscutil
\        MARKER -thread



\                (* THREAD-TEST takes 13.35 seconds on 12.5 MHz AT *)
\                (* 50 MHz '486: 0.550 seconds                     *)

[DEFINED] 4TH# [IF]
[NEEDS lib/timer.4th]
[THEN]

\ CODE bottom gcall, END-CODE   \ 3 seconds
: bottom ;                      \ 4 seconds
: 1st   bottom bottom ;
: 2nd   1st 1st ;
: 3rd   2nd 2nd ;
: 4th   3rd 3rd ;
: 5th   4th 4th ;
: 6th   5th 5th ;
: 7th   6th 6th ;
: 8th   7th 7th ;
: 9th   8th 8th ;
: 10th  9th 9th ;
: 11th  10th 10th ;
: 12th  11th 11th ;
: 13th  12th 12th ;
: 14th  13th 13th ;
: 15th  14th 14th ;
: 16th  15th 15th ;
: 17th  16th 16th ;
: 18th  17th 17th ;
: 19th  18th 18th ;
: 20th  19th 19th ;     \ -- do 2^20 :; pairs
: 21st  20th 20th ;
: 22nd  21st 21st ;
: 23rd  22nd 22nd ;
: 24th  23rd 23rd ;
: 25th  24th 24th ;     \ -- 2^25 = 32 million pairs

: 32-MILLION    CR ." 32 million nest/unnest pairs take "
                TIMER-RESET 25th .ELAPSED
                CR ." (66 MHz '486: 9.777 seconds.)" ;

: 1-MILLION     CR ." 1 million nest/unnest pairs take "
                TIMER-RESET 20th .ELAPSED
                CR ." (66 MHz '486: 0.281 seconds.)" ;


                CR .( Enter: 1-MILLION  or  32-MILLION )

\                            (* End of Source *)
[DEFINED] 4TH# [IF]
cr cr 32-million
[THEN]

