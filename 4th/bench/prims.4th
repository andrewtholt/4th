\ Based on a benchmark by Phil Burk

[needs lib/timer.4th]

\ benchmark primitives
100000000 constant #do

create data_@c data_@c ,
variable data_@ data_@ data_@ !
: foo ( noop ) ;

: stopwatch depth 1- 0 ?do drop loop .elapsed cr timer-reset ;

: t1           #do 0      do                         loop ;
: t2  23 45    #do 0      do  swap                   loop ;
: t3  23       #do 0      do  dup drop               loop ;
: t4  23 45    #do 0      do  over drop              loop ;
: t5  23       #do 0      do  dup +                  loop ;
: t6  23       #do 0      do  >r r>                  loop ;
: t7  23 45 67 #do 0      do  rot                    loop ;
: t8  23       #do 0      do  2*                     loop ;
: t9  data_@   #do 0      do  @                      loop ;
: t10 data_@c  #do 0      do  @c                     loop ;
: t11          #do 0      do  foo                    loop ;
: t12          #do 0      do  23 drop                loop ;
: t13 data_@   #do 0      do  dup dup !              loop ;

timer-reset
." PRIMITIVES" cr
t1
." empty         : " stopwatch
t2
." swap          : " stopwatch
t3
." dup drop      : " stopwatch
t4
." over drop     : " stopwatch
t5
." dup +         : " stopwatch
t6
." >r r>         : " stopwatch
t7
." rot           : " stopwatch
t8
." 2*            : " stopwatch
t9
." @             : " stopwatch
t10
." @c            : " stopwatch
t11
." call          : " stopwatch
t12
." 23 drop       : " stopwatch
t13
." dup dup !     : " stopwatch drop




