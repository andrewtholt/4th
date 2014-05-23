REM This was written in response to a question on an internet discussion
REM group about the focal length of a perfect sphere, for paraxial rays.
REM It solves the case of a two-surface thick lens, with possibly different
REM refractive indices on either side.

1 REM THICKLEN.BAS Thick Lens, by Donald E. Simanek, April 2, 1995.
2 PRINT 
3 PRINT "    B    A     B-A"
4 PRINT "    -- = -- + -----      (Cartesian sign convention)"
5 PRINT "    Q    P      R"
6 PRINT
7 PRINT "This program solves a two-surface thick lens, using equation above."
8 PRINT "Use cartesian coordinates for positions of vertices and objects."
9 PRINT
10 INPUT "Index of refraction of first medium ", A
11 INPUT "Index of refraction of second medium ", B
12 INPUT "Index of refraction of third medium ", C
13 PRINT
20 INPUT "Position of first surface vertex ", D
21 INPUT "Position of second surface vertex ", E 
22 PRINT
23 INPUT "Radius of first surface ", F
24 INPUT "Radius of second surface ", G
25 PRINT
26 PRINT "Enter zero at the next prompt for an object at infinity."
27 INPUT "Position of object ", H
28 IF H=0 THEN PRINT "Object distance is infinite." 
29 I=0 
30 GOTO 40
31 J = H-D 
35 I = A/J
40 K = I + (B-A)/F
41 L = B/K
45 T = E-D
46 PRINT 
47 PRINT "RESULTS:"
48 PRINT
49 PRINT "Image from first surface is "; L ;" from the first surface."
50 M = L-T
51 PRINT "Image from first surface is "; M ;" from the second surface."
52 N = B/M
55 O = N + (C-B)/G
60 P = C/O
70 PRINT "The final image is at "; E+P
71 PRINT "It is "; P+T; " from the first surface."
72 PRINT "It is "; P; " from the second surface."
80 END
