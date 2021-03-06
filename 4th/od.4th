\ Copyright 1995,2005 J.L. Bezemer
\ You can redistribute this file and/or modify it under
\ the terms of the GNU General Public License

include lib/argopen.4th
include lib/dump.4th

128 constant /buffer
/buffer string buffer

: OctalDump
  argn 1- 0= abort" No file specified"
  input 1 arg-open >r
  over negate dump_offset ! hex
  begin
    r@ use
    over over swap erase
    over over accept
  while
    over over dump cr
    stdin use
    dup dump_offset +!
    ." Press <Enter> to continue"
    refill drop
  repeat
  r> close drop drop
;

buffer /buffer OctalDump
  
