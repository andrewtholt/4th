     REM Copyright 1983 by A. Clapman (ZX Basic), 2011 by H. Bezemer (uBasic)
     REM Permission is granted by the authors to use and distribute this software
     REM provided these copyright notices are preserved.
     REM ** Attributes of locations
     @(0)  = 000000 : @(1)  = 033825 : @(2)  = 033795 : @(3)  = 038977
     @(4)  = 033830 : @(5)  = 034000 : @(6)  = 105605 : @(7)  = 204833
     @(8)  = 242986 : @(9)  = 034152 : @(10) = 047377 : @(11) = 033833
     @(12) = 033837 : @(13) = 277889 : @(14) = 328737 : @(15) = 427041
     @(16) = 033953 : @(17) = 034113
     REM ** Attributes of objects
     @(20)=04 : @(21)=37 : @(22)=03 : @(23)=49 : @(24)=14
     @(25)=45 : @(26)=12 : @(27)=11 : @(28)=16 : @(29)=15
     @(30)=06 : @(31)=01 : @(32)=08 : @(33)=01
     REM ** Initialization
     LET H=3 : LET T=0 : LET N=0 : LET S=0 : LET W=0 : LET E=0
     GOTO 9000
     REM ** Commands
 100 IF N#1 THEN LET H=N
     IF N=1 THEN GOSUB 5010
     RETURN
 200 IF S#1 THEN LET H=S
     IF S=1 THEN GOSUB 5010
     RETURN
 300 IF W#1 THEN LET H=W
     IF W=1 THEN GOSUB 5010
     RETURN
 400 IF E#1 THEN LET H=E
     IF E=1 THEN GOSUB 5010
     RETURN
 500 IF (@(20)=4)*(H#4) THEN PRINT "YOU HAVEN'T GOT ANYTHING TO CARRY IT IN!!" : PRINT : RETURN
     IF (@(20)=4)*(H=4) THEN LET @(20)=0 : PRINT "YOU STRAP IT ON YOUR WRIST." : PRINT : RETURN
     LET Z=0 : FOR I=21 TO 33
     IF (@(I)%32=H)*(@(I)/32=0) THEN LET @(I)=0 : LET Z=1 : PRINT "IT ZOOMS SAFELY INTO YOUR WATCH!" : PRINT
     NEXT : IF Z=0 THEN GOSUB 5020
     RETURN
 600 PRINT "You are carrying:" : LET A=0 : GOSUB 6000
     IF Z=0 THEN GOSUB 6010 : PRINT "Nothing"
     PRINT : RETURN
 700 IF ((T/8)%2)+@(33) THEN GOSUB 5010 : RETURN
     IF H#13 THEN GOSUB 5020 : RETURN
     PRINT "Chop chop smash smash.. The door has been smashed down." : PRINT : LET T=T+8
     RETURN
 800 IF @(32) THEN GOSUB 5030 : RETURN
     IF ((T/2)%2) THEN PRINT "You're already wearing it!!" : PRINT : RETURN
     LET T=T+2 : PRINT "You're wearing a helmet now!!" : PRINT
     RETURN
 900 IF ((T%2)+@(22)+@(26)) THEN GOSUB 5010 : RETURN
     LET T=T+1 : PRINT "The saw is powered up!!" : PRINT
     RETURN
1000 IF @(29) THEN GOSUB 5030 : RETURN
     IF H#9 THEN PRINT "I can't see anywhere to insert it!!" : PRINT : RETURN
     LET @(29)=1 : LET T=T+4
     PRINT "The wall suddenly shakes and glides one side leaving a doorway west!!" : PRINT
     RETURN
1100 IF @(30) THEN GOSUB 5030 : RETURN
     IF @(24) THEN PRINT "You haven't got anything to sharpen it on!!" : PRINT : RETURN
     PRINT "The knife turns extra sharp!!" : PRINT : LET @(30)=1 : LET @(31)=0
     RETURN
1200 IF @(31) THEN GOSUB 5010 : RETURN
     IF H#5 THEN GOSUB 5020 : RETURN
     IF ((T/32)%2) THEN PRINT "The poor thing is already dead." : PRINT : RETURN
     LET T=T+32 : PRINT "Squelch. The dagger sinks to the hilt in the dragon."
     PRINT "It's dead. Poor thing." : PRINT : IF ((T/64)%2) THEN LET T=T-64
     RETURN
1300 IF ((T/16)%2)+@(22)+@(26) THEN GOSUB 5010 : RETURN
     IF H#17 THEN GOSUB 5020 : RETURN
     IF (T%2)=0 THEN PRINT "The saw won't work without electricity!!" : PRINT : RETURN
     IF ((T/2)%2)=0 THEN PRINT "The tree falls on your unprotected head. Crunch." : PRINT : GOTO 5000
     PRINT "The tree falls down on your safety helmet." : LET T=T+16
     PRINT "An axe falls out of the top of the tree." : PRINT : LET @(33)=H
     RETURN
1400 PRINT "There is no easy way out of here!!"
     PRINT "So you decide to commit suicide."
     GOTO 5000
     REM ** General subroutines
5000 PRINT "YOU'RE DEAD!!" : END
5010 PRINT "YOU CAN'T, IDIOT!!" : PRINT : RETURN
5020 PRINT "It isn't here!!" : PRINT : RETURN
5030 PRINT "You aren't carrying it, stupid!!" : PRINT : RETURN
5040 E=A%32 : W=(A/32)%32 : S=(A/1024)%32 : N=(A/32768)%32 : RETURN
5050 GOSUB 5140 : PRINT "You are at "; : GOSUB 6000+(H*10) : LET A=@(H) : GOSUB 5040
     PRINT "Directions you may proceed in:" : GOSUB 6010
     GOSUB 5100 : GOSUB 5110 : GOSUB 5120 : GOSUB 5130 : PRINT : PRINT
     PRINT "Things of interest here:" : LET A=H : GOSUB 6000
     IF Z=0 THEN GOSUB 6010 : PRINT "None"
     GOSUB 5060 : RETURN
5060 IF (H#5)*((T/64)%2) THEN LET T=T-64
     IF (H=5)*((T/32)%2) THEN PRINT : PRINT "The dragon is dead."
     IF (H=5)*((T/64)%2) THEN PRINT : PRINT "The dragon doesn't like you so he kills you." : GOTO 5000
     IF (H=5)*(((T/32)%2)=0) THEN LET T=T+64 : PRINT : PRINT "The dragon blocks a hole in the EAST wall."
     IF (H=17)*((T/16)%2) THEN PRINT : PRINT "The tree is lying on the ground."
     IF (H=17)*(((T/16)%2)=0) THEN PRINT : PRINT "There is something glistening at the top of the tree."
     IF (H=9)*(((T/4)%2)=0) THEN PRINT : PRINT "There is a small slot on the west wall."
     IF (H=13)*((T/8)%2) THEN PRINT : PRINT "The door is smashed down."
     RETURN
5100 IF N#1 THEN PRINT "North  ";
     RETURN
5110 IF (H=13)*(((T/8)%2)=0) THEN S=1
     IF S#1 THEN PRINT "South  ";
     RETURN
5120 IF (H=9)*(((T/4)%2)=0) THEN W=1
     IF W#1 THEN PRINT "West  ";
     RETURN
5130 IF (H=5)*(((T/32)%2)=0) THEN E=1
     IF E#1 THEN PRINT "East  ";
     RETURN
5140 IF H#0 THEN RETURN
     PRINT "LASER BOLTS FLASH OUT FROM THE KILLO-ZAP GUNS FIXED TO THE ROAD!"
     IF @(27)*@(28) THEN PRINT "FRIZZLE!!" : GOTO 5000
     IF @(27) THEN PRINT "THE RIGHT RAY IS REFLECTED BY THE REFLECTOR. THE LEFT ONE ISN'T!!" : GOTO 5000
     IF @(28) THEN PRINT "THE LEFT RAY IS REFLECTED BY THE MIRROR. THE RIGHT ONE ISN'T!!" : GOTO 5000
     PRINT "BOTH THE RAYS ARE REFLECTED BY THE MIRROR AND THE REFLECTOR!!"
     PRINT "YOU HAVE MANAGED TO ESCAPE ALIVE!!" : END
6000 LET Z=0
     FOR I=20 TO 33
     IF @(I)%32=A THEN GOSUB 6010 : GOSUB 7000+(10*(I-20)) : GOSUB 7200+(10*(I-20)) : Z=1
     NEXT
     RETURN
6010 PRINT "        "; : RETURN
     REM ** Location desciptions
6020 PRINT "a road leading west and east. Two things are pointing to the west." : RETURN
6030 PRINT "a bend in the road." : RETURN
6040 PRINT "a small dark shack." : RETURN
6050 PRINT "a small dark shack." : RETURN
6060 PRINT "a road leading north and south. There are shacks either side." : RETURN
6070 PRINT "a road leading north. There is a pyramid south." : RETURN
6080 PRINT "the entrance hall of the pyramid. There is a road north." : RETURN
6090 PRINT "the embalming room." : RETURN
6100 PRINT "the recreation room. An exit to the garden is east." : RETURN
6110 PRINT "the room of ANKH." : RETURN
6120 PRINT "a small triangular room." : RETURN
6130 PRINT "a long oblong room." : RETURN
6140 PRINT "the funeral parlour." : RETURN
6150 PRINT "the treasure room. It has been looted. There is a smashed door north." : RETURN
6160 PRINT "a small circular cave." : RETURN
6170 PRINT "a small garden." : RETURN
     REM ** Object adjectives
7000 PRINT "wrist "; : RETURN
7010 PRINT "magenta, firebreathing "; : RETURN
7020 PRINT "mobile electricity "; : RETURN
7030 PRINT "Canadian Redwood "; : RETURN
7040 PRINT "granite "; : RETURN
7050 PRINT "thick wooden "; : RETURN
7060 PRINT "electric "; : RETURN
7070 PRINT "purple "; : RETURN
7080 PRINT "green "; : RETURN
7090 PRINT "10 pence "; : RETURN
7100 PRINT "butter "; : RETURN
7110 PRINT "razor sharp "; : RETURN
7120 PRINT "safety "; : RETURN
7130 PRINT "sharp "; : RETURN
     REM ** Object names
7200 PRINT "watch" : RETURN
7210 PRINT "dragon" : RETURN
7220 PRINT "generator" : RETURN
7230 PRINT "tree" : RETURN
7240 PRINT "slab" : RETURN
7250 PRINT "door" : RETURN
7260 PRINT "saw" : RETURN
7270 PRINT "mirror" : RETURN
7280 PRINT "reflector" : RETURN
7290 PRINT "coin" : RETURN
7300 PRINT "knife" : RETURN
7310 PRINT "dagger" : RETURN
7320 PRINT "helmet" : RETURN
7330 PRINT "axe" : RETURN
     REM ** Main command loop
9000 GOSUB 5050 : PRINT
     PRINT " (1) North (2) South (3) West  (4) East"
     PRINT " (5) Take  (6) List  (7) Smash (8) Wear"
     PRINT " (9) Plug (10) Push (11) File (12) Kill"
     PRINT "(13) Saw  (14) Exit" : PRINT
     INPUT "Command: ";A
     PRINT : IF (A<1)+(A>14) THEN PRINT "You can't do that." : PRINT : GOTO 9000
     GOSUB A*100 : GOTO 9000
