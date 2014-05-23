rem Print pi to 71 decimal places (72 digits)
rem See https://cs.uwaterloo.ca/~alopez-o/math-faq/mathtext/node12.html
rem Note: c must be a multiple of 14

a=10000 : c=252

for b=0 to c-1
    let @(b) = a/5
next

for d=0
    g=c*2
while g>0

    for b=c
        d=d+@(b)*a
        g=g-1 : @(b)=d%g
        d=d/g : g=g-1
        b=b-1
    while b>0
        d=d*b
    next

    c=c-14

    rem print value (e+d/a) in 4 spaces with leading zeros

    z=e+d/a

    if z=0 then
       print "0000";
    else if (z<10) then
       print "000";z;
    else if (z<100) then
       print "00";z;
    else if (z<1000) then
       print "0";z;
    else
       print z;
    endif endif endif endif

    e=d%a
next

print
stop