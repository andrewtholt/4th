Rem Example from: Wikipedia, QBasic
Rem http://en.wikipedia.org/wiki/QBasic
Rem uBasic version, 2013, J.L. Bezemer 

PRINT "Guess the number!"
INPUT "Would you like to play? (Y=1, N=0): ", c : Rem An input statement, that takes what the user inputs..
IF c = 1 THEN                                   : Rem and decides whether or not you want to play:
  g = 5                                         : Rem Set up number of guess remaining
  t = RND(10) + 1                               : Rem Picks a random number between 1 and 10 (inclusive)
  w = 0                                         : Rem Sets up a flag called 'w' to check if user has won 

  PRINT "The number is between 1 and 10."
  DO WHILE (g > 0) * (w = 0)                    : Rem Enters a loop until the user wins or runs out of chances
    INPUT "Enter your guess: ", u               : Rem Takes user input (the guess)
    IF u = t THEN                               : Rem Determines if the guess was correct
      PRINT "Correct, the answer was "; t; "!"
      w = 1                                     : Rem Sets a flag to indicate user has won
    ELSE
      g = g - 1                                 : Rem Deducts one chance
      PRINT "Sorry, please try again. You have "; g; " guesses left."
    ENDIF
  LOOP                                          : Rem End of guessing loop

  IF w = 0 THEN 
     PRINT "You ran OUT of guesses, the number was "; t; "."
  ENDIF                                         : Rem Print the result
ENDIF