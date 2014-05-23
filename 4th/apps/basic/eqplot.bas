 10 REM  Equation plotting program from April 1977 BYTE magazine
 15 PRINT : PRINT "Equation plotting program - enter equation in program line 1010": PRINT
 20 PRINT : INPUT "Enter 1- end program, 2- show data values: "; X
 30 IF (X<1)+(X>2) GOTO 20
 40 GOTO X*100
 100 STOP
 200 INPUT "Enter starting X value: "; T : INPUT "Enter step interval: "; V
 205 X=T
 210 PRINT "X       Y"
 215 PRINT "---     ---"
 220 GOSUB 1000
 230 PRINT X,Y
 240 X=X+5*V
 250 IF X<T+75*V GOTO 220
 270 IF Y<0 GOTO 490
 290 PRINT : PRINT : GOTO 20
 1000 REM  The equation to be plotted is:
 1010 Y=X*X*X/10+X*X/4+X
 1999 RETURN
