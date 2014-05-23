10 rem find the pirate treasure
30 T = 0
100 rem beach
101 print "           |"
102 print "         \\ _ /"
103 print "       -= (_) =-"
104 print "         /   \\         _\\/_"
105 print "           |           //o\\  _\\/_"
106 print "    _____ _ __ __ ____ _ | __/o\\\\ _"
107 print "  =-=-_-__=_-= _=_=-=_,-'|' ''-|-,_"
108 print "   =- _=-=- -_=-=_,-''|''"
109 print "     =- =- -=.--' '"
110 print "You are standing on the beach.  Sand and water stretch in all directions."
120 print "You see a boat farther along the shore and a clearing through the forest."
130 print "(boat - clearing) ";
150 input "boat=0 clearing=1 hill=2 beach=3 tree=4 rock=5 dig=6 hide=7 ";C
160 if C = 0 then goto 800
170 if C = 1 then goto 300
180 goto 130
300 rem clearing
310 print
320 print "You are in the clearing of the forest.  You see a hill ahead of you and the beach behind you."
330 print "There is also a tree you could probably climb, if the pirates don't see you!"
335 if T = 1 then print "(hill - beach - tree - rock) ";
340 if T = 0 then print "(hill - beach - tree) ";
350 input "boat=0 clearing=1 hill=2 beach=3 tree=4 rock=5 dig=6 hide=7 ";C
360 if C = 2 then goto 400
370 if C = 3 then goto 100
380 if C = 4 then goto 500
385 if (C = 5) * (T = 1) then goto 600
390 goto 335
400 rem hill
410 print
420 print "You are standing on a hill.  There is a clearing behind you."
430 print "There is also a funny-shaped rock below you, but you can't see how to get to it."
440 print "(clearing) ";
450 input "boat=0 clearing=1 hill=2 beach=3 tree=4 rock=5 dig=6 hide=7 ";C
460 if C = 1 then goto 300
470 goto 440
500 rem tree
505 print
510 print "You climb the tree carefully.  It's pretty high and you get a little scrapped up."
520 print "When you get to the top, you see a skull-shaped rock. It looks easy to get to."
530 T = 1
540 print "(clearing) ";
550 input "boat=0 clearing=1 hill=2 beach=3 tree=4 rock=5 dig=6 hide=7 ";C
560 if C = 1 then goto 300
570 goto 800
600 rem skull rock
605 print
610 print "You made it to skull rock.  You see the large 'X' in the sand."
620 print "It is getting a little dark though.  Maybe you should dig for the treasure tomorrow."
630 print "(dig - hide) ";
640 input "boat=0 clearing=1 hill=2 beach=3 tree=4 rock=5 dig=6 hide=7 ";C
650 if C = 6 then goto 700
660 if C = 7 then goto 800
670 goto 630
700 rem treasure
701 print "         __________"
702 print "        /\\____;;___\\"
703 print "       | /         /"
704 print "       `. ())oo() ."
705 print "        |\\(%()*^^()^\\"
706 print "       %| |-%-------|"
707 print "      % \\ | %  ))   |"
708 print "      %  \\|%________|"
709 print "       %%%%"
710 print "Yeah!"
720 print "You got the treasure!"
730 print "Way to go!"
740 end
800 rem pirates
801 print "        {}  _---_  {}"
802 print "          \\/     \\/ "
803 print "           |() ()| "
804 print "            \\ + /  "
805 print "           / HHH  \\"
806 print "         {}  \\_/   {}"
810 print "Oh no!"
820 print "The pirates found you!"
830 end