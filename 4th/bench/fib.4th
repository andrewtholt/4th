include lib/timer.4th

: fib1 ( n1 -- n2 )
    dup 2 < if drop 1 exit then
    dup  1- recurse 
    swap 2 - recurse  + ;

: fib2 ( n1 -- n2 )
    dup 2 < if
	drop 1
    else
	dup
	1- recurse
	swap 2 - recurse
	+
    then ;

: main	cr ." Fibonacci (optimized).. "
	timer-reset 34 fib1 . cr .elapsed 
	cr ." Fibonacci (original).. "
	timer-reset 34 fib2 . cr .elapsed ;

main
