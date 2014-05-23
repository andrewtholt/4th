\ 4tH library - ASCII to XML codes - Copyright 2012 J.L. Bezemer
\ You can redistribute this file and/or modify it under
\ the terms of the GNU General Public License

[UNDEFINED] ASCII>XML [IF]
[UNDEFINED] row       [IF] [needs lib/row.4th]    [THEN]

table ASCII>XML
    \ traitements signes reserves HTML
    060 , ," &lt;"                     \ Signe inferieur a
    062 , ," &gt;"                     \ Signe supreieur a
    038 , ," &amp;"                    \ Ampersand
    034 , ," &quot;"                   \ Signe double appostrophe
    039 , ," &apos;"                   \ Signe apostrophe
    NULL ,
does>                                  ( c -- a n)
  2 num-key row                        \ search table
  if                                   \ if HTML code drop original
    nip cell+ @c count                 \ output HTML code
  else                                 \ else drop dummy code
    drop <# [char] ; hold #s [char] # hold [char] & hold #>
  then                                 \ emit original
;
[THEN]