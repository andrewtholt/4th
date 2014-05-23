\ 4tH library - Database sort - Copyright 2011 J.L. Bezemer
\ You can redistribute this file and/or modify it under
\ the terms of the GNU General Public License

[UNDEFINED] db.sort     [IF]
[UNDEFINED] db.error    [IF] include lib/dbm.4th       [THEN]
[UNDEFINED] /sort-index [IF] 4096 constant /sort-index [THEN]
                                       \ holds all valid rowids
/sort-index array  db.sorted does> swap cells + ;
          0 value  db.norows           \ number of valid rows in table
          0 value  (sort-key)          \ field to sort by
        256 string (temp-field)        \ temporary buffer for field value

[UNDEFINED] sort [IF]                  \ other sorting algorithm
defer db.sorting                       \ xt of sorting algorithm

:noname                                \ compare two rows
  >r                                   \ save array address
  cells r@ + @ db.goto db.buffer (sort-key) + count (temp-field) place
  cells r> + @ db.goto db.buffer (sort-key) + count (temp-field) count
  compare 0<                           \ get values and compare
; is precedes

:noname                                \ standard exchange word
  >r cells r@ + swap cells r> + over @ over @ swap rot ! swap !
; is exchange
[ELSE]                                 \ quicksort algorithm
' sort is db.sorting                   \ assign quicksort word

:noname                                \ compare two rows
  db.goto db.buffer (sort-key) + count (temp-field) place
  db.goto db.buffer (sort-key) + count (temp-field) count compare 0<
; is precedes                          \ get values and compare
[THEN]
                                       \ scan current table
: db.scan                              ( --)
  db.first 0                           \ setup scanning
  begin                                \ no rows scanned so far
    db.error 0=                        \ if an error occurred
  while                                \ exit right away
    db.rowid over db.sorted ! db.next 1+ /sort-index over =
  until to db.norows                   \ check whether bounds are crossed
;
                                       ( n --)
: db.sort to (sort-key) 0 db.sorted db.norows db.sorting ;
: db.sortkey (sort-key) + ;            ( n1 -- n2)

[DEFINED] 4TH# [IF]
  hide /sort-index
  hide (temp-field)
  hide (sort-key)
[THEN]
[THEN]