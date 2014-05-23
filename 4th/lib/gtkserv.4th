\ 4tH library - GTK server Unix - Copyright 2010,2012 J.L. Bezemer
\ You can redistribute this file and/or modify it under
\ the terms of the GNU General Public License

[UNDEFINED] gtk-init [IF]
: gtk                                  ( fam --)
  s" /tmp/gtk4tH" rot open error?
  abort" Cannot open pipe" dup use to (gtk)
;
                                       ( a n --)
: "type" [char] " emit type [char] " emit ;
: gtk{ output gtk ;                    ( --)
: }gtk cr (gtk) close input gtk refill drop (gtk) close ;

: gtk-srv-start                        ( -- , init connection with gtk-server)
  s" gtk-server -fifo=/tmp/gtk4tH -detach" input pipe + open
  error? abort" Cannot start gtk-server" close
  gtk{ ." gtk_init NULL NULL" }gtk ;

: gtk-srv-stop                         ( -- , disconnect from gtk-server )
  gtk{ ." gtk_server_exit" }gtk ;
  
[DEFINED] 4TH# [IF]
  hide gtk
  hide (gtk)
[THEN]
[THEN]

