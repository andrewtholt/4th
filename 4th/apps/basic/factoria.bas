 10 REM This example shows you how a stack can enhance an ancient
 20 REM programming language like Minimal Basic. It calculates 10!
 30 REM using a recursive algorith, something that is very hard to
 40 REM do without a stack and simply impossible without an array.
 50 REM uBasic version, Hans Bezemer, 2013
 60 REM
 70 print "Factorial of 10: "; : push (10) : gosub 100 : print pop() : end
100 if tos()=1 then return
110 push (tos()-1) : gosub 100 : push (pop()*pop()) : return