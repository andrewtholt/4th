Rem Example from: FreeBASIC Primer #1
Rem http://www.freebasic.net/wiki/wikka.php?wakka=ProPgPrimer1
Rem uBasic version, 2013, J.L. Bezemer 

Print "This program will calculate the sum and average for a"
Print "list of numbers. Enter a zero value to end."
Print

Do
  Input "Enter a number: ", a
While a#0
  c = c + 1
  t = t + a
Loop

Print
Print "You entered "; c; " numbers"
Print "The sum is "; t

If c # 0 Then
  Print "The average is "; t / c
EndIf