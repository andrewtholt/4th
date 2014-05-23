\ 4tH pipes demonstration program
\ Copyright 2002,2008 J.L. Bezemer

\ WARNING: Do not use this program if
\ you don't want the root user to
\ get email!!!

s" ls"        input  pipe + open error? >r to ls
s" mail root" output pipe + open error? >r to mail
r> r> or abort" Cannot open pipe"

ls   use
mail use

." 4tH demonstration program - please ignore!!!" cr
." These are the contents of my current working directory:"
cr cr

begin
  refill
while
  0 parse type cr
repeat

ls   close
mail close

