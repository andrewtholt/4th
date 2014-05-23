 10 REM  Various games adapted for 68000 Tiny BASIC
 20 REM  Adapted by Gordon Brandly from Dr. Dobb's Journal #7
 30 PRINT
 1000 PRINT "Which game do you want to play?"
 1001 PRINT "Type 1 for Stars"
 1002 PRINT "Type 2 for Acey-Ducey"
 1003 PRINT "Type 3 for Trap"
 1004 PRINT "Type 4 for Slots"
 1010 PRINT:INPUT "Enter your choice: "; Z
 1020 IF Z<1 GOTO 1000
 1030 IF Z>4 GOTO 1000
 1040 IF Z=1 GOTO 1100
 1050 IF Z=2 GOTO 2000
 1060 IF Z=3 GOTO 4000
 1070 IF Z=4 GOTO 5000
 1100 PRINT:PRINT
 1120 PRINT "Welcome to my galaxy. I'm in charge of the stars here."
 1130 PRINT "Play my game STARS and get some stars for yourself!"
 1140 PRINT
 1150 PRINT "I will think of a whole number from 1 to 100."
 1160 PRINT "Try to guess my number. After you guess, I will"
 1170 PRINT "display one or more stars (*). The closer"
 1180 PRINT "you are to my number, the more stars I will display."
 1190 PRINT "One star (*) means you are far away from my"
 1200 PRINT "number, seven stars (*******) means you are very,"
 1210 PRINT "very, very close to my number!"
 1220 X=RND(100)
 1230 PRINT
 1240 PRINT "OK, starseeker, I am thinking of a number. Start guessing."
 1250 N=1
 1260 PRINT
 1270 INPUT "Enter your guess: "; G
 1290 IF G=X GOTO 1550
 1370 D=ABS(G-X)
 1380 IF D>63 GOTO 1500
 1390 IF D>31 GOTO 1490
 1400 IF D>15 GOTO 1480
 1410 IF D>7 GOTO 1470
 1420 IF D>3 GOTO 1460
 1430 IF D>1 GOTO 1450
 1440 PRINT " *";
 1450 PRINT " *";
 1460 PRINT " *";
 1470 PRINT " *";
 1480 PRINT " *";
 1490 PRINT " *";
 1500 PRINT " *"
 1520 N=N+1
 1530 GOTO 1260
 1550 PRINT " ** ** ** ** ** ** ** ** ** ",
 1560 PRINT "** ** ** ** ** ** ** ** ** !!!"
 1590 PRINT "That's it!!! You guessed my cosmic number in ";N;" guesses."
 1600 PRINT
 1610 PRINT "Do you want to play again?"
 1620 INPUT "Enter 1 to play again or 2 to play a different game: "; I
 1640 IF I=1 GOTO 1220
 1650 IF I=2 GOTO 1000
 1660 GOTO 1600
 2000 REM  Acey-Ducey
 2100 PRINT
 2101 PRINT "Acey-Ducey is played in the following manner:"
 2102 PRINT "The dealer (computer) deals two cards face up."
 2103 PRINT "You have the option to bet or not to bet depending"
 2104 PRINT "on whether or not you feel the next card will have"
 2105 PRINT "a value between the first two."
 2106 PRINT "If you don't want to bet, enter a bet of 0."
 2110 PRINT
 2160 N=100
 2170 Q=100
 2190 PRINT "You now have ";Q;" dollars."
 2195 PRINT
 2200 GOTO 2260
 2210 Q=Q+M
 2220 GOTO 2190
 2240 Q=Q-M
 2250 GOTO 2190
 2260 PRINT "Here are your next two cards..."
 2270 A=RND(13)+2
 2300 B=RND(13)+2
 2330 IF A>B-1 GOTO 2270
 2340 PRINT "        ";
 2350 IF A<11 GOTO 2400
 2360 IF A=11 GOTO 2420
 2370 IF A=12 GOTO 2440
 2380 IF A=13 GOTO 2460
 2390 IF A=14 GOTO 2480
 2400 PRINT A
 2410 GOTO 2490
 2420 PRINT "Jack"
 2430 GOTO 2500
 2440 PRINT "Queen"
 2450 GOTO 2500
 2460 PRINT "King"
 2470 GOTO 2500
 2480 PRINT "Ace"
 2490 PRINT "        ";
 2500 IF B<11 GOTO 2550
 2510 IF B=11 GOTO 2570
 2520 IF B=12 GOTO 2590
 2530 IF B=13 GOTO 2610
 2540 IF B=14 GOTO 2630
 2550 PRINT B
 2560 GOTO 2650
 2570 PRINT "Jack"
 2580 GOTO 2650
 2590 PRINT "Queen"
 2600 GOTO 2650
 2610 PRINT "King"
 2620 GOTO 2650
 2630 PRINT "Ace"
 2650 PRINT
 2660 INPUT "Enter your bet: "; M
 2670 IF M#0 GOTO 2680
 2675 PRINT "Chicken!!":PRINT
 2677 GOTO 2260
 2680 IF M<Q+1 GOTO 2730
 2690 PRINT "Sorry, my friend, but you bet too much."
 2700 PRINT "You have only ";Q;" dollars to bet."
 2710 GOTO 2650
 2730 C=RND(13)+2
 2740 PRINT "        ";
 2760 IF C<11 GOTO 2810
 2770 IF C=11 GOTO 2830
 2780 IF C=12 GOTO 2850
 2790 IF C=13 GOTO 2870
 2800 IF C=14 GOTO 2890
 2810 PRINT C
 2820 GOTO 2910
 2830 PRINT "Jack"
 2840 GOTO 2910
 2850 PRINT "Queen"
 2860 GOTO 2910
 2870 PRINT "King"
 2880 GOTO 2910
 2890 PRINT "Ace"
 2910 IF C>A GOTO 2930
 2920 GOTO 2970
 2930 IF C>B-1 GOTO 2970
 2950 PRINT "You win!"
 2960 GOTO 2210
 2970 PRINT "Sorry, you lose."
 2980 IF M<Q GOTO 2240
 3000 PRINT
 3010 PRINT "Sorry, friend, but you blew your wad."
 3020 PRINT
 3030 PRINT "Do you want to try again?"
 3040 PRINT "Enter 1 to play again or 2 to play a different game."
 3050 INPUT "Enter your choice: "; I
 3060 IF I=1 GOTO 2110
 3070 IF I=2 GOTO 1000
 3080 GOTO 3040
 4000 REM  Trap
 4160 PRINT "I will think of a number from 1 to 100."
 4170 PRINT "Try to guess my number. Enter two numbers, trying"
 4180 PRINT "to trap my number by your two trap numbers. I'll"
 4190 PRINT "tell you if you have trapped my number or if my"
 4200 PRINT "number is smaller than your two trap numbers or"
 4210 PRINT "if my number is larger than your two trap numbers."
 4220 PRINT "If I tell you that you have trapped my number, I"
 4230 PRINT "mean that my number is BETWEEN your trap numbers"
 4240 PRINT "or perhaps my number is the same as one of your"
 4250 PRINT "trap numbers."
 4260 PRINT
 4270 PRINT "IMPORTANT!!  If you think you know my number, then"
 4280 PRINT "enter your guess for BOTH trap numbers."
 4290 PRINT
 4300 X=RND(100)
 4310 PRINT "I'm thinking...thinking...Ah! I have a number!"
 4320 K=1
 4330 PRINT
 4340 INPUT "First trap number: "; A
 4360 INPUT "Second trap number: "; B
 4371 Y=X-A
 4372 IF Y<0 Y=-1
 4373 IF Y>0 Y=1
 4374 Z=X-B
 4375 IF Z<0 Z=-1
 4376 IF Z>0 Z=1
 4380 T=Y+Z
 4390 IF T=-2 GOTO 4430
 4391 IF T=-1 GOTO 4410
 4392 IF T=0 GOTO 4400
 4393 IF T=1 GOTO 4410
 4394 IF T=2 GOTO 4450
 4400 IF A=B GOTO 4480
 4410 PRINT "My number is trapped by your numbers."
 4420 GOTO 4460
 4430 PRINT "My number is smaller than your trap numbers."
 4440 GOTO 4460
 4450 PRINT "My number is larger than your trap numbers."
 4460 K=K+1
 4470 GOTO 4330
 4480 PRINT "You got it in ";K;" guesses!!"
 4485 PRINT
 4490 PRINT "Do you want to play again?"
 4500 INPUT "Type 1 to play again or 2 to play a different game: "; I
 4510 IF I=1 GOTO 4290
 4520 IF I=2 GOTO 1000
 4530 GOTO 4500
 5000 REM  Slots
 5100 PRINT
 5120 PRINT "This is a simulation of a slot machine using a computer."
 5130 PRINT "Each time you 'pull' I will ask you if you wish to play again."
 5140 PRINT "Just answer with a '1' for yes and a '0' for no."
 5150 PRINT "Please place 4 quarters on my keyboard for each play."
 5160 B=0
 5170 PRINT
 5180 D=RND(8)
 5181 E=RND(7)
 5182 F=RND(7)
 5201 IF D=1 GOTO 5211
 5202 IF D=2 GOTO 5213
 5203 IF D=3 GOTO 5215
 5204 IF D=4 GOTO 5217
 5205 IF D=5 GOTO 5219
 5206 IF D=6 GOTO 5221
 5207 IF D=7 GOTO 5223
 5208 IF D=8 GOTO 5226
 5211 PRINT "  BELL ";
 5212 GOTO 5231
 5213 PRINT "  BAR  ";
 5214 GOTO 5231
 5215 PRINT " CHERRY";
 5216 GOTO 5231
 5217 PRINT " APPLE ";
 5218 GOTO 5231
 5219 PRINT " LEMON ";
 5220 GOTO 5231
 5221 PRINT "  $$$  ";
 5222 GOTO 5231
 5223 PRINT " CHERRY";
 5224 D=3
 5225 GOTO 5231
 5226 PRINT " CHERRY";
 5227 D=3
 5231 IF E=1 GOTO 5241
 5232 IF E=2 GOTO 5243
 5233 IF E=3 GOTO 5245
 5234 IF E=4 GOTO 5247
 5235 IF E=5 GOTO 5249
 5236 IF E=6 GOTO 5251
 5237 IF E=7 GOTO 5253
 5241 PRINT "  BELL ";
 5242 GOTO 5261
 5243 PRINT "  BAR  ";
 5244 GOTO 5261
 5245 PRINT " CHERRY";
 5246 GOTO 5261
 5247 PRINT " APPLE ";
 5248 GOTO 5261
 5249 PRINT " LEMON ";
 5250 GOTO 5261
 5251 PRINT "  $$$  ";
 5252 GOTO 5261
 5253 PRINT " CHERRY";
 5254 E=3
 5261 IF F=1 GOTO 5271
 5262 IF F=2 GOTO 5273
 5263 IF F=3 GOTO 5275
 5264 IF F=4 GOTO 5277
 5265 IF F=5 GOTO 5279
 5266 IF F=6 GOTO 5281
 5267 IF F=7 GOTO 5283
 5271 PRINT "  BELL ";
 5272 GOTO 5410
 5273 PRINT "  BAR  ";
 5274 GOTO 5410
 5275 PRINT " CHERRY";
 5276 GOTO 5410
 5277 PRINT " APPLE ";
 5278 GOTO 5410
 5279 PRINT " LEMON ";
 5280 GOTO 5410
 5281 PRINT "  $$$  ";
 5282 GOTO 5410
 5283 PRINT " CHERRY";
 5284 F=3
 5410 IF D#E GOTO 5440
 5420 IF E=F GOTO 5530
 5430 IF D=E GOTO 5460
 5440 IF D#F GOTO 5490
 5450 GOTO 5510
 5460 IF D=1 GOTO 5510
 5461 IF D=3 GOTO 5510
 5462 IF D=5 GOTO 5510
 5463 IF D=7 GOTO 5510
 5470 B=B+5
 5475 PRINT " Keno...You win $5...Total = $";B;
 5480 GOTO 5550
 5490 B=B-1
 5495 PRINT " You have lost $1 -- Total = $";B;
 5500 GOTO 5550
 5510 B=B+1
 5515 PRINT " You have won $1 -- Total = $";B;
 5520 GOTO 5550
 5530 IF D=2 GOTO 5540
 5531 IF D=6 GOTO 5545
 5535 B=B+20
 5536 PRINT " Jackpot...$20...Total = $";B;
 5537 GOTO 5550
 5540 B=B+50
 5541 PRINT " Jackpot...$50...Total = $";B;
 5542 GOTO 5550
 5545 B=B+100
 5546 PRINT " Jackpot...$100...Total = $";B;
 5550 INPUT " Again? (1=Y, 0=N) "; I
 5561 IF I>1 GOTO 5550
 5562 IF I=1 GOTO 5170
 5565 PRINT
 5570 PRINT "It's been nice operating for you - come back soon!"
 5571 PRINT
 5575 GOTO 1000
