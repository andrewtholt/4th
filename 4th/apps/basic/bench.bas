REM Based on a benchmark by Christopher W. Cowell-Shah, Copyright 2004
REM uBasic version by J.L. Bezemer, Copyright 2009
    A = 1
    B = 1
    C = 1000000
200 A=A-B
    B=B+1
    A=A+B
    B=B+1
    A=A*B
    B=B+1
    A=A/B
    B=B+1
    IF B < C THEN GOTO 200
