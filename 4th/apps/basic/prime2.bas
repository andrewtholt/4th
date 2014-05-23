10 REM Find the first 1000 prime numbers in Vanilla Flavour
20 REM P is a prime number candidate
30 REM N is used to test primacy
40 REM Z is the count of prime numbers found
50 REM F is used to count the factors found of the prime candidate
60 REM A.F.Lack, 8th Oct 2012
100 let z=0
110 let p=3
120 let l=1
150 z=z+1: print z,") ",2," is prime"
200    let f=0
300    for n=2 to (p-1)
400       if p%n=0 then f=f+1
500    next n
600    if f=0 then z=z+1: print z,") ",P," is prime"
700    p=p+2	: REM the next candidate
800 if z<1000 goto 200
999 stop