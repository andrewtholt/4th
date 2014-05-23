Rem "Not One" for uBasic, J.L. Bezemer 2013

Print "The game of 'Notone' is played with two players and a pair of dice."
Print "There are ten rounds in the game. One round consisting of one turn"
Print "for each player. Players (yourself and the computer) add the score"
Print "they attain on each round. And the player with the highest score"
Print "after ten rounds is the winner."
Print
Print "On each turn the player may roll the two dice from 1 to n times. If"
Print "T1 is the total of dice on the Ith roll, then the players score for"
Print "the turn is T(1)+T(2)+T(3)+..T(N)."
Print
Print "However, and here's the catch. If any T(I)is equal to T(1) then the"
Print "turn is over and his score for that round is zero. After each roll"
Print "that doesn't equal T(1), the player can decide whether to roll again"
Print "or stop and score the number of points already obtained."
Print

P = 0 : C = 0                         : Rem set up the scores

For X = 1 To 10                       : Rem for 10 rounds
  Print "Round ";X : Print
  Gosub 120                           : Rem Your turn
  Gosub 130                           : Rem The computers turn
Next X

Print "Final score","You","Computer"  : Rem Print final score
Print "Total points:", P, C

End

100 Do                                 : Rem get confirmation
      Input "Roll again? (Yes=1, No=0): "; A
      Until (A=0)+(A=1)
    Loop
    Return

110 Push (Rnd(6)+1)+(Rnd(6)+1)         : Rem Roll two dice
    Return

120 Print "Your turn:"                 : Rem Players turn
    Gosub 110 : M = Pop() : R = M : Print M
                                       : Rem Set up initial result
    Do
      Gosub 100                        : Rem Ask for another one
      Until A = 0                      : Rem Not another roll

      Gosub 110 : T = Pop() : Print T  : Rem Roll the dice

      If T = M Then                    : Rem If failed ..
        R = 0                          : Rem Set result to zero
        Print "You get a zero for this round."
      Else                             : Rem Otherwise
        R = R + T                      : Rem Add to the result
      Endif

      Until T = M                      : Rem We failed ..
    Loop

    P = P + R                          : Rem Add the result to score
    Print "You got ";P;" points."      : Rem Print the score
    Print : Return

130 Print "Computers turn:"            : Rem computers turn
    Gosub 110 : M = Pop() : R = M : I = 1
    Print "Computer's roll ";I;" : ";M

    If (C + 36) < P Then               : Rem If computer is behind
       Y = 7 + Rnd(2) + 2 * ((M < 4) + (M > 10))
    Else                               : Rem Then a bit more aggressive
       Y = 5 + Rnd(2) + 2 * ((M < 4) + (M > 10))
    Endif                              : Rem Take chances of T(1) into account

    Do Until I = Y                     : Rem Now apply the "strategy"

      I = I + 1 : Gosub 110 : T = Pop()
      Print "Computer's roll ";I;" : ";T
                                       : Rem Roll the dice
      If T = M Then                    : Rem If failed ..
        R = 0                          : Rem Set result to zero
        Print "The computer gets a zero for this round."
      Else                             : Rem Otherwise
        R = R + T                      : Rem Add to the result
      Endif

      Until T = M                      : Rem We failed ..
    Loop

    C = C + R                          : Rem Add the result to score
    Print "The computer got ";C;" points."
    Print : Return                     : Rem Print the score