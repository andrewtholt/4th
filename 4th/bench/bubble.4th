.( Loading Bubble Sort benchmark...) cr

\ A classical benchmark of an O(n**2) algorithm; Bubble sort

\ Part of the programs gathered by John Hennessy for the MIPS
\ RISC project at Stanford. Translated to forth by Marty Fraeman
\ Johns Hopkins University/Applied Physics Laboratory.

include lib/anscore.4th
include lib/comus.4th
include lib/random.4th

6000 constant elements ( -- int)

elements array list

: initiate-list ( -- )
  randomize list elements cells + list do random i ! cell +loop
;

: dump-list ( -- )
  list elements cells + list do i @ . cell +loop cr
;

: verify-list ( -- )
  list elements 1- cells bounds do
    i 2@ > abort" bubble-sort: not sorted"
  cell +loop
;

: bubble ( -- )
  ." bubbling..." cr
  1 elements 1 do
    list elements i - cells bounds do
      i 2@ > if i 2@ swap i 2! then
    cell +loop 
  loop
;

: bubble-sort ( -- )
  initiate-list
  bubble
  verify-list
\  dump-list
;

bubble-sort


