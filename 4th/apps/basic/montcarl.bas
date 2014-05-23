REM A Monte Carlo Simulation is a way of approximating the value of a function
REM where calculating the actual value is difficult or impossible. It uses
REM random sampling to define constraints on the value and then makes a sort of
REM "best guess."

REM A simple Monte Carlo Simulation can be used to calculate the value for PI.
REM If you had a circle and a square where the length of a side of the square
REM was the same as the diameter of the circle, the ratio of the area of the
REM circle to the area of the square would be PI/4. So, if you put this circle
REM inside the square and select many random points inside the square, the
REM number of points inside the circle divided by the number of points inside
REM the square and the circle would be approximately PI/4.

PRINT "This will take a while. Patience.."

PUSH 1000 : GOSUB 10 : PRINT POP()
PUSH 10000 : GOSUB 10 : PRINT POP()
PUSH 100000 : GOSUB 10 : PRINT POP()
PUSH 1000000 : GOSUB 10 : PRINT POP()
END

10 N = 0
   FOR i = 1 TO POP()
     IF RND(10000)^2 + RND(10000)^2 < 10000^2 THEN N=N+1
   NEXT

   PUSH 4 * N
   RETURN