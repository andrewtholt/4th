include lib/mergsort.4th
include lib/choose.4th

:noname < ; is precedes

100000 constant /size
/size array example

: array! /size 0 do max-rand choose example i th ! loop ;
: .array /size 0 do example i th ? loop cr ;

array! example /size sort .array