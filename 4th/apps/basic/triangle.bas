Rem Produce a graphical or ASCII-art representation of a Sierpinski triangle
Rem of order N.
Rem uBasic version, 2013 J.L. Bezemer

Input "Triangle order: ";n
n = 2^n

For y = n - 1 To 0 Step -1

  For i = 0 To y
    Print " ";
  Next

  x = 0

  For x = 0 Step 1 While ((x + y) < n)
     Push x,y
     Gosub 100

     If Pop() Then
        Print "  ";
     Else
        Print "* ";
     EndIf
  Next

  Print
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