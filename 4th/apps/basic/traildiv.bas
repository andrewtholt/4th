1 REM Write a boolean function that tells whether a given integer is prime.
2 REM Remember that 1 and all non-positive numbers are not prime.
3 REM Use trial division. Even numbers over two may be eliminated right away.
4 REM A loop from 3 to SQRT(n) will suffice, but other loops are allowed
10 LET n=0: LET p=0
20 INPUT "Enter number: ";n
30 LET p=0 : IF n>1 THEN GOSUB 1000
40 IF p=0 THEN PRINT n;" is not prime!"
50 IF p#0 THEN PRINT n;" is prime!"
60 GOTO 10
1000 REM ***************
1001 REM * PRIME CHECK *
1002 REM ***************
1010 LET p=0
1020 IF (n%2)=0 THEN RETURN
1030 LET p=1 : PUSH n,0 : GOSUB 9030
1040 FOR i=3 TO POP() STEP 2
1050 IF (n%i)=0 THEN LET p=0: PUSH n,0 : GOSUB 9030 : LET i=POP()
1060 NEXT i
1070 RETURN
9030 Push ((10^(Pop()*2))*Pop()) : @(255)=Tos()
9040 Push (@(255) + (Tos()/@(255)))/2
     If Abs(@(255)-Tos())<2 Then @(255)=Pop() : If Pop() Then Push @(255) : Return
     @(255) = Pop() : Goto 9040
     REM ** This is an integer SQR subroutine. Output is scaled by 10^(TOS()).