REM Find the first 1000 prime numbers
REM See http://primes.utm.edu/lists/small/1000.txt
REM P is a prime number candidate
REM N is used to test primacy
REM Z is the count of prime numbers found
REM F is used to count the factors found of the prime candidate
REM A.F.Lack, 8th Oct 2012

let z=0
for p=3 step 2
    let f=0
    for n=2 to (p-1)
        if p%n=0 then f=f+1: break
    next n
    if f=0 then print z;") ";P;" is prime" : z=z+1
    if z>1000 then break
next
stop