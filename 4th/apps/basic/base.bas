Rem convert a decimal number to any base
Rem uBasic version, 2013, Hans Bezemer

Do
  Input "Enter base (<17): "; b
  While (b < 1) + (b > 16)
Loop

Input "Enter number: "; n
s = (n < 0)                            : Rem save the sign
n = Abs(n)                             : Rem make number unsigned

For x = 0 Step 1 Until n = 0           : Rem calculate all the digits
    @(x) = n % b
    n = n / b
Next x

If s Then Print "-";                   : Rem reapply the sign

For y = x - 1 To 0 Step -1             : Rem print all the digits
    If @(y) > 9 Then                   : Rem take care of hexadecimal digits
       Gosub @(y) * 10
    Else
       Print @(y);                     : Rem print "decimal" digits
    Endif
Next y

Print                                  : Rem finish the string
End

100 Print "A"; : Return                : Rem print hexadecimal digit
110 Print "B"; : Return
120 Print "C"; : Return
130 Print "D"; : Return
140 Print "E"; : Return
150 Print "F"; : Return
