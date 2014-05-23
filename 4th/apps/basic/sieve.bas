1 rem     example contributed by H. Kaplan <hmk@nadn.navy.mil>
2 rem
100 rem The famous sieve of Eratosthenes, using the modern features of
110 rem Chipmunk Basic.  This program is written as crudely as possible,
120 rem so as to make the algorithm obvious.
130 rem
140 rem @() marks, 0 for prime and 1 for composite
150 rem
170 let p = 0      : rem no primes found yet
190 let n = 255    : rem how many marks there are
200 rem
210 for j = 2 to n : rem 1 cannot be a prime
220 rem
230 if @(j) = 0
240 let p = p+1    : rem one more prime
250 print j        : rem suppress printing so as to time the program
260 rem
270 for k = j+j to n step j : rem mark the numbers divisible by j
280 let @(k) = 1   : rem k is composite
290 next k
300 rem
310 endif
320 rem
330 next j
340 rem
360 print
370 print "I found ";p;" primes out of ";n;" numbers."
380 end
