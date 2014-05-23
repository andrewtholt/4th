5 rem *** HUNT THE WUMPUS ***
20 input "INSTRUCTIONS (Y=1 N=0)? ";i
25 if (i = 0) then goto 35
30 gosub 375
35 goto 80
80 rem *** SET UP CAVE (DODECAHEDRAL NODE LIST) ***
90 push 2,5,8,1,3,10,2,4,12,3,5,14,1,4,6
95 push 5,7,15,6,8,17,1,7,9,8,10,18,2,9,11
100 push 10,12,19,3,11,13,12,14,20,4,13,15,6,14,16
105 push 15,17,20,7,16,18,9,17,19,11,18,20,13,16,19
110 for j = 20 to 1 step -1
115 for k = 3 to 1 step -1
120 let @(j*3+k)=pop()
125 next k
130 next j
150 rem *** LOCATE L ARRAY ITEMS ***
155 rem *** 1-YOU, 2-WUMPUS, 3&4-PITS, 5&6-BATS ***
170 for j = 1 to 6
175 @(j+68) = RND(20)+1
180 @(j+74) = @(j+68)
185 next j
190 rem *** CHECK FOR CROSSOVERS (IE l(1)=l(2), ETC) ***
195 j = 1 : REM for j=1 to 6
200 k = 1 : REM for k=1 to 6
205 if j = k then goto 215
210 if @(j+68) = @(k+68) then goto 170
215 k=k+1 : if k<7 then goto 205
220 j=j+1 : if j<7 then goto 200
225 rem *** SET NO. OF ARROWS ***
230 a = 5
235 l = @(1+68)
240 rem *** RUN THE GAME ***
245 print "HUNT THE WUMPUS"
250 rem *** HAZARD WARNING AND LOCATION ***
255 gosub 585
260 rem *** MOVE OR SHOOT ***
265 gosub 670
270 goto 260 + (20*o) : REM on o goto 280,300
275 rem *** SHOOT ***
280 gosub 715
285 if f = 0 then goto 255
290 goto 310
295 rem *** MOVE ***
300 gosub 975
305 if f = 0 then goto 255
310 if f > 0 then goto 335
315 rem *** LOSE ***
320 print "HA HA HA - YOU LOSE!"
325 goto 340
330 rem *** WIN ***
335 print "HEE HEE HEE - THE WUMPUS'LL GET YOU NEXT TIME!!"
340 for j = 1 to 6
345 @(j+68) = @(j+74)
350 next j
355 input "SAME SETUP (Y=1 N=0)? ";i
365 if (i # 1) then goto 170
370 goto 230
375 rem *** INSTRUCTIONS ***
380 print "WELCOME TO 'HUNT THE WUMPUS'"
385 print "  THE WUMPUS LIVES IN A CAVE OF 20 ROOMS. EACH ROOM"
390 print "HAS 3 TUNNELS LEADING TO OTHER ROOMS. (LOOK AT A"
395 print "DODECAHEDRON TO SEE HOW THIS WORKS-IF YOU DON'T KNOW"
400 print "WHAT A DODECAHEDRON IS, ASK SOMEONE)"
405 print
410 print "     HAZARDS:"
415 print " BOTTOMLESS PITS - TWO ROOMS HAVE BOTTOMLESS PITS IN THEM"
420 print "     IF YOU GO THERE, YOU FALL INTO THE PIT (& LOSE!)"
425 print " SUPER BATS - TWO OTHER ROOMS HAVE SUPER BATS. IF YOU"
430 print "     GO THERE, A BAT GRABS YOU AND TAKES YOU TO SOME OTHER"
435 print "     ROOM AT RANDOM. (WHICH MAY BE TROUBLESOME)"
440 input "ENTER ANY NUMBER TO CONTINUE: ";a : print
445 print "     WUMPUS:"
450 print " THE WUMPUS IS NOT BOTHERED BY HAZARDS (HE HAS SUCKER"
455 print " FEET AND IS TOO BIG FOR A BAT TO LIFT).  USUALLY"
460 print " HE IS ASLEEP.  TWO THINGS WAKE HIM UP: YOU SHOOTING AN"
465 print "ARROW OR YOU ENTERING HIS ROOM."
470 print "     IF THE WUMPUS WAKES HE MOVES (P=.75) ONE ROOM"
475 print " OR STAYS STILL (P=.25).  AFTER THAT, IF HE IS WHERE YOU"
480 print " ARE, HE EATS YOU UP AND YOU LOSE!"
485 print
490 print "     YOU:"
495 print " EACH TURN YOU MAY MOVE OR SHOOT A CROOKED ARROW"
500 print "   MOVING:  YOU CAN MOVE ONE ROOM (THRU ONE TUNNEL)"
505 print "   ARROWS:  YOU HAVE 5 ARROWS.  YOU LOSE WHEN YOU RUN OUT"
510 print "   EACH ARROW CAN GO FROM 1 TO 5 ROOMS. YOU AIM BY TELLING"
515 print "   THE COMPUTER THE ROOM#S YOU WANT THE ARROW TO GO TO."
520 print "   IF THE ARROW CAN'T GO THAT WAY (IF NO TUNNEL) IT MOVES"
525 print "   AT RANDOM TO THE NEXT ROOM."
530 print "     IF THE ARROW HITS THE WUMPUS, YOU WIN."
535 print "     IF THE ARROW HITS YOU, YOU LOSE."
540 input "ENTER ANY NUMBER TO CONTINUE: ";a : print
545 print "    WARNINGS:"
550 print "     WHEN YOU ARE ONE ROOM AWAY FROM A WUMPUS OR HAZARD,"
555 print "     THE COMPUTER SAYS:"
560 print " WUMPUS:  'I SMELL A WUMPUS'"
565 print " BAT   :  'BATS NEARBY'"
570 print " PIT   :  'I FEEL A DRAFT'"
575 print
580 return
585 rem *** PRINT LOCATION & HAZARD WARNINGS ***
590 print
595 for j = 2 to 6
600 for k = 1 to 3
605 if @((@(1+68)*3)+k) # @(j+68) then goto 640
610 gosub 1510 : goto pop()
615 print "I SMELL A WUMPUS!"
620 goto 640
625 print "I FEEL A DRAFT"
630 goto 640
635 print "BATS NEARBY!"
640 next k
645 next j
650 print "YOU ARE IN ROOM ";@(1+68)
655 print "TUNNELS LEAD TO ";@(l*3+1);" ";@(l*3+2);" ";@(l*3+3)
660 print
665 return
670 rem *** CHOOSE OPTION ***
675 input "SHOOT OR MOVE (S=1 M=0)? ";i
685 if (i # 1) then goto 700
690 o = 1
695 return
700 if (i # 0) then goto 675
705 o = 2
710 return
715 rem *** ARROW ROUTINE ***
720 f = 0
725 rem *** PATH OF ARROW ***
735 input "NO. OF ROOMS (1-5): ";c
745 if c < 1 then goto 735
750 if c > 5 then goto 735
755 for k = 1 to c
760 input "ROOM # ";@(k+63)
770 if k < 3 then goto 790
775 if @(k+63) # @((k-2)+63) then goto 790
780 print "ARROWS AREN'T THAT CROOKED - TRY ANOTHER ROOM"
785 goto 760
790 next k
795 rem *** SHOOT ARROW ***
800 l = @(1+68)
805 k = 1 : REM for k = 1 to c
810 d = 1 : REM for d = 1 to 3
815 if @((l*3)+d) = @(k+63) then goto 895
820 d=d+1 : if d<4 then goto 815
825 rem *** NO TUNNEL FOR ARROW ***
830 l = @((l*3)+RND(3)+1)
835 goto 900
840 k=k+1 : if k<(c+1) then goto 810
845 print "MISSED"
850 l = @(1+68)
855 rem *** MOVE WUMPUS ***
860 gosub 935
865 rem *** AMMO CHECK ***
870 a = a-1
875 if a > 0 then goto 885
880 f = -1
885 return
890 rem *** SEE IF ARROW IS AT l(1) OR AT l(2)
895 l = @(k+63)
900 if l # @(2+68) then goto 920
905 print "AHA! YOU GOT THE WUMPUS!"
910 f = 1
915 return
920 if l # @(1+68) then goto 840
925 print "OUCH! ARROW GOT YOU!"
930 goto 880
935 rem *** MOVE WUMPUS ROUTINE ***
940 k = RND(4)+1
945 if k = 4 then goto 955
950 @(2+68) = @((@(2+68)*3)+k)
955 if @(2+68) # l then goto 970
960 print "TSK TSK TSK - WUMPUS GOT YOU!"
965 f = -1
970 return
975 rem *** MOVE ROUTINE ***
980 f = 0
985 input "WHERE TO? ";l
995 if l < 1 then goto 985
1000 if l > 20 then goto 985
1005 k = 1 : REM for k = 1 to 3
1010 rem *** CHECK IF LEGAL MOVE ***
1015 if @((@(1+68)*3)+k) = l then goto 1045
1020 k=k+1 : if k<4 then goto 1010
1025 if l = @(1+68) then goto 1045
1030 print "NOT POSSIBLE -";
1035 goto 985
1040 rem *** CHECK FOR HAZARDS ***
1045 @(1+68) = l
1050 rem *** WUMPUS ***
1055 if l # @(2+68) then goto 1090
1060 print "... OOPS! BUMPED A WUMPUS!"
1065 rem *** MOVE WUMPUS ***
1070 gosub 940
1075 if f = 0 then goto 1090
1080 return
1085 rem *** PIT ***
1090 if l = @(3+68) then goto 1100
1095 if l # @(4+68) then goto 1120
1100 print "YYYYIIIIEEEE . . . FELL IN PIT"
1105 f = -1
1110 return
1115 rem *** BATS ***
1120 if l = @(5+68) then goto 1130
1125 if l # @(6+68) then goto 1145
1130 print "ZAP--SUPER BAT SNATCH! ELSEWHEREVILLE FOR YOU!"
1135 l = RND(20)+1
1140 goto 1045
1145 return
1150 end
1500 REM *** uBasic subroutines ***
1510 if j-1=1 then push 615 : return
1530 if j-1<4 then push 625 : return
1540 push 635 : return
2000 REM *** uBasic documentation ***
2010 REM S = @( 4 - 63)
2020 REM P = @(64 - 68) [+63]
2030 REM L = @(69 - 74) [+68]
2040 REM M = @(75 - 80) [+74]
2050 REM fnA() = RND(20)+1
2060 REM fnB() = RND(3)+1
2070 REM fnC() = RND(4)+1
