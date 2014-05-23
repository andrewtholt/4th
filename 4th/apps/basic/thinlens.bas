REM During lab, it's nice to be able to check student data quickly.
REM This program asks for: object position, screen position, and lens position
REM with reference to the bench scale.

REM Some student always comes up with data in which the object is at a high
REM number and the screen is at a low number on the scale. This is the opposite
REM of what is usually recommended, which I call an 'inverted' situation.
REM If that's the case, respond to the prompt 'Invert bench scale' with 'yes'
REM and the calculation is done correctly.

10 REM Thin lens calculations, By Dr. Donald Simanek, Sept 2001
12 REM Vanilla Basic, will work on Tandy 100.
15 V = 1
20 INPUT "Invert bench scale (0 = no, 1 = yes) ", Y
30 IF Y=1 THEN V=-1
40 INPUT "Object position ", O
50 INPUT "Lens position ", L
60 INPUT "Image position ", I
70 P=V*(L-O)
72 Q=V*(I-L) 
74 F=P*Q/(P+Q)
80 PRINT "P ="; P;", Q ="; Q
90 PRINT "F ="; F
100 INPUT "Another calculation (0 = no, 1 = yes) ", Y
110 IF Y=1 THEN GOTO 15
