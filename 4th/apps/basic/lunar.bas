10 REM Lunar Lander
20 REM DO
30 PRINT "Beginning landing procedure.........."
40 PRINT
50 PRINT "G o o d  l u c k ! ! !"
60 PRINT
70 B = 0
80 F = 150
90 H = 1000
100 Q = -1
110 T = 0
120 V = 50
130 Y = 1
140 REM DO
150 PRINT "Sec", T; " Feet", H; " Speed", V; " Fuel", F
160 PRINT "Units";
170 INPUT B
180 IF B > -1 GOTO 220
190 PRINT
200 PRINT "Control out."
210 END
220 REM END IF
230 IF B > 30 B = 30
240 IF B > F B = F
250 REM DO
260 W = V - B + 5
270 F = F - B
280 H = H - (V + W) / 2
290 IF H < 1 GOTO 380
300 T = T + 1
310 V = W
320 IF F > 0 GOTO 380
330 IF B > 0 PRINT "**** Out of fuel ****"
340 PRINT "Sec", T; " Feet", H; " Speed", V; " Fuel", F
350 B = 0
370 GOTO 250
380 REM LOOP
390 IF H > 0 GOTO 140
400 REM LOOP
410 PRINT "***** Contact *****"
430 H = H + (W + V) / 2
440 IF B = 5 GOTO 490
450 N = V * V + H * (10 - 2 * B)
460 GOSUB 750
470 D = (S - V) / (5 - B)
480 GOTO 510
490 REM ELSE
500 IF V D = H / V
510 REM END IF
520 W = V + (5 - B) * D
530 PRINT "Touchdown at "; T + D; " seconds."
540 PRINT "Landing velocity "; W; " feet/sec."
550 PRINT F; " units of fuel remaining."
570 IF W # 0 GOTO 600
580 PRINT "Congratulations! A perfect landing!!"
590 PRINT "Your license will be renewed.......later."
600 REM END IF
610 IF (W > -2) * (W < 2) GOTO 640
620 PRINT "***** Sorry, but you blew it!!!! *****"
630 PRINT "Appropriate condolences will be sent to your next of kin."
640 REM END IF
650 PRINT
670 N = 0
680 PRINT "Another mission (Y=1 or N=0)";
690 INPUT N
700 PRINT
710 IF N = 1 GOTO 20
720 REM LOOP
730 PRINT "Control out."
740 END
750 REM SUBROUTINE square root
760 S = 1
770 K = 0
780 REM DO
790 S = (S + N / S) / 2
800 K = K + 1
810 IF (K < 100) * S GOTO 780
820 REM LOOP
830 RETURN

