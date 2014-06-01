-1 value sid
-1 value out-buffer
-1 value in-buffer

0 value counter
 
2048 constant O_NONBLOCK \ 04000 in ocatl
 
0 constant F_DUPFD ( Duplicate file descriptor.  )
1 constant F_GETFD ( Get file descriptor flags.  )
2 constant F_SETFD ( Set file descriptor flags.  )
3 constant F_GETFL ( Get file status flags.  )
4 constant F_SETFL ( Set file status flags.  )
 
255 constant /buffer

: main
   ." Hello" cr
   s" localhost" 1234 socket-connect abort" connect" to sid

\   /buffer allocate abort" allocate" to in-buffer
\   /buffer allocate abort" allocate" to out-buffer

\   cr
\   ." Socket id is " sid . cr

\    in-buffer  /buffer erase
\    out-buffer /buffer erase

\    sid F_GETFL 0 fcntl  \ flags
\    O_NONBLOCK or
\    >r sid F_SETFL r> fcntl abort" fcntl"

\    s" fred" out-buffer swap move
\    0x0a out-buffer 4 + c!

\    out-buffer 10 dump

\    out-buffer 5 sid socket-send abort" socket-send"
\    ." Chars sent " . cr

\    begin
\        in-buffer 6 sid socket-recv -1 =
\    while
\        count 1+ to count
\        1 ms
\    repeat

\    ." Looped " count . cr

\    in-buffer 6 sid socket-recv
\    dup ." Char rx " . cr
\    in-buffer swap dump

;

main

