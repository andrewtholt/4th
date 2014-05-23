REM uBasic WHILE and UNTIL loop demonstration
REM J.L. Bezemer, 2013

input "Factorial: ", n : print

REM ** Using a WHILE loop

a = n : if a < 1 then print 1 : end

for i=1 step 1
    while (i < n - 1)
    a = a * (n - i)
next

print n;"! = ";a;" (using WHILE)"

REM ** Using an UNTIL loop

a = 1

for i=n step -1
    a = a * i
    while (i > 1)
next

print n;"! = ";a;" (using UNTIL)"

