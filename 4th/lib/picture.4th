\ PICTURE -- Albert Nijhof -- oct2006
\ 4tH version -- J.L. Bezemer -- dec2006

[UNDEFINED] PICTURE [IF]
[UNDEFINED] '?'     [IF] include lib/chars.4th [THEN]

: picture ( n1 a1 n2 -- a3 n4 )
  swap >r >r dup abs <#
  begin
    r> dup
  while
    1- dup chars r@ + c@ swap >r '#' over =
    if drop # else '?' over = if drop #s else hold then then 
  repeat r> 2drop
  sign #>
;

\ Some examples:
\ ==============
\ 12345678 S" fl. ?.##" PICTURE TYPE cr     ( fl. 123456.78)
\ 12345678 S" C#-##"    PICTURE TYPE cr     ( C6-78)
\ 12345678 S" #####"    PICTURE TYPE cr     ( 45678)
\ 12345678 S" F#.#.#.#" PICTURE TYPE cr     ( F5.6.7.8)
\ 12345678 S" ##/##/##" PICTURE TYPE cr     ( 34/56/78)
\ 12345678 S" ? # #"    PICTURE TYPE cr     ( 123456 7 8) 
\ 12345678 S" -#+"      PICTURE TYPE cr     ( -8+) 
\ 12345678 S" ##,# km"  PICTURE TYPE cr     ( 67,8 km) 
\ 12345678 S" DM ?.##"  PICTURE TYPE cr     ( DM 123456.78)
\ depth . cr
[THEN]
