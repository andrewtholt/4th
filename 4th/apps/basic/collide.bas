1 REM Here's a really simple one, for one dimensional collisions,
2 REM for example, collisions on an air track.
10 REM Collide.bas. Calculation of elastic collisions.
20 REM
30 PRINT "One-dimensional elastic collision of two bodies."
35 PRINT
36 INPUT "Mass of first body ", A
50 INPUT "Velocity of first body ", B
55 PRINT
60 INPUT "Mass of second body ", C
70 INPUT "Velocity of second body ", D
80 F=(A*(2*B-D)+C*D)/(A+C)
81 E=(A*B+C*(2*D-B))/(A+C)
90 PRINT
91 PRINT "Final velocity of first body = "; E
92 PRINT "Final velocity of second body = "; F
95 PRINT
98 INPUT "Do you want to play again? (0 = no, 1 = yes) ", Y
99 IF Y = 1 THEN GOTO 30
