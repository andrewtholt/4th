\ SHUFFLE - Copyright 2007 J.L. Bezemer
\ You can redistribute this file and/or modify it under
\ the terms of the GNU General Public License

\ Rnaodm Osbrevation
\ I'm srue a few of you hvae alerady seen tihs, but, I stlil tinhk it's
\ facsintaing: Aoccdrnig to rscheearch at Cmabrigde Uinervtisy,
\ it deosn't mttaer in waht oredr the ltteers in a wrod are, the olny
\ iprmoetnt tihng is taht the frist and lsat ltteer be at the rghit pclae.
\ The rset can be a total mses and you can sitll raed it wouthit porbelm.
\ Tihs is bcuseae the huamn mnid deos not raed ervey lteter by istlef,
\ but the wrod as a wlohe. In'st taht intrestnig?

include lib/slice.4th
include lib/choose.4th

64 string temp

: +char chars >r over r@ + 1 temp +place r> 1 cut ;
: shuffle 0 +char dup 2 - 0 ?do dup 1- choose +char loop ;
: ?shuffle dup 3 > if shuffle then temp +place temp count type space ;
: Read-file refill ;
: Usage abort" Usage: shuffle infile.txt outfile.txt" ;
: Process begin 0 temp c! bl parse-word dup while ?shuffle repeat 2drop cr ;
  
include lib/convert.4th