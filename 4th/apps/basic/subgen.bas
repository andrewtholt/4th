Rem "Subtractive Random Generator" for uBasic, J.L. Bezemer 2014

Rem A subtractive generator calculates a sequence of random numbers,
Rem where each number is congruent to the subtraction of two previous
Rem numbers from the sequence.

Rem The subtractive generator has a better reputation than the linear
Rem congruential generator, perhaps because it holds more state. A
Rem subtractive generator might never multiply numbers: this helps where
Rem multiplication is slow.

Rem All subtractive generators have some weaknesses. Anyone who observes
Rem i consecutive numbers can predict the next numbers, so the generator
Rem is not cryptographically secure. The authors of Freeciv and xpat2
Rem knew another problem: the low bits are less random than the high bits.

Push 292929 : Gosub 100 : d = Pop()

For i = 1 To 10
  Push 0 : Gosub 100
  Print Pop()
Next

End

100 s = Pop()
    If s = 0 Then
       p = (p + 1) % 55
       @(p) = @(p) - @((p + 31) % 55)
       If @(p) < 0 Then
          @(p) = @(p) + 1000000000
       Endif
       Push (@(p)) : Return
    Endif

    @(54) = s : @(33) = 1
    p = 12

    For i = 2 To 54
      @(p) = @((p + 42) % 55) - @((p + 21) % 55)
      If @(p) < 0 Then
          @(p) = @(p) + 1000000000
      Endif
      p = (p + 34) % 55
    Next

    For i = 55 To 219
        Push 0 : Gosub 100 : d = Pop()
    Next

    Push 0 : Return
