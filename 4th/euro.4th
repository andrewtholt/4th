\ Euro Calculator - (c) 1999,2008 HanSoft & Partners

\ DISCLAIMER!
\ THIS PROGRAM IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, EITHER
\ IMPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
\ WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
\ PURPOSE. THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF
\ THIS PROGRAM IS WITH YOU. THE AUTHOR DOES NOT WARRANT THAT
\ OPERATION OF THIS PROGRAM WILL BE UNINTERRUPTED OR ERROR FREE. IN
\ NO EVENT WILL THE DISTRIBUTOR OR AUTHOR OF THIS PROGRAM BE LIABLE FOR
\ ANY DAMAGES, INCLUDING ANY LOST PROFITS, LOST SAVINGS OR ANY OTHER
\ INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF THE USE OR
\ INABILITY TO USE THIS PROGRAM, EVEN IF THE AUTHOR HAS BEEN ADVISED
\ OF THE POSSIBILITY OF SUCH DAMAGES, OR FOR ANY OTHER CLAIM BY ANY
\ OTHER PARTY. THE AUTHOR EXPLICITLY STATES THAT THE RESULTS OF THIS
\ PROGRAM MAY NOT BE ACCURATE AND DISCOURAGES ITS USE IN ENVIRONMENTS
\ WHERE CONFORMITY WITH COUNCIL DIRECTIVE CE 1103/97 IS REQUIRED!!

[needs lib/interprt.4th]

   1000000 constant EUR                \ exchange rates
   2203710 constant NLG
  40339900 constant BEF
   1955830 constant DEM
1936270000 constant ITL
 200482000 constant PTE
   5945730 constant FIM
    787564 constant IEP
   6559570 constant FRF
 166386000 constant ESP
  13760300 constant ATS
                                       \ general conversion words
: Reverse 1000000 swap / swap over ;   ( n1 n2 -- n3 n1 n3)
: Round swap 2/ + ;                    ( n1 n2 -- n3)
: ScaleRate dup >r 2/ + r> / ;         ( n1 n2 -- n3)
: SplitSign >r dup abs r> ;            ( n1 n2 -- n3 +n1 n2)
: ApplySign swap 0< if negate then ;   ( n1 +n2 -- n2)
: Currency s>d <# # # [char] , hold #s sign #> type cr ;

: GetPrecision                         ( n1 -- n2)
  1000000                              \ determine scaling factor
  begin                                \ for this exchange rate
    over over
    /
    1000 <
  while
    10 /
  repeat
  swap drop
;
                                       \ convert to scaled rate
: GetScaledRate                        ( n1 n2 -- n3 +n1 n4 n5)
  SplitSign                            ( sg am ra)
  dup GetPrecision                     ( sg am ra pr)
  swap over                            ( sg am pr ra pr)
  ScaleRate                            ( sg am pr sr)
;

: >EURO                                \ convert to Euro (n1 n2 -- n3)
  GetScaledRate                        ( sg +am pr sr)
  >r                                   ( sg +am pr)
  Reverse                              ( sg rp +am rp)
  *                                    ( sg rp +ua)
  Round                                ( sg +sa)
  r> /                                 ( sg +eu)
  ApplySign                            ( eu)
;

: EURO>                                \ convert from Euro ( n1 n2 --)
  GetScaledRate                        ( sg +eu pr sr)
  rot                                  ( sg pr sr +eu)
  *                                    ( sg pr +sa)
  swap                                 ( sg +sa pr)
  Reverse                              ( sg rp +sa rp)
  >r                                   ( sg rp +sa)
  Round                                ( sg +ra)
  r> /                                 ( sg +am)
  Currency                             ( --)
;

: nlg> NLG >EURO ;                     \ currency conversions words
: bef> BEF >EURO ;
: dem> DEM >EURO ;
: itl> ITL >EURO ;
: pte> PTE >EURO ;
: fim> FIM >EURO ;
: iep> IEP >EURO ;
: frf> FRF >EURO ;
: esp> ESP >EURO ;
: ats> ATS >EURO ;
: eur> EUR >EURO ;

: .nlg ." NLG " NLG EURO> ;            \ currency display words
: .bef ." BEF " BEF EURO> ;
: .dem ." DEM " DEM EURO> ;
: .itl ." ITL " ITL EURO> ;
: .pte ." PTE " PTE EURO> ;
: .fim ." FIM " FIM EURO> ;
: .iep ." IEP " IEP EURO> ;
: .frf ." FRF " FRF EURO> ;
: .esp ." ESP " ESP EURO> ;
: .ats ." ATS " ATS EURO> ;
: .luf ." LUF " BEF EURO> ;
: .eur ." EUR " EUR EURO> ;

: _+ + ;                               \ general words
: _- - ;
: _* * ;
: _/ / ;
: bye quit ;

: help                                 \ help screen
  cr ." The amount must be multiplied by 100 when entered, e.g.:"
  cr ." 'NLG 175' must be entered as '17500 NLG'."
  cr ." This will convert Dutch guilders to German marks, eg.:"
  cr ." 17500 NLG .DEM <enter>"
  cr ." Available currencies are: "
  cr ." NLG, BEF, DEM, ITL, PTE, FIM, IEP, FRF, ESP, ATS, LUF and EUR"
  cr ." RPN calculation is available. Enter 'exit' to quit program."
  cr ." NOTE: Results may suffer from rounding and overflow errors."
  cr
;

create wordlist                        \ dictionary
  ," nlg" ' nlg> ,
  ," bef" ' bef> ,
  ," dem" ' dem> ,
  ," itl" ' itl> ,
  ," pte" ' pte> ,
  ," fim" ' fim> ,
  ," iep" ' iep> ,
  ," frf" ' frf> ,
  ," esp" ' esp> ,
  ," ats" ' ats> ,
  ," luf" ' bef> ,
  ," eur" ' eur> ,
  ," .nlg" ' .nlg ,
  ," .bef" ' .bef ,
  ," .dem" ' .dem ,
  ," .itl" ' .itl ,
  ," .pte" ' .pte ,
  ," .fim" ' .fim ,
  ," .iep" ' .iep ,
  ," .frf" ' .frf ,
  ," .esp" ' .esp ,
  ," .ats" ' .ats ,
  ," .luf" ' .luf ,
  ," .eur" ' .eur ,
  ," +"    ' _+ ,
  ," -"    ' _- ,
  ," *"    ' _* ,
  ," /"    ' _/ ,
  ," quit" ' bye ,
  ," exit" ' bye ,
  ," bye"  ' bye ,
  ," q"    ' bye ,
  ," help" ' help ,
  NULL ,

wordlist to dictionary
:noname ." Unknown command '" type ." '" cr ; is NotFound
                                       \ euro calculator
: euro
  begin
    ." OK" cr
    refill drop ['] interpret
    catch if ." Error" cr then
  again
;

euro
