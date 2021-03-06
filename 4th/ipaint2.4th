\ Paint program for bitmap ppm images in 4tH 
\ David Johnson, May 2012 
\ Cursor movement is taken from a user string with
\    i,m = up/down  j,k = left right
\ ======================================================================
\ Simple example of a few commands:
\   150 200 new_color          Define the new image
\   blue                       Set the pen color to blue
\   fr kkkkmmmm                Shift window 3 increments left and 4 down
\   dr .....xxxxxxxxxx         Draw line: 5 pixels no draw: 10 pixels draw
\   nd .....x........x         Next line: color in two pixel
\   nd .....xxxxxxxxxx         Next line: finish bottom of the box
\   sk ukkkkkkkkkki            Sketch: pen_up, move 10 left and 1 up.
\   sk dgmmmmmkkkkkiiiiijjjjj  Sketch: Pen_down, green, draw a box.
\   n n n n htext "test"       Move down 4 lines and write text
\   home n l                   List the second line
\   red                        Set pen to red
\   dr .........x              draw  one red pixel in  of middle box
\   show                       Show the results
\   isave test.ppm             Save the bitmap image.
\ =======================================================================
\ Example 2: modify an ppm file
\ file portrait.ppm            Load the picture 
\ shrink shrink                Reduce the image by 4x (2x 2x)
\ grayscale info               Convert the image to grayscale
\ 117 width  40 height         Define the viewing/drawing frame
\ 0 50 xy                      Move the viewing frame
\ home                         Home the graphics cursor 
\ penup                        Do not draw wheh moving the cursor 
\ sk mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm (30 m's) Move the cursor down  
\ vtext Hans                   Write "HANS" on image
\ isave Hans.ppm               Save the modified image
\ quit                         Bye
\ ========================================================================


 
include lib/interprt.4th 
include lib/row.4th 
include lib/anstools.4th   \ for .s in the calculator 
 
include lib/graphics.4th    
include lib/gview.4th 
include lib/gshrink.4th 
include lib/gcol2gry.4th
include lib/gbanner.4th
 
variable reduction    1 reduction !   \ count the times image is shrunk 
variable iwidth       \ image width 
variable iheight      \ image height 
1 value draw?         \ Note if the brush or pen on the canvis! 
 
81 string gfile       \ graphics file 
256 string paint$ 
 
70 constant default_width    \ Assuming standard text display 
22 constant default_height 
 
\ Must define the 'NotFound' for interprt.4th 
:noname 2drop ." Not found!" cr ; is NotFound 
 
: defaults ( -- ) 
    0 0 view_from 
    0 cursor_x !  0 cursor_y ! ;
 
: pen_up 0 to draw? ; 
: pen_down 1 to draw? ; 
 
\ Drawing primatives 
: plot ( -- )  draw? if  cursor_y @ cursor_x @  set_pixel then ; 
: <down> ( -- )  1 cursor_y +! ;
: down ( -- )  plot <down> ; 
: <up> ( -- )  cursor_y @ 1-  current_view nip  max cursor_y ! ; 
: up ( -- )  plot <up> ; 
: <left> ( -- )  cursor_x @ 1-  current_view drop  max cursor_x ! ; 
: left ( -- )  plot <left> ; 
: <right> ( -- ) 1 cursor_x +! ;
: right ( -- )  plot <right> ; 
: home ( -- )  current_view cursor_y !  cursor_x ! ;
: gcls ( -- )  255 whiteout  home black ; 
 
\ set the pen color to match the pixel color on the image 
: cmatch ( -- ) 
    cursor_y @  cursor_x @  pixel@
    intensity! ; 
 
\ Draw the picture capturing the cursor and editing 
\ the keystrokes in a single string.
 
: get_string ( -- a n) 
  0 parse-word dup 0=                 \ parse the filename 
  if 1 throw then ;           \ if no filename throw exception 
  
 create paint_keys 
  char i ,    ' up ,     \ arrow keys: will draw with pen_down
  char m ,    ' down ,
  char j ,    ' left ,
  char k ,    ' right ,
  char . ,    ' <right> ,  \ only cursor movement; no drawing
  char x ,    ' right ,
  char d ,    ' pen_down ,
  char u ,    ' pen_up ,
  char b ,    ' black ,    \ set pen color on the fly
  char z ,    ' blue ,
  char c ,    ' cyan ,
  char r ,    ' red ,
  char p ,    ' magenta ,
  char y ,    ' yellow ,
  char g ,    ' green ,
  char w ,    ' white ,
  null , 
 
: do_keys (  c -- ) 
       paint_keys 2 num-key  row if 
        cell+ @c execute 
      then drop ;
 
: sketch ( -- )
     get_string paint$ place 
     paint$ count 
     0 do
        paint$ i +  c@ do_keys 
     loop drop ;

: cursor_return ( -- )  \ move the cursor to left edge of frame
     current_view drop cursor_x ! ;  

: line_ ( -- )   \ show the current line of ascii image
    4 spaces  cursor_y @  current_view nip  -  show_line cr ;

: draw ( -- )    \ draw a line for easier editing
      pen_down cursor_return sketch ;

: next_ ( -- )  \ increment the current image line
      <down> cursor_return ;

: back_ ( -- )  \ decrement the current image line
      <up> cursor_return ;    
      
: draw_next ( -- ) next_ draw ;  \ combine for easier editing

: plot_text ( -- )               \ Plot the text from user
     cursor_y @  cursor_x @  get_string gbanner ;

: htext ( -- ) text_up horizontal plot_text ;  \ horizontal text
: vtext ( -- )  text_down vertical plot_text ; \ verical text

\ Reduce bitmap image size by 2 
: shrinkit ( -- ) 
     current_view  swap 2/  swap 2/   view_from
     reduction @  2*  reduction !  shrink ;

\ Print the color or grayscale number from the stack 
: .color (  R G B : grayscale -- ) 
    c/pixel 0 do  >g loop 
    c/pixel 0 do  g> . loop ;

\ Current view frame information
: status_line ( -- ) 
    ." Cursor: " cursor_x @ dup .  cursor_y @ dup . space space 
    ." Pixel color: " swap pixel@  .color space space 
    ." Pen color: " intensity@ .color space space 
    draw? if ." Pen is down" else ." Pen is up" then 
    cr ;

: info ( -- ) 
   ."  Current file: " gfile count type cr 
   space c/pixel 1 = if ." grayscale" else ." color" then 
   space ." image size: " pic_width @   reduction @  /  . 
                         pic_height @   reduction @  /  .  cr 
   ."  Display from   " current_view swap . . cr 
   ."  Display width  " iwidth @ . cr
   ."  Display height " iheight @ . cr  cr ;

\ Change the viewing frame
: width_ ( n -- ) iwidth ! ; 
: height_ ( n -- ) iheight ! ; 
 
: +xy ( nx ny -- )  \ shift upper left corner of viewing frame 
     >r current_view >r +  r> r> +  view_from ; 

5 constant sfactor
: lsframe ( -- ) sfactor negate  0 +xy ;
: rsframe ( -- ) sfactor 0 +xy ;
: usframe ( -- ) 0 sfactor negate +xy ;
: dsframe ( -- ) 0 sfactor +xy ;

 create shift_keys             \ Evaluate user string for finer
  char i ,    ['] usframe ,    \ placment of the viewing frame
  char m ,    ['] dsframe , 
  char j ,    ['] lsframe , 
  char k ,    ['] rsframe ,
  null , 

: shift_it (  c -- ) 
       shift_keys 2 num-key  row if 
        cell+ @c execute 
      then drop ;

: shift_frame ( -- )            \ Shift viewing frame based on 
      get_string paint$ place   \ keystrokes recorded from user
      paint$ count 
      0 do
         paint$ i +  c@ shift_it 
      loop drop ;

\ The ascii art view of the image 
: show ( -- ) 
     iwidth @   pic_width @   reduction @ /  min 
     iheight @  pic_height @  reduction @ /  min 
     show_image status_line ;  

\ File I/O stuff
: getfile ( --  ) 
         defaults  1 reduction ! 
         get_string 2dup gfile place get_image 
         image_comment$ count type cr 
         info ; 

: saveit ( -- )   \ save current ascii image display 
  get_string 
  output open error?        \ value for file 
  abort" File could not be opened"    \ save handle 
  dup use                   \ redirect input to file 
  show close ; 

: isave ( -- )   \ save as ppm-bitmap using current shrink size. 
   get_string 
   0 0                              ( rx1 cy1 ) 
   pic_height @  reduction @  /     ( rx2 ) 
   pic_width @   reduction @  /     ( cy2 ) 
   crop ; 

: icrop ( -- )   \ save window as ppm-bitmap
   get_string
   current_view swap  2dup
   iwidth @ +  pic_width @ min     
   swap iheight @ +   pic_height @ min 
   swap crop ;
 
\ Restore the original image
: reload ( -- ) 1 reduction !  defaults  gfile count get_image ; 


: new_color ( width height -- )   \ set new color image
    color_image  pic_width !   pic_height !  gcls ;

: new_grayscale ( width height -- )  \ net new grayscale image
    grayscale_image pic_width !  pic_height !  gcls ;

 
\ Calculator executables 
: bye abort ;
: dot . ;
: .s_  .s ;
: dup_ dup ;
: rot_ rot ;
: swap_ swap ;
: plus_ + ;
: minus_ - ;
: times_ * ;
: divide_ / ;

: help  ( -- ) cr 
  ."  file  <name>  Load the PPM image file" cr
  ."  tsave <name>  Save current display as ASCII art" cr
  ."  isave <name>  Save full image as PPM-bitmap" cr
  ."  crop <name>   Save current display as bitmap" cr
  ."  w h new_color New color image of set width and height" cr
  ."  w h new_gray  New grayscale image" cr
  ."  info          Current settings" cr 
  ."  show          Show the ASCII image" cr
  ."  n n xy        Define the upper corner of image" cr
  ."  n n +xy       Shift the current viewing frame" cr 
  ."  n width       Define the width to display" cr 
  ."  n height      Define the height to display" cr 
  ."  invert        Set to display the negative image" cr 
  ."  normal        Set to display the normal image" cr 
  ."  shrink        Reduce current image size by two" cr 
  ."  reload        Reload image to full size" cr 
  ."  grayscale     Converted to grayscale image" cr 
  ."  + - * / .     Simple 4tH calculator" cr
  ."  swap dup rot  Simple 4tH calculator.   <Enter> to continue "
  cr refill drop 
  ."  penup pendown Drawing mode" cr
  ."  pen@  pen!    Check or set the pen color or grayscale intensity" cr
  ."  match         Set th pen color to current pixel color" cr
  ."  sk <string>   Sketch: u=penup d=pendown ijkm=cursor movement" cr
  ."                 rgzypcbw=red green yellow blue purple cyan black white" cr
  ."  dr <string>   Draw line: same as sketch but with x=draw .=right" cr
  ."  l             List or show the current line from the image" cr
  ."  n             Increment current line to the next line" cr
  ."  b             Decrement the back a line" cr
  ."  nd <string>   Incrment to next line and draw" cr
  ."  move <string> Move the viewing frame: ijkm = frame movement" cr
  ."  htext <str>   Write text at cursor position (horizontal)" cr
  ."  vtext <str>   Write text vertically" cr
  ."  home          Place cursor top left corner" cr
  ."  cls           Clear screen to white and set pen to black" cr
  ."  canvis        Fill canvas with current pen color" cr
  ."  white black red blue green yellow magenta cyan = set pen color" cr
  ."  quit          Exit the program" cr 
 cr ;

\ Dictionary 
create wordset 
  ," quit"    ' bye , 
  ," q"       ' bye , 
  ," bye"     ' bye , 
  ," .s"      ' .s_  , 
  ," ."       ' dot  , 
  ," dup"     ' dup_ , 
  ," rot"     ' rot_ , 
  ," swap"    ' swap_ , 
  ," +"       ' plus_ , 
  ," -"       ' minus_ , 
  ," *"       ' times_ , 
  ," /"       ' divide_ , 
  ," file"    ' getfile , 
  ," tsave"    ' saveit , 
  ," info"    ' info , 
  ," i"       ' info , 
  ," show"    ' show , 
  ," s"       ' show , 
  ," shrink"  ' shrinkit , 
  ," reload"  ' reload , 
  ," xy"      ' view_from , 
  ," +xy"     ' +xy , 
  ," width"   ' width_ , 
  ," height"  ' height_ , 
  ," invert"  ' invert_text_pixel , 
  ," normal"  ' normal_text_pixel , 
  ," grayscale" ' image>grayscale , 
  ," isave"   ' isave , 
  ," crop"    ' icrop ,
  ," pen!"    ' intensity! , 
  ," pen@"    ' intensity@ ,
  ," penup"   ' pen_up , 
  ," pendown" ' pen_down , 
  ," match"   ' cmatch , 
  ," sk"      ' sketch ,
  ," dr"      ' draw ,
  ," nd"      ' draw_next ,
  ," n"       ' next_ ,
  ," b"       ' back_ ,
  ," l"       ' line_ ,
  ," move"    ' shift_frame ,
  ," home"    ' home ,
  ," htext"   ' htext ,
  ," vtext"   ' vtext ,
  ," cls"     ' gcls ,
  ," black"   ' black ,
  ," blue"    ' blue ,
  ," cyan"    ' cyan ,
  ," red"     ' red ,
  ," green"   ' green ,
  ," magenta" ' magenta ,
  ," yellow"  ' yellow ,
  ," white"   ' white ,
  ," canvis"  ' background ,
  ," new_color"  ' new_color ,
  ," new_gray"   ' new_grayscale ,
  ," help"    ' help , 
  NULL , 
wordset to dictionary                  \ assign to dictionary 

 : initialize   \ file specified or assume a small color image 
    argn 1 > 
    if  1 args 2dup  gfile place  get_image 
    else  color_image s" none.ppm"  gfile place 
          150 pic_width !  150 pic_height !  gcls
    then 
    default_width iwidth ! 
    default_height iheight ! 
    cursor_on ; 

: title 
  cr ." == ASCII PPM/PMG PAINT PROGRAM ==" cr
   ."    Maximum image size is "  ppm_width .  ppm_height . cr 
   ."    help  = paint commands" cr cr info ; 

: ipaint
  initialize defaults show title 
  begin                                \ show the prompt and get a command 
    ." >" 
    refill drop              \ interpret and issue oops when needed 
    ['] interpret catch if ." Oops " then 
  again                                \ repeat command loop eternally 
;

ipaint


