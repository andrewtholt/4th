0001 REM Lyrics of the song 99 Bottles of Beer in Tiny Basic

0005 LET I=99
0006 PRINT "Lyrics of the song 99 Bottles of Beer"

0010 REM main
0011 IF I>2 THEN GOTO 20
0012 IF I=2 THEN GOTO 30
0013 IF I=1 THEN GOTO 40
0014 GOTO 50

0020 REM if greater than two
0021 PRINT I;" Bottles of beer on the wall, ";I;" bottles of beer."
0022 LET I=I-1
0023 PRINT "Take one down and pass it around, ";
0024 PRINT I;" bottles of beer on the wall."
0025 GOTO 10

0030 REM if equals two
0031 PRINT I;" Bottles of beer on the wall, ";I;" bottles of beer."
0032 LET I=I-1
0033 PRINT "Take one down and pass it around, ";
0034 PRINT I;" bottle of beer on the wall."
0035 GOTO 10

0040 REM if equals one
0041 PRINT I;" Bottle of beer on the wall, ";I;" bottle of beer."
0042 LET I=I-1
0043 PRINT "Take one down and pass it around,";
0044 PRINT " no more bottles of beer on the wall."
0045 GOTO 10

0050 REM if equals zero then exit
0051 PRINT "No more bottles of beer on the wall.  No more bottles of beer..."
0052 PRINT "Go to the store and buy some more...99 bottles of beer."
