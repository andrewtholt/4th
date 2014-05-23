: BadExecute ( -- ) -4 EXECUTE ;
: BadAddress ( -- ) -4 @ DROP ;
: BadAlign ( -- ) 1 @ DROP ;
: BadReturn ( -- ) -4 >R ;
: _DROP DROP ;
: BadCode ( -- ) 0 ['] _DROP !  0 DROP ;
: BadRes1  9 0 /MOD ;
\ : BadRes2  0 1 1 UM/MOD ;
: BadBreak BEGIN  AGAIN ;
: BadNumb  1 1 BASE ! . ;

\ BadExecute
\ BadAddress
\ BadAlign
\ BadReturn
\ BadCode
\ BadRes1
\ BadBreak
\ BadNumb
