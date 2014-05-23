\ Based on a benchmark by Christopher W. Cowell-Shah, Copyright 2004
\ 4tH version by J.L. Bezemer, Copyright 2004,2012

\                       int     I/O     Total
\ Java 1.4.2            9.3     10.1    19.4
\ Visual C#             9.7     9.9     19.6
\ gcc C                 9.8     10.0    19.8
\ Visual C++            9.6     10.5    20.1
\ Java 1.3.1            14.5    12.3    26.8
\ Python/Psyco          29.7    10.5    40.4
\ Visual Basic          9.8     30.7    40.5
\ Visual J#             9.6     35.1    44.7
\ 4tH 3.4e (GCC)        170.8   17.0    187.8
\ Python                322.4   11.9    334.3
\ 4tH 3.4c (LCC)        320.0   33.0    353.0

\ Tests performed on a Pentium4 2 GHz, Win32

[needs lib/timer.4th]

1000000    constant ioMax
1000000000 constant intMax

variable intResult


\ FILE *stream;
\ stream = fopen("C:\\TestGcc.txt", "w");
\ int i = 0;
\ while (i++ < ioMax)
\ {
\   fputs("abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefgh\n", stream);
\ }
\ fclose(stream);

\ char readLine[100];
\ stream = fopen("C:\\TestGcc.txt", "r");
\ i = 0;
\ while (i++ < ioMax)
\ {
\   fgets(readLine, 100, stream);
\ }
\ fclose(stream);

: DoIO
  s" test4th.txt" output open dup use
  0 begin
    dup ioMax <
  while
    ." abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefgh" cr
    1+
  repeat
  drop close

  s" test4th.txt" input open dup use
  0 begin
    dup ioMax <
  while
    refill drop
    1+
  repeat
  drop close

  s" test4th.txt" delete-file abort" Cannot remove 'test4th.txt'"
;

\ int intResult = 1;
\ int i = 1;
\ while (i < intMax)
\ {
\   intResult -= i++;
\   intResult += i++;
\   intResult *= i++;
\   intResult /= i++;
\ }

: DoInt
  1 dup intResult dup >r !
  begin
    dup intMax <
  while
    dup negate r@ +! 1+
    dup r@ +! 1+
    r@ @ over * r@ ! 1+
    r@ @ over / r@ ! 1+
  repeat
  r> drop drop
;

timer-reset
DoIO
." I/O benchmark: " .elapsed cr

timer-reset
DoInt
." int benchmark: " .elapsed cr

