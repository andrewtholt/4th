.( Loading Matrix Multiplication benchmark...) cr
\ NOTE: This version needs 0.5MB data space

\ A classical benchmark of an O(n**3) algorithm; Matrix Multiplication

\ Part of the programs gathered by John Hennessy for the MIPS
\ RISC project at Stanford. Translated to forth by  Marty Fraeman,
\ Johns Hopkins University/Applied Physics Laboratory.

1 cells constant cell

include lib/random.4th

: initiate-seed ( -- )  74755 seed ! ;

200 constant row-size
row-size cells constant row-byte-size

row-size row-size * constant mat-size
mat-size cells constant mat-byte-size

mat-byte-size array ima
mat-byte-size array imb
mat-byte-size array imr

: initiate-matrix ( m[row-size][row-size] -- )
  mat-byte-size bounds do
    random dup 120 / 120 * - 60 - i !
  cell +loop
;

: innerproduct ( a[row][*] b[*][column] -- int)
  0 row-size 0 do
    >r over @ over @ * r> + >r
    swap cell+ swap row-byte-size +
    r>
  loop
  >r 2drop r>
;

: main  ( -- )
  initiate-seed
  ima initiate-matrix
  imb initiate-matrix 
  imr ima mat-byte-size bounds do
    imb row-byte-size bounds do
      j i innerproduct over ! cell+ 
    cell +loop
  row-size cells +loop
  drop
;

main
