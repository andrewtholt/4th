10 rem **************************************
20 rem *** Play the "blackjack" (21) game ***
30 rem **************************************
40 m = 1000
50 rem
60 rem Create deck of cards and shuffle it
70 rem
80 for i=0 to 51: @(i) = i: next
90 for i=0 to 51: g=@(i): @(i)=@(g): @(g)=rnd(52): next
100 rem
110 rem Prompt for amount of bet (on this game)
120 rem
130 print "You have "; m; " dollars"
140 input "How much do you wish to bet? "; b: if b=0 then stop
150 if b>m then print "You don't have enough money":goto 140
160 t = 0: d = 0
170 rem
180 rem Prompt PLAYER for another card
190 rem
200 print "Total: "; t: Input ">>> Another card (0 = no, 1 = yes)? ", y
210 if y=0 then goto 380
220 if y#1 then print "Please answer 1-Yes or 0-No": goto 200
230 c = @(d): d = d + 1: gosub 530
240 c = c % 13: if c > 9 then c = 9
250 if c > 0 then goto 300
260 input "(1) one or (2) ten? ", h
270 if h=1 then goto 300
280 if h#2 then goto 260
290 c = 9
300 t = t + c + 1
310 if t > 21 then goto 320
315 goto 200
320 print "You went over 21! - you LOSE!"
330 m = m - b: if m > 0 then goto 80
340 print "You went BUST!":end
350 rem
360 rem Play DEALER
370 rem
380 j = 0
390 c = @(d): d = d + 1: print "Dealer draws ",: gosub 530
400 c = c % 13: if c > 9 then c = 9
410 if c > 0 then goto 470
420 if j < 10 then goto 450
430 if (j+10) > 23 then goto 460
450 c = 9
460 print "Dealer chooses", c+1
470 j = j + c + 1: print "Dealer totals", j: if j < t then goto 390
480 if j > 21 then goto 490
485 print "Dealer wins - You LOSE!": goto 330
490 print "Dealer loses - You WIN!!!": m = m + b: goto 80
500 rem
510 rem Subroutine to display text description of a card
520 rem
530 if c / 13 = 0 then print "Hearts";
540 if c / 13 = 1 then print "Diamonds";
550 if c / 13 = 2 then print "Clubs";
560 if c / 13 = 3 then print "Spades";
570 print " of ";
580 if c % 13 = 0 then print "Ace"
590 if c % 13 = 1 then print "Two"
600 if c % 13 = 2 then print "Three"
610 if c % 13 = 3 then print "Four"
620 if c % 13 = 4 then print "Five"
630 if c % 13 = 5 then print "Six"
640 if c % 13 = 6 then print "Seven"
650 if c % 13 = 7 then print "Eight"
660 if c % 13 = 8 then print "Nine"
670 if c % 13 = 9 then print "Ten"
680 if c % 13 = 10 then print "Jack"
690 if c % 13 = 11 then print "Queen"
700 if c % 13 = 12 then print "King"
710 return

