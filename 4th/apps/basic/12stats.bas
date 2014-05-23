Rem Given the following twelve statements, which of them are true?

Rem 1.  This is a numbered list of twelve statements.
Rem 2.  Exactly 3 of the last 6 statements are true.
Rem 3.  Exactly 2 of the even-numbered statements are true.
Rem 4.  If statement 5 is true, then statements 6 and 7 are both true.
Rem 5.  The 3 preceding statements are all false.
Rem 6.  Exactly 4 of the odd-numbered statements are true.
Rem 7.  Either statement 2 or 3 is true, but not both.
Rem 8.  If statement 7 is true, then 5 and 6 are both true.
Rem 9.  Exactly 3 of the first 6 statements are true.
Rem 10.  The next two statements are both true.
Rem 11.  Exactly 1 of statements 7, 8 and 9 are true.
Rem 12.  Exactly 4 of the preceding statements are true.

S = 12
For T = 0 To (2^S)-1

  For I = 1 To 12
      Push T, 2^(I-1) : Gosub 100
      @(I) = Pop() # 0
  Next

  REM Test consistency:

  @(101) = @(1)  = (S = 12)
  @(102) = @(2)  = ((@(7)+@(8)+@(9)+@(10)+@(11)+@(12)) = 3)
  @(103) = @(3)  = ((@(2)+@(4)+@(6)+@(8)+@(10)+@(12)) = 2)
  @(104) = @(4)  = ((@(5)=0) + (@(6) * @(7)) # 0)
  @(105) = @(5)  = ((@(2)=0) * (@(3)=0) * (@(4)=0))
  @(106) = @(6)  = ((@(1)+@(3)+@(5)+@(7)+@(9)+@(11)) = 4)
  @(107) = @(7)  = ((@(2) + @(3)) = 1)
  @(108) = @(8)  = ((@(7)=0) + (@(5) * @(6)) # 0)
  @(109) = @(9)  = ((@(1)+@(2)+@(3)+@(4)+@(5)+@(6)) = 3)
  @(110) = @(10) = (@(11) * @(12))
  @(111) = @(11) = ((@(7)+@(8)+@(9)) = 1)
  @(112) = @(12) = ((@(1)+@(2)+@(3)+@(4)+@(5)+@(6)+@(7)+@(8)+@(9)+@(10)+@(11)) = 4)

  Q = 0
  For I = 101 To 112
      Q = Q + @(I)
  Next

  If (Q = 11) Then
     Print "Near miss with statements ";
     For I = 1 To 12
       If @(I) Then
          Print I; " ";
       Endif
       If (@(I+100) = 0) Then
          M = I
       Endif
     Next
     Print "true (failed " ;M; ")."
  Endif

  If (Q = 12) Then
     Print "Solution! with statements ";
     For I = 1 TO 12
       If @(I) Then
          Print I; " ";
       Endif
     Next
     Print "true."
  Endif

Next
End

100 Rem a hard way to do a binary AND
    q = Pop() : p = Pop() : Push 0

    Do While (p * q) * (Tos() = 0)
       Push Pop() + (p % 2) * (q % 2)
       p = p / 2
       q = q / 2
    Loop

    Return