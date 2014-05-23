REM ** Several sorting routines
REM ** Converted to uBasic, J.L. Bezemer, 2013
REM **
REM ** Taken from various Rosetta code examples
REM ** http://rosettacode.org

PRINT "Shellsort:"
GOSUB 200 : PUSH TOS() : GOSUB 210 : PUSH TOS()
GOSUB 100 : GOSUB 210 : PRINT

PRINT "Combsort:"
GOSUB 200 : PUSH TOS() : GOSUB 210 : PUSH TOS()
GOSUB 110 : GOSUB 210 : PRINT

PRINT "Insertion sort:"
GOSUB 200 : PUSH TOS() : GOSUB 210 : PUSH TOS()
GOSUB 120 : GOSUB 210 : PRINT

PRINT "Selection sort:"
GOSUB 200 : PUSH TOS() : GOSUB 210 : PUSH TOS()
GOSUB 130 : GOSUB 210 : PRINT

PRINT "Bubble sort:"
GOSUB 200 : PUSH TOS() : GOSUB 210 : PUSH TOS()
GOSUB 140 : GOSUB 210 : PRINT

PRINT "Gnome sort:"
GOSUB 200 : PUSH TOS() : GOSUB 210 : PUSH TOS()
GOSUB 150 : GOSUB 210 : PRINT

PRINT "Cocktail sort:"
GOSUB 200 : PUSH TOS() : GOSUB 210 : PUSH TOS()
GOSUB 160 : GOSUB 210 : PRINT

END

100 REM Shellsort subroutine
    n = POP ()
    h = n

    DO WHILE h
      h = h / 2
      FOR i = h TO n - 1
        k = @(i)
        j = i
        DO WHILE (j > h-1) * (k < @(ABS(j - h)))
          @(j) = @(j - h)
          j = j - h
        LOOP
        @(j) = k
      NEXT
    LOOP

    RETURN

110 REM Combsort subroutine
    s = POP()
    g = s
    p = 1

    DO WHILE (g > 1) + p

      g = (g * 10) / 13

      IF (g = 9) + (g = 10) THEN
        g = 11
      ENDIF

      IF g < 1 THEN
        g = 1
      ENDIF

      p = 0
      i = 0
      j = g

      DO WHILE j < s
        IF @(i) > @(j) THEN
          PUSH @(i)
          @(i) = @(j)
          @(j) = POP()
          p = 1
        ENDIF

        i = i + 1
        j = j + 1
      LOOP
    LOOP

    RETURN

120 REM Insertion sort
    n = POP()

    FOR i = 1 TO n-1
      t = @(i)
      j = i
      DO WHILE (j>0) * (t < @(ABS(j-1)))
          @(j) = @(j-1)
          j = j - 1
      LOOP
      @(j) = t
    NEXT

    RETURN

130 REM Selection sort
    s = POP()

    FOR i = 0 TO s-1
      l = i

      FOR j = i TO s-1
        IF @(j) < @(l) THEN
          l = j
        ENDIF
      NEXT

      IF i # l THEN
        PUSH @(i)
        @(i) = @(l)
        @(l) = POP()
      ENDIF

    NEXT

    RETURN

140 REM Bubble sort
    n = POP()

    DO
      l = 0
      FOR i = 1 TO n-1
        IF @(i-1) > @(i) THEN
          PUSH @(i-1)
          @(i-1) = @(i)
          @(i) = POP()
          l = i
        ENDIF
      NEXT
      n = l
      UNTIL l = 0
    LOOP

    RETURN

150 REM Gnome sort
    n = POP()
    i=1
    j=2

    DO WHILE i < n
      IF @(i-1) > @(i) THEN
        PUSH @(i-1)
        @(i-1) = @(i)
        @(i) = POP()
        i = i - 1
        IF i THEN
          CONTINUE
        ENDIF
      ENDIF
      i = j
      j = j + 1
    LOOP

    RETURN

160 REM Cocktail sort
    s = POP()
    t = 0

    DO WHILE t = 0
      t = 1
      FOR i=1 TO s-1
        IF @(i) < @(i-1) THEN
          PUSH @(i-1)
          @(i-1) = @(i)
          @(i) = POP()
          t = 0
        ENDIF
      NEXT

      IF t THEN
        BREAK
      ENDIF

      t = 1
      FOR i=s-1 TO 1 STEP -1
        IF @(i) < @(i-1) THEN
          PUSH @(i-1)
          @(i-1) = @(i)
          @(i) = POP()
          t = 0
        ENDIF
      NEXT
    LOOP

    RETURN

200 REM Init example array
    PUSH 4, 65, 2, -31, 0, 99, 2, 83, 782, 1

    FOR i = 0 TO 9
      @(i) = POP()
    NEXT

    PUSH i
    RETURN

210 REM Show array subroutine
    FOR i = 0 TO POP()-1
      PRINT @(i),
    NEXT

    PRINT
    RETURN

