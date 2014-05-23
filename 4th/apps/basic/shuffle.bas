 10 FOR y = 1 to 52
 20 @(y) = y : NEXT y
 30 REM Pack filled
 50 y = 52
 60 z = rnd(52) + 1
 70 a = @(y) : @(y) = @(z) : @(z) = a
100 y = y - 1 : IF y THEN GOTO 60
105 INPUT "How many cards? ", x
110 REM IF x > 52 THEN x = 52
115 IF x < 1 END
120 PRINT "Here are your cards:"
125 FOR y = 1 TO x
130 PRINT "Card No. ";y;" is ";@(y)
135 NEXT y : GOTO 50