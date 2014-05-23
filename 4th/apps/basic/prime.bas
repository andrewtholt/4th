    PRINT "All primes from 1 to 500" : PRINT
    FOR x=1 TO 500
    y = 1
100 y=y+1 : z=x%y
    IF (z)*(y<x/2) THEN GOTO 100
    IF (z) THEN PRINT x, : p=p+1 : IF p%5=0 THEN PRINT
    NEXT x
