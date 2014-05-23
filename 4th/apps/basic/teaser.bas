 100 REM  Shooting Stars in 68000 Tiny BASIC
 110 REM  Adapted by Gordon Brandly from an article in DDJ #7
 120 REM  This game was described in the May 1976 issue
 130 REM  of BYTE magazine and I haven't the faintest idea
 140 REM  how to play it!
 160 @(1)=-23
 170 @(2)=-3
 180 @(3)=-19
 190 @(4)=-11
 200 @(5)=2
 210 @(6)=-5
 220 @(7)=-13
 230 @(8)=-7
 240 @(9)=-17
 250 @(10)=1518
 260 @(11)=1311
 270 @(12)=570
 280 @(13)=3289
 290 @(14)=2310
 300 @(15)=1615
 310 @(16)=2002
 320 @(17)=1547
 330 @(18)=1190
 340 REM  Initialize the shot counter
 350 C=0
 360 REM  Randomize star and black hole position
 370 FOR I=1 TO 9
 380 X=RND(32762)
 390 IF X>20000 @(I)=-@(I)
 400 NEXT
 410 REM  Print initial pattern
 420 GOSUB 840
 430 REM  Get first shot
 440 INPUT "Your shot: ", X
 450 IF (X<1)+(X>9) THEN PRINT "You must enter a number from 1 to 9." : GOTO 440
 460 REM  Increment shot counter
 470 C=C+1
 480 REM  Check for valid shot
 490 IF @(X)>0 GOTO 530
 500 PRINT "You can only shoot stars."
 510 GOTO 440
 520 REM  Initialize scoring counter
 530 B=0
 540 REM  Invert (change sign) of appropriate galaxy.
 550 GOSUB 770
 560 REM  Check score by adding star values
 570 FOR L=1 TO 9
 580 B=B+@(L)
 590 NEXT
 600 REM  Print out modified universe
 610 GOSUB 840
 620 REM  If B=-100 all points are black holes
 630 IF B=-100 GOTO 690
 640 REM  If B is neither -100 nor 96 game continues
 650 IF B#96 GOTO 440
 660 PRINT "You win!"
 670 PRINT "You fired ";C;" shots."
 680 GOTO 700
 690 PRINT "Sorry, you lost."
 700 PRINT "To play again, type RUN and press the RETURN key."
 710 END
 720 REM  The following subroutine checks to see if the F value
 730 REM  for the shot can be evenly divided by the S value
 740 REM  for each position.  If S divides into F without
 750 REM  a remainder, the star or black hole is inverted.
 760 REM  (Its sign is changed.)
 770 FOR K=1 TO 9
 780 IF (@(X+9)/@(K))*@(K)=@(X+9) @(K)=-@(K)
 790 NEXT
 800 RETURN
 810 REM  This subroutine prints out the galaxy
 840 REM : FOR Z=1 TO 24 : PRINT : NEXT
 850 PRINT : FOR J=1 TO 9
 860 IF @(J)<0 PRINT "   .",
 870 IF @(J)>0 PRINT "   *",
 880 REM  If J isn't divisible by 3, skip carriage returns.
 890 IF J/3*3#J GOTO 920
 900 PRINT
 910 PRINT
 920 NEXT
 930 RETURN
