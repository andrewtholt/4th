100 rem initialize
110 a=1+(rnd(32767)%8)
120 b=1+(rnd(32767)%8)
130 if b=a then goto 120
140 c=1+(rnd(32767)%8)
150 if c=a then goto 140
160 if c=b then goto 140
170 d=a*100+b*10+c
190 rem print d
300 rem now get user input for code until code is broken
310 rem variable a contains the right digits at right position count
320 rem if a=3 then code is broken. variable b contains
330 rem the right digit but wrong position count
350 print "Hi, try to break my 3-digit code..."
360 print "No zeros, no duplicate digits."
400 rem now get used input
410 input "Code: "; e
415 if e>122 then goto 420
416 if e<988 then goto 420
417 print "Error: Input must be between 123 and 987. Try again"
418 goto 410
420 a=0
430 b=0
500 rem now check the code against the input and update variable a and b
505 if e=d then goto 700
510 k=d/100
515 l=(d/10)%10
520 m=d%10
525 o=e/100
530 p=(e/10)%10
535 q=e%10
550 if k=o then a=a+1
551 if l=p then a=a+1
552 if m=q then a=a+1
560 if k=p then b=b+1
561 if k=q then b=b+1
563 if l=o then b=b+1
564 if l=q then b=b+1
565 if m=p then b=b+1
566 if m=o then b=b+1
600 print "Right digit / right position=";a;"; right digit / wrong position=";b
605 rem input x
610 if a<3 then goto 410
700 rem code broken
710 print "Hurray, you broke the code!"
720 stop
