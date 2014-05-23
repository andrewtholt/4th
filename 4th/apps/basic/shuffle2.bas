REM The Fisher/Yates shuffle (named after Ronald Fisher and Frank Yates),
REM also known as the Knuth shuffle (after Donald Knuth), is an algorithm
REM for generating a random permutation of a finite set�in plain terms, 
REM for randomly shuffling the set.
REM uBasic version, 2013, Hans Bezemer
 
PRINT "before:"
FOR L = 0 TO 51
    @(L) = L
    PRINT @(L); " ";
NEXT
 
FOR L = 51 TO 0 STEP -1
    C = RND(L + 1)
    IF C # L THEN 
      PUSH @(C), L, @(L), C
      GOSUB 100
    ENDIF
NEXT
 
PRINT : PRINT "after:"
FOR L = 0 TO 51
    PRINT @(L); " ";
NEXT
PRINT
END

100 @(POP()) = POP() : @(POP()) = POP() : RETURN