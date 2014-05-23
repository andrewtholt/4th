Rem Produce a graphical or ASCII-art representation of a Sierpinski carpet
Rem of order N.
Rem uBasic version, 2013 J.L. Bezemer

Input "Carpet order: ";n

l = (3^n) - 1
For i = 0 To l
  For j = 0 To l
    Push i,j
    Gosub 100
    If Pop() Then
      Print "#";
    Else
      Print " ";
    EndIf
  Next
  Print
Next
End

100 y = Pop(): x = Pop() : Push 1

    Do While (x > 0) * (y > 0)
      If (x % 3 = 1) * (y % 3 = 1) Then
         Push (Pop() - 1)
         Break
      EndIf
      y = y / 3
      x = x / 3
    Loop

    Return
