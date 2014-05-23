REM Program name: Factors
print "Choose an integer greater than one"
print "to find all of its factors"
input N
for I = 1 to N
if N%I = 0 then print I
next
print "are the factors of ";N
end
