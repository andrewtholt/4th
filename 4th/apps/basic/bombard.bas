 10 PRINT "                   Bombardment"
 20 PRINT "     Creative Computing - Morristown, New Jersey"
 30 PRINT:PRINT:PRINT
 100 PRINT "You are on a battlefield with 4 platoons and you"
 110 PRINT "have 25 outposts available where they may be placed."
 120 PRINT "You can only place one platoon at any one outpost."
 130 PRINT "The computer does the same with its four platoons."
 135 PRINT
 140 PRINT "The object of the game is to fire missles at the"
 150 PRINT "outposts of the computer.  It will do the same to you."
 160 PRINT "The one who destroys all four of the enemy's platoons"
 170 PRINT "first is the winner."
 180 PRINT
 190 PRINT "Good luck... and tell us where you want the bodies sent!"
 200 PRINT :INPUT "Press a number key, then the RETURN key to continue ", R:PRINT 
 205 PRINT :PRINT :PRINT 
 210 PRINT "Write down the following matrix and use it to check"
 215 PRINT "off the numbers."
 220 FOR R=1 TO 5:PRINT:NEXT
 230 Q=0 : P=0 : Z=0
 260 FOR I=0 TO 100:@(I)=0:NEXT
 270 FOR R=1 TO 5
 280 I=(R-1)*5+1
 290 PRINT I,I+1,I+2,I+3,I+4
 300 NEXT
 350 FOR R=1 TO 5:PRINT:NEXT
 380 C=RND(25)
 390 D=RND(25)
 400 E=RND(25)
 410 F=RND(25)
 420 IF C=D THEN GOTO 390
 430 IF C=E THEN GOTO 400
 440 IF C=F THEN GOTO 410
 450 IF D=E THEN GOTO 400
 460 IF D=F THEN GOTO 410
 470 IF E=F THEN GOTO 410
 480 PRINT "What are your positions (known as G, H, K, and L)?"
 490 INPUT G,
 491 INPUT H
 492 INPUT K
 493 INPUT L
 495 PRINT
 500 INPUT "Where do you wish to fire your missle? ", Y
 520 IF Y=C THEN GOTO 710
 530 IF Y=D THEN GOTO 710
 540 IF Y=E THEN GOTO 710
 550 IF Y=F THEN GOTO 710
 560 GOTO 630
 570 M=RND(25)
 575 GOTO 1160
 580 IF X=G THEN GOTO 920
 590 IF X=H THEN GOTO 920
 600 IF X=L THEN GOTO 920
 610 IF X=K THEN GOTO 920
 620 GOTO 670
 630 PRINT " Ha, ha, you missed. My turn now!"
 640 PRINT:PRINT:GOTO 570
 670 PRINT "I missed you, you dirty rat. I picked ";M;". Your turn."
 680 PRINT:PRINT:GOTO 500
 710 Q=Q+1
 720 IF Q=4 THEN GOTO 890
 730 PRINT "You got one of my outposts!"
 740 IF Q=1 THEN GOTO 770
 750 IF Q=2 THEN GOTO 810
 760 IF Q=3 THEN GOTO 850
 770 PRINT "One down, three to go"
 780 PRINT:PRINT:GOTO 570
 810 PRINT "Two down, two to go"
 820 PRINT:PRINT:GOTO 570
 850 PRINT "Three down, one to go"
 860 PRINT:PRINT:GOTO 570
 890 PRINT "You got me, I'm going fast. But I'll get you when";
 900 PRINT " Y Transistors Secupera E"
 910 END
 920 Z=Z+1
 930 IF Z=4 THEN GOTO 1110
 940 PRINT "I got you! It won't be long now. Post ";X;" was hit."
 950 IF Z=1 THEN GOTO 990
 960 IF Z=2 THEN GOTO 1030
 970 IF Z=3 THEN GOTO 1070
 990 PRINT "You have only three outposts left."
 1000 PRINT:PRINT:GOTO 500
 1030 PRINT "You have only two outposts left."
 1040 PRINT:PRINT:GOTO 500
 1070 PRINT "You have only one outpost left."
 1080 PRINT:PRINT:GOTO 500
 1110 PRINT "You're dead! Your last outpost was at ";X;". Ha, ha, ha!"
 1120 PRINT "Better luck next time."
 1150 END
 1160 P=P+1
 1170 N=P-1
 1180 FOR T=1 TO N
 1190 IF M=@(T) THEN GOTO 570
 1200 NEXT
 1210 X=M
 1220 @(P)=M
 1230 GOTO 580
