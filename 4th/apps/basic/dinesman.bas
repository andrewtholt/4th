REM Baker, Cooper, Fletcher, Miller, and Smith live on different floors of an
REM apartment house that contains only five floors. Baker does not live on the
REM top floor. Cooper does not live on the bottom floor. Fletcher does not
REM live on either the top or the bottom floor. Miller lives on a higher floor
REM than does Cooper. Smith does not live on a floor adjacent to Fletcher's.
REM Fletcher does not live on a floor adjacent to Cooper's. Where does everyone
REM live?

REM Floors are numbered 0 (ground) to 4 (top)

FOR B = 0 TO 4
  FOR C = 0 TO 4
    FOR F = 0 TO 4
      FOR M = 0 TO 4
        FOR S = 0 TO 4
          GOSUB 100 : IF POP() THEN
            GOSUB 110 : IF POP() THEN
              GOSUB 120 : IF POP() THEN
                GOSUB 130 : IF POP() THEN
                  GOSUB 140 : IF POP() THEN
                    GOSUB 150 : IF POP() THEN
                      GOSUB 160 : IF POP() THEN
                        PRINT "Baker lives on floor " ; B + 1
                        PRINT "Cooper lives on floor " ; C + 1
                        PRINT "Fletcher lives on floor " ; F + 1
                        PRINT "Miller lives on floor " ; M + 1
                        PRINT "Smith lives on floor " ; S + 1
                      ENDIF
                    ENDIF
                  ENDIF
                ENDIF
              ENDIF
            ENDIF
          ENDIF
        NEXT S
      NEXT M
    NEXT F
  NEXT C
NEXT B

END

REM "Baker, Cooper, Fletcher, Miller, and Smith live on different floors"
100 PUSH (B#C)*(B#F)*(B#M)*(B#S)*(C#F)*(C#M)*(C#S)*(F#M)*(F#S)*(M#S)
    RETURN

REM "Baker does not live on the top floor"
110 PUSH B#4
    RETURN

REM "Cooper does not live on the bottom floor"
120 PUSH C#0
    RETURN

REM "Fletcher does not live on either the top or the bottom floor"
130 PUSH (F#0)*(F#4)
    RETURN

REM "Miller lives on a higher floor than does Cooper"
140 PUSH M>C
    RETURN

REM "Smith does not live on a floor adjacent to Fletcher's"
150 PUSH ABS(S-F)#1
    RETURN

REM "Fletcher does not live on a floor adjacent to Cooper's"
160 PUSH ABS(F-C)#1
    RETURN