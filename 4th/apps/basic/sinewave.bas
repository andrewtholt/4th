     REM Original program by David Ahl, Creative Computing, 1978
     REM uBasic version by J.L. Bezemer, 2011
     REM Based on an integer 4tH version
     REM ***
     LET Z=0 : FOR X=0 TO 160 : PUSH X*2500 : GOSUB 9000
     FOR Y=1 TO ((POP()*25)+260000)/10000 : PRINT " "; : NEXT Y
     IF Z THEN PRINT "J.L. Bezemer"
     IF Z=0 THEN PRINT "4tH compiler"
     LET Z=Z=0 : NEXT X : END
9000 LET @(255)=TOS()<0 : PUSH ABS(POP()%62832)
     IF TOS()>31416 THEN @(255)=@(255)=0 : PUSH POP()-31416
     IF TOS()>15708 THEN PUSH 31416-POP()
     PUSH (TOS()*TOS())/10000 : PUSH 10000+((10000*-(TOS()/72))/10000)
     PUSH 10000+((POP()*-(TOS()/42))/10000) : PUSH 10000+((POP()*-(TOS()/20))/10000)
     PUSH 10000+((POP()*-(POP()/6))/10000)  : PUSH (POP()*POP())/10000 
     IF @(255) THEN PUSH -POP()
     RETURN
     REM ** This is an integer SIN subroutine. Input and output are scaled by 10K.
9010 PUSH ABS(POP()%62832) : IF TOS()>31416 THEN PUSH 62832-POP()
     LET @(255)=TOS()>15708 : IF @(255) THEN PUSH 31416-POP()
     PUSH TOS() : PUSH (POP()*POP())/10000 : PUSH 10000+((10000*-(TOS()/56))/10000)
     PUSH 10000+((POP()*-(TOS()/30))/10000): PUSH 10000+((POP()*-(TOS()/12))/10000)
     PUSH 10000+((POP()*-(POP()/2))/10000) : IF @(255) THEN PUSH -POP()
     RETURN
     REM ** This is an integer COS subroutine. Input and output are scaled by 10K.
9020 PUSH TOS() : GOSUB 9000 : LET @(254)=POP() : GOSUB 9010
     PUSH (@(254)*10000)/POP() : RETURN
     REM ** This is an integer TAN subroutine. Input and output are scaled by 10K.


