2 PRINT "NICOMA"
4 PRINT "CREATIVE COMPUTING  MORRISTOWN, NEW JERSEY"
6 PRINT: PRINT: PRINT
10 PRINT "BOOMERANG PUZZLE FROM ARITHMETICA OF NICOMACHUS -- A.D. 90!"
20 PRINT
30 PRINT "PLEASE THINK OF A NUMBER BETWEEN 1 AND 100."
40 PRINT "YOUR NUMBER DIVIDED BY 3 HAS A REMAINDER OF";
45 INPUT A
50 PRINT "YOUR NUMBER DIVIDED BY 5 HAS A REMAINDER OF";
55 INPUT B
60 PRINT "YOUR NUMBER DIVIDED BY 7 HAS A REMAINDER OF";
65 INPUT C
70 PRINT
80 PRINT "LET ME THINK A MOMENT..."
85 PRINT
100 D=70*A+21*B+15*C
110 IF D<105 THEN GOTO 140
115 IF D=105 THEN GOTO 140
120 D=D-105
130 GOTO 110
140 PRINT "YOUR NUMBER WAS ";D;", RIGHT (0 = no, 1 = yes) ";
150 INPUT Z
180 IF Z=0 THEN GOTO 240
220 PRINT "HOW ABOUT THAT!!"
230 GOTO 250
240 PRINT "I FEEL YOUR ARITHMETIC IS IN ERROR."
250 PRINT
260 PRINT "LET'S TRY ANOTHER."
999 END