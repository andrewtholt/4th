\ Lists the contents of an area in dump format ( a n --)

[UNDEFINED] dump [IF]
: dump                                 ( addr n -- )
  cr /cell 2* spaces over              \ print a ruler
  base @ 0 do i over + base @ mod /cell .r loop 2 spaces
  base @ 0 do i over + base @ mod 1 .r loop drop
                                       \ dump bytes
  0 ?do cr dup /cell 2* .r             \ print line of bytes
    base @ 0 do i over + c@ /cell .r loop 2 spaces
    base @ 0 do i over + c@            \ print same bytes in ascii again
    127 and dup 32 < if drop 46 then emit
  loop

  base @ +
  base @ +loop
  cr drop ;
[THEN]
