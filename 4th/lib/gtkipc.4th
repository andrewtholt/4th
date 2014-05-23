\ 4tH library - GTK server Unix IPC - Copyright 2010,2012 J.L. Bezemer
\ You can redistribute this file and/or modify it under
\ the terms of the GNU General Public License

[UNDEFINED] gtk-srv-start [IF]

256 string gtk-message                 \ message buffer
                                       \ determine PID
: pid!                                 ( -- n)
  s" ps --no-heading -C 4th" input pipe + open
  error? abort" Cannot start ps" dup use refill 0= abort" Cannot read ps"
  bl parse-word number error? abort" Invalid pid" to pid close
;
                                       ( -- h f)
: gtk-connect gtk-message count input pipe + open error? ;
: s>msg gtk-message +place ;           ( a n --)
: n>msg <# #s bl hold #> gtk-message +place  ;
: 's'>msg s"  '" s>msg s>msg s" '" s>msg ;
: gtk{ s" gtk-server msg=" gtk-message place pid <# #s #> s>msg s| ,"| s>msg ;
: }gtk s| "| s>msg gtk-connect if drop else dup use refill drop close then ;

: gtk-srv-start                        ( -- , init connection with gtk-server)
  pid! s" gtk-server -ipc=" gtk-message place
  pid <# #s #> gtk-message +place s"  -detach" s>msg 
  gtk-connect abort" Cannot start GTK-server" close
  gtk{ s" gtk_init NULL NULL" s>msg }gtk
;

: gtk-srv-stop                         ( -- , disconnect from gtk-server )
  gtk{ s" gtk_server_exit" s>msg }gtk
;

[DEFINED] 4TH# [IF]
  hide gtk-message
  hide gtk-connect
  hide pid
  hide pid!
[THEN]
[THEN]
