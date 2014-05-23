Rem Sine Wave
Rem Structured uBasic version, 2013, J.L. Bezemer

q = 10
c = 1000
n = 0

Do
  t = s * 967 / 1000 + c * 249 / 1000
  c = c * 967 / 1000 - s * 249 / 1000
  s = t
  i = 0

  Do
    Print " ";
    i = i + 1
    While i < 28 + 26 * s / 1000
  Loop

  Print "uBasic for 4tH compiler"
  n = n + 1

  If n < 25 Then
     Continue
  EndIf

  n = 0
  s = 0
  c = 1000
  q = q - 1

  While q
Loop
