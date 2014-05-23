10 REM Gunner
20 REM
30 REM DO
40 R = RND(40000) + 20000
50 PRINT "Maximum range of your gun is ";R;" yards."
60 Z = 0
70 L = 0
80 REM DO
90 G = 0
100 T = R / 10 + RND(R / 10 * 8) + 1
110 K = 0
120 PRINT "Distance to the target is ";T;" yards."
130 REM DO
140 PRINT
150 B = 0
160 PRINT "Elevation";
170 INPUT B
180 IF B > 0 GOTO 250
190 PRINT
200 PRINT "Better go back for refresher training!"
210 PRINT
220 PRINT "OK. Return to base camp."
230 PRINT
240 END
250 REM END IF
260 IF B < 90 GOTO 290
270 PRINT "Maximum elevation is 89 degrees."
280 GOTO 130
290 REM END IF
300 K = K + 1
310 IF K < 6 GOTO 360
320 PRINT
330 PRINT "Boom !!!!  You have just been destroyed by the enemy."
340 L = 20
350 GOTO 560
360 REM END IF
370 N = 2 * B
380 GOSUB 810
390 E = T - R * S / 1000
400 IF (2 * (E > 0) - 1) * E > 600 GOTO 490
410 PRINT "*** Target destroyed *** ";K;" rounds of ammunition expended."
420 L = L + K
430 IF Z = 4 GOTO 560
440 Z = Z + 1
450 PRINT
460 PRINT "The forward observer has sighted more enemy activity..."
470 G = 1
480 GOTO 560
490 REM END IF
500 IF E < 601 GOTO 530
510 PRINT "Short of target by "; (2 * (E > 0) - 1) * E; " yards."
520 GOTO 130
530 REM END IF
540 PRINT "Over target by "; (2 * (E > 0) - 1) * E; " yards."
550 GOTO 130
560 REM LOOP
570 IF G GOTO 740
580 PRINT
590 PRINT "Total rounds expended were "; L
600 IF L > 18 GOTO 630
610 PRINT "Nice shooting !!"
620 GOTO 660
630 REM ELSE
640 PRINT
650 PRINT "Better go back for refresher training!"
660 REM END IF
670 PRINT
680 N = 0
690 Y = 1
700 PRINT "Try again (Y=1 or N=0)";
710 INPUT N
720 IF N PRINT
730 IF N GOTO 30
740 REM LOOP
750 IF G GOTO 80
760 REM LOOP
770 PRINT
780 PRINT "OK. Return to base camp."
790 PRINT
800 END
810 REM SUBROUTINE sine
820 C = 10000
830 S = 0
840 M = 1
850 REM DO
860 IF M > N GOTO 920
870 U = S * 9998 / 10000 + C * 175 / 10000
880 C = C * 9998 / 10000 - S * 175 / 10000
890 S = U
900 M = M + 1
910 GOTO 850
920 REM LOOP
930 S = S / 10
940 C = C / 10
950 RETURN

