 10 REM Copyright 2011, J.L. Bezemer - Made for Rosetta Code
 20 LET P=0: LET Q=0: LET Z=0
 30 INPUT "Rock, paper, or scissors (1 = rock, 2 = paper, 3 = scissors)? ", A
 40 IF A>3 THEN GOTO 200
 50 IF A<1 THEN GOTO 200
 60 GOTO (((A-1)+(RND(3)*3))*10)+100
100 Z=Z+1 : PRINT "We both chose 'rock'. It's a draw." : GOTO 30
110 P=P+1 : PRINT "You chose 'paper', I chose 'rock'. You win.." : GOTO 30
120 Q=Q+1 : PRINT "You chose 'scissors', I chose 'rock'. I win!" : GOTO 30
130 Q=Q+1 : PRINT "You chose 'rock', I chose 'paper'. I win!" : GOTO 30
140 Z=Z+1 : PRINT "We both chose 'paper'. It's a draw." : GOTO 30
150 P=P+1 : PRINT "You chose 'scissors', I chose 'paper'. You win.." : GOTO 30
160 P=P+1 : PRINT "You chose 'rock', I chose 'scissors'. You win.." : GOTO 30
170 Q=Q+1 : PRINT "You chose 'paper', I chose 'scissors'. I win!" : GOTO 30
180 Z=Z+1 : PRINT "We both chose 'scissors'. It's a draw." : GOTO 30
200 PRINT "There were ";Z;" draws. I lost ";P;" times, you lost ";Q;" times." : END
