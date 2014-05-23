     REM This program uses the so-called Babylonian Algorithm
     REM without estimation.
  10 INPUT "Enter precision (0-4): ";A : IF (A>4)+(A<0) THEN GOTO 10
     LET B=2147483647/10^(A+A) : IF A=0 THEN LET B=B-1
  20 PRINT "Enter number (<";B+1;"): "; : INPUT "";C : IF (C<0)+(C>B) THEN GOTO 20
     PUSH C, A : GOSUB 9030
     PRINT : PRINT "SQRT(";C;") = ";TOS()/(10^A);".";
     FOR Q=1 TO A-1  : IF TOS()%(10^A) < 10^Q THEN PRINT "0";
     NEXT Q : PRINT POP()%(10^A) : END
9030 Push ((10^(Pop()*2))*Pop()) : @(255)=Tos()
9040 Push (@(255) + (Tos()/@(255)))/2
     If Abs(@(255)-Tos())<2 Then @(255)=Pop() : If Pop() Then Push @(255) : Return
     @(255) = Pop() : Goto 9040
     REM ** This is an integer SQR subroutine. Output is scaled by 10^(TOS()).
