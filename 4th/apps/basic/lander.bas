  10 REM Lunar Lander
     REM By Diomidis Spinellis
     REM Chipmunk Basic version
     PRINT "You aboard the Lunar Lander about to leave the spacecraft."
     GOSUB 4000
     GOSUB 1000
  80 GOSUB 2000
     GOSUB 3000
     H = H - V
     V = ((V + G) * 10 - U * 2) / 10
     F = F - U
     IF H > 0 THEN GOTO 80
     H = 0
     GOSUB 2000
     IF V > 5 THEN GOTO 200
     PRINT "Congratulations!  This was a very good landing."
 170 GOSUB 5000
     GOTO 10
 200 PRINT "You have crashed."
     GOTO 170
1000 REM Initialise
     V = 70
     F = 500
     H = 1000
     G = 2
     RETURN
2000 REM Print values
     PRINT
     PRINT "         Meter readings"
     PRINT "         --------------"
     PRINT "Fuel     (gal)  : "; F
     PRINT "Velocity (m/sec): "; V
     PRINT "Height   (m)    : "; H
     PRINT
     RETURN
3000 REM User input
     IF F = 0 THEN GOTO 3070
3010 INPUT "How much fuel will you use? ", U
     IF U<0 THEN GOTO 3090
     IF U<F THEN GOTO 3060
     IF U=F THEN GOTO 3060
     PRINT "Sorry, you have not got that much fuel!"
     PRINT F
     GOTO 3010
3060 RETURN
3070 U = 0
     RETURN
3090 PRINT "No cheating please!  Fuel must be >= 0."
3100 GOTO 3010
4000 REM Detachment
     PRINT "Ready for detachment"
     PRINT "-- COUNTDOWN --"
     FOR I = 1 TO 11
     PRINT 11 - I,
     GOSUB 4500
     NEXT
     PRINT
     PRINT "You have left the spacecraft."
     PRINT "Try to land with velocity less than 5 m/sec."
4040 RETURN
4500 REM Delay
     FOR J = 1 TO 500
     NEXT
     RETURN
5000 INPUT "Do you want to play again? (0 = no, 1 = yes) ", Y
5020 IF Y = 0 THEN GOTO 5040
     RETURN
5040 PRINT "Have a nice day."
     END
9992 REM --- End of source code ---
9993 REM I know it stinks as a game, but see it as a relic from old times.
9994 REM Ingemar Ragnemalm, PhD
9995 REM Image processing, Mac shareware games
9996 REM E-mail address: ingemar@isy.liu.se or ingemar@lysator.liu.se
