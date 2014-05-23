/*
+-------+-----------------+------+-----------------+-------+-----------------+
|Program| COMP_4TH.C      |Header| 4TH.H           |Library| 4TH             |
+-------+-----------------+------+-----------------+-------+----------+------+
|HISTORY                                           |    Programmer    | Date |
+--------------------------------------------------+------------------+------+
| Turbo C V2.0 version                             | J.L. Bezemer     |181094|
| DPX/2 340 version                                | J.L. Bezemer     |181094|
| Coherent V4.2 version                            | J.L. Bezemer     |201094|
| DJGPP V2.72 version                              | J.L. Bezemer     |230597|
| Linux 2.2.10 version                             | J.L. Bezemer     |170600|
+--------------------------------------------------+------------------+------+
|MODIFICATION LOG                                  |    Programmer    | Date |
+--------------------------------------------------+------------------+------+
| Added J, I', /MOD, * /, * /MOD, FAST, SLOW       | J.L. Bezemer     |191094|
| Added hex check on resolving symbols             | J.L. Bezemer     |191094|
| Added .R, TH, BASE@, USER@, LIMIT@, STACK@,      | J.L. Bezemer     |201094|
| Added WIDTH@, V0@, SP@, RP@, VARIABLE, ALLOT     | J.L. Bezemer     |201094|
| Redesigned building symboltable                  | J.L. Bezemer     |201094|
| Added TICK, COMMA, EXECUTE, ABORT, EXIT, CREATE  | J.L. Bezemer     |241094|
| Added C@, WAIT; removed resolving LITERALS       | J.L. Bezemer     |241094|
| Redesigned resolving symbols                     | J.L. Bezemer     |241094|
| Added OCTAL, DECIMAL, HEX in second pass         | J.L. Bezemer     |241094|
| Removed LITERAL resolving code at VARIABLE       | J.L. Bezemer     |251094|
| Completely restructured substitution algorhythm  | J.L. Bezemer     |251094|
| Added /. and /.R commands                        | J.L. Bezemer     |271094|
| Added TIME and RANDOM commands                   | J.L. Bezemer     |161194|
| Merged pass1_4th() and pass2_4th()               | J.L. Bezemer     |220295|
| Modified documentation; added some statics       | J.L. Bezemer     |010395|
| Fixed first pass bug and PRINT bug               | J.L. Bezemer     |140395|
| Removed V0@, changed , to C,                     | J.L. Bezemer     |180395|
| Merged GetFAddr() and GetBAddr() to GetAddr()    | J.L. Bezemer     |210395|
| GetAddr() now optionally patches target keyword  | J.L. Bezemer     |210395|
| Removed LABEL, DEFINE and CREATE                 | J.L. Bezemer     |210395|
| Fixed ProgSiz4th check bug                       | J.L. Bezemer     |210395|
| Cut out some unneeded assignments in 1st pass    | J.L. Bezemer     |240395|
| Changed LIMIT@ to VARS, USER@ to USER            | J.L. Bezemer     |310395|
| Changed STACK@ to STACK, C, to ,                 | J.L. Bezemer     |310395|
| Added C, , HERE, ASCII, changed WIDTH@ to LENGTH | J.L. Bezemer     |310395|
| Completely redesigned the object format          | J.L. Bezemer     |140495|
| Removed LITERAL, PENDING, TICK, SLOW and FAST    | J.L. Bezemer     |140495|
| Removed CCOMMA and COMMENT, redefined COMMA      | J.L. Bezemer     |140495|
| First version of 4tH V2.0; changed C@ to ,@      | J.L. Bezemer     |190495|
| Removed VARDECL from VARIABLE code               | J.L. Bezemer     |200495|
| Fixed some very minor errors                     | J.L. Bezemer     |200495|
| Fixed stringarea bug; added static to functions  | J.L. Bezemer     |210495|
| Fixed bug in ASCII                               | J.L. Bezemer     |210495|
| Added R@, >> & <<, removed VALUE, changed STACK  | J.L. Bezemer     |250495|
| Fixed StringArea bug; changed LENGTH to WIDTH@   | J.L. Bezemer     |280495|
| Removed INPUT, added QUERY and other text words  | J.L. Bezemer     |280495|
| Added !IN                                        | J.L. Bezemer     |290495|
| Changed all CONSTANT to LITERAL; added SYMWORDS  | J.L. Bezemer     |300495|
| Removed /., /.R; added #, #S, <#, #>, HOLD & SIGN| J.L. Bezemer     |010595|
| Added COPY; TICK now also compiles VARIABLE      | J.L. Bezemer     |020595|
| TICK now works like Forth                        | J.L. Bezemer     |030595|
| TICK now only works with COLON defs again        | J.L. Bezemer     |040595|
| Added ,", -TRAIL, >TTY, >FILE, ConstList         | J.L. Bezemer     |060995|
| Added GetSimpleConst(); removed strcalc() words  | J.L. Bezemer     |060995|
| Renamed WIDTH@ to WIDTH; some cosmetic changes   | J.L. Bezemer     |070995|
| Removed NEG, changed #define into NEGATE         | J.L. Bezemer     |080995|
| Added [BINARY] operator                          | J.L. Bezemer     |080995|
| Removed LESS, KILL, LEFT, RIGHT, !IN             | J.L. Bezemer     |110995|
| Added SHIFT, >IN                                 | J.L. Bezemer     |110995|
| Added EXPECT; new Version4th included            | J.L. Bezemer     |140995|
| Added TTY>, FILE>, #TIB, #PAD                    | J.L. Bezemer     |150995|
| Added INFILE, OUTFILE                            | J.L. Bezemer     |180995|
| Added -N, +N and DEPTH                           | J.L. Bezemer     |210995|
| Updated errors; changed -N/+N to -LIMIT/+LIMIT   | J.L. Bezemer     |220995|
| Added ParseStrings(), ParseText(), MoveString()  | J.L. Bezemer     |020296|
| Added GetNextWord(); deleted others              | J.L. Bezemer     |020296|
| Fixed some declarations (ANSI_C, static)         | J.L. Bezemer     |070296|
| Added MakeLink(), MarkLink(), PairLink()         | J.L. Bezemer     |080296|
| Removed GetAddr(), FillWord() and 2nd pass       | J.L. Bezemer     |080296|
| Added FALSE, TRUE, new BRANCH-constructs         | J.L. Bezemer     |080296|
| Replaced RETURN with EXIT in ;                   | J.L. Bezemer     |090296|
| Added cell support and NE0; fixed some minor bugs| J.L. Bezemer     |100296|
| Checks for unique name; moved WordList           | J.L. Bezemer     |110296|
| Moved ConstList to GetSimpleConst()              | J.L. Bezemer     |110296|
| Added support for Hcode and tok                  | J.L. Bezemer     |120296|
| Added HI, LO, ALLOCATE; changed #LINE to L/SCR   | J.L. Bezemer     |140296|
| Fixed bug when early errors occur                | J.L. Bezemer     |160296|
| Added TO and VALUE                               | J.L. Bezemer     |240296|
| Fixed some minor bugs in strings; changed TICK   | J.L. Bezemer     |240296|
| Added aliases CHAR, CHAR+, CHAR-, CELL+, CELL-   | J.L. Bezemer     |250296|
| Added dummies CHARS and CELLS                    | J.L. Bezemer     |250296|
| Changed ," to c" ; added aliases INVERT and R@   | J.L. Bezemer     |040396|
| Removed LINE, C/L, L/SCR; changed ALLOCATE       | J.L. Bezemer     |050396|
| Changed VARS to LAST, USER to FIRST; added VARS  | J.L. Bezemer     |050396|
| Added aliases MOVE, LSHIFT, ['] and [CHAR]       | J.L. Bezemer     |100396|
| Added dummies ALIGN and ALIGNED                  | J.L. Bezemer     |100396|
| Changed header to check alignment                | J.L. Bezemer     |130396|
| Fixed bug; no error when no program              | J.L. Bezemer     |130396|
| Changed InitObject() to new standards            | J.L. Bezemer     |100496|
| Added GetDeclaration(); changed main()           | J.L. Bezemer     |180496|
| Renamed SearchSymTable() to GetSymbolTable()     | J.L. Bezemer     |180496|
| Fixed silly bug in DoBinary()                    | J.L. Bezemer     |060596|
| Added constant APPL                              | J.L. Bezemer     |290796|
| Changed APPL to APP                              | J.L. Bezemer     |100996|
| Added AllocResource() and AbortCompile()         | J.L. Bezemer     |021096|
| Rewrote sections for new Hcode format            | J.L. Bezemer     |021096|
| Added ReallocSegs(); fixed minor bugs            | J.L. Bezemer     |031096|
| Added NULL check in ParseText()                  | J.L. Bezemer     |081096|
| Changed GetDeclaration() to GetImmediate()       | J.L. Bezemer     |081096|
| Changed '@ to @'; changed allocation order       | J.L. Bezemer     |101096|
| Removed ALLOCATE, added STRING and AT            | J.L. Bezemer     |211096|
| Renamed DoAllocate() to DoString()               | J.L. Bezemer     |211096|
| Changed DoConstant() a little                    | J.L. Bezemer     |211096|
| Renamed GetSymbolTable() to GetSymbol()          | J.L. Bezemer     |301096|
| Renamed GetSimpleWord() to GetWord()             | J.L. Bezemer     |301096|
| Renamed GetSimpleConst() to GetConstant()        | J.L. Bezemer     |301096|
| Added NOT_FOUND; changed DoValue() and DoTick()  | J.L. Bezemer     |301096|
| Changed GetWord(), GetImmediate(), GetConstant() | J.L. Bezemer     |301096|
| Added COMPILE, , changed +LIMIT to LIMIT         | J.L. Bezemer     |201196|
| Changed -LIMIT to (ERROR), added S0 and R0       | J.L. Bezemer     |201196|
| Removed ABORT, added SP! and RP!                 | J.L. Bezemer     |201196|
| Added F_T and F_F                                | J.L. Bezemer     |031296|
| Added CLOSEIO                                    | J.L. Bezemer     |061296|
| Fixed bug in ParseText(); last word is ignored   | J.L. Bezemer     |060297|
| Updated errors; removed M4INTERR                 | J.L. Bezemer     |060297|
| Removed >TTY, TTY>, >FILE, FILE>, INFILE, OUTFILE| J.L. Bezemer     |280297|
| Removed CLOSEIO; added FILE, TTY, INPUT, OUTPUT  | J.L. Bezemer     |280297|
| Added OPEN, CLOSE                                | J.L. Bezemer     |280297|
| Fixed tiny bug in AbortCompile() K&R header      | J.L. Bezemer     |150397|
| Removed COMPILE,                                 | J.L. Bezemer     |180397|
| Removed stpncpy() because of Linux confict       | J.L. Bezemer     |080497|
| Added RESULT variable                            | J.L. Bezemer     |100497|
| Added ASSERT, ASSERT( and )                      | J.L. Bezemer     |110497|
| Fixed bug in ParseStrings()                      | J.L. Bezemer     |110497|
| Added ParseDefines(); fixed bug: init globals    | J.L. Bezemer     |120497|
| Changed ASSERT to [ASSERT]; changed DoAssert()   | J.L. Bezemer     |170497|
| Added THROW, HANDLER; removed SP!, RP!, S0, R0   | J.L. Bezemer     |170497|
| Changed M4TABFUL to M4BADOBJ                     | J.L. Bezemer     |200497|
| Added DecodeSymbol(), DoArray(); removed ALLOT   | J.L. Bezemer     |220597|
| Removed DoAllot(); added .(, ", TABLE, ARRAY     | J.L. Bezemer     |220597|
| Removed AT; changed ParseStrings(), DoString()   | J.L. Bezemer     |220597|
| Added support for LOCAL_H; fixed ASCII bug       | J.L. Bezemer     |220597|
| Changed AddSymbol(); added DoRecurse(), RECURSE  | J.L. Bezemer     |220597|
| Fixed bug in ParseText()                         | J.L. Bezemer     |230597|
| Cleaned up code in ParseText()                   | J.L. Bezemer     |240597|
| Added ARGS and ARGN                              | J.L. Bezemer     |240797|
| Removed <limits.h>                               | J.L. Bezemer     |250797|
| Added [IF] and [THEN]                            | J.L. Bezemer     |260897|
| Added SkipSource() and DecodeLiteral()           | J.L. Bezemer     |260897|
| Fixed serious bug in ParseStrings()              | J.L. Bezemer     |270897|
| Added S>D and ABORT                              | J.L. Bezemer     |310897|
| Added :NONAME, DoNoName() and DecodeWord()       | J.L. Bezemer     |130997|
| Added ParseDirective(); removed ParseDefines()   | J.L. Bezemer     |170997|
| Changed ParseStrings() and ParseText()           | J.L. Bezemer     |170997|
| Added FreeResource() to minimize memory usage    | J.L. Bezemer     |250997|
| Removed -TRAIL; added TUCK, NIP, +UNDER, RSHIFT  | J.L. Bezemer     |250997|
| Added -TRAILING, CMOVE>, BLANK and ERASE         | J.L. Bezemer     |250997|
| Changed char[] to *char in ...4th structs        | J.L. Bezemer     |250997|
| Changed ? to inline macro; removed I'            | J.L. Bezemer     |260997|
| Stripped arguments from MoveString()             | J.L. Bezemer     |290997|
| Removed 2+ and 2-; added ?DO and CompileLoop()   | J.L. Bezemer     |151097|
| Removed QUERY, added REFILL                      | J.L. Bezemer     |311097|
| Removed Forth79 words ASCII, END, ENDIF, MINUS, R| J.L. Bezemer     |011197|
| Removed Forth79 word NOT, added D>S              | J.L. Bezemer     |011197|
| Changed DoRecurse(), uses the ControlStack now   | J.L. Bezemer     |121197|
| Added CATCH and CAUGHT; changed SPACE to macro   | J.L. Bezemer     |191197|
| Changed LIMIT to MAX-N, #PAD to /PAD             | J.L. Bezemer     |201197|
| Changed #TIB to /TIB, STACK to STACK-CELLS       | J.L. Bezemer     |201197|
| Added MAX-RAND; fixed serious bug in searchings  | J.L. Bezemer     |201197|
| Changed MAX-RAND from RAND_MAX to RNDMASK        | J.L. Bezemer     |221197|
| Removed EasyC syntax                             | J.L. Bezemer     |150198|
| Added #!, APPEND, TEXT; changed ReallocSegs()    | J.L. Bezemer     |160298|
| Updated version info                             | J.L. Bezemer     |180198|
| Added DoSQuote() and S"                          | J.L. Bezemer     |200198|
| Fixed minor bug in ReallocSegs()                 | J.L. Bezemer     |230198|
| Added DoAdd(), DoMultiply(), DoNot()             | J.L. Bezemer     |071298|
| Removed +UNDER                                   | J.L. Bezemer     |131099|
| Replaced tok datatype by unit datatype           | J.L. Bezemer     |301099|
| Fixed major bug; changed InitObject()            | J.L. Bezemer     |111199|
| Global variables are now properly initialized    | J.L. Bezemer     |111199|
| Added [=], [ABORT], /CELL and /CHAR              | J.L. Bezemer     |170600|
| Fixed some Linux warnings (no need; code is OK)  | J.L. Bezemer     |190600|
| Added SKIP, TOKEN; Added DoWord() and DoParse()  | J.L. Bezemer     |160201|
| Added PLACE and DoPlace()                        | J.L. Bezemer     |290301|
| Added ABORT" and DoAbortQuote()                  | J.L. Bezemer     |301101|
| Added PIPE                                       | J.L. Bezemer     |230202|
| Added USE, removed TTY and FILE                  | J.L. Bezemer     |280202|
| Added DEFER, IS, AS and FILE and DoInitValue()   | J.L. Bezemer     |140902|
| Added STDIN, STDOUT                              | J.L. Bezemer     |170902|
| Added [NEEDS, MakeRoom(), ScanText(), DoNeeds()  | J.L. Bezemer     |240103|
| Rewrote ParseXXXX() functions and ScanText()     | J.L. Bezemer     |290103|
| Fixed a few small bugs in DoNeeds() and others   | J.L. Bezemer     |300103|
| Updated comments, fixed K&R prototype ScanText() | J.L. Bezemer     |020203|
| Changed DoAssert(), added static to MatchName()  | J.L. Bezemer     |020203|
| Added SearchDictionary(), [FIND]                 | J.L. Bezemer     |050203|
| Changed [FIND] to [DEFINED] (COMUS compatible)   | J.L. Bezemer     |120203|
| Removed C", changed DoCQuote() to DoQuote()      | J.L. Bezemer     |120203|
| Removed COPY, NOOP, TOKEN, FETCHPRM, GE, LE      | J.L. Bezemer     |060603|
| Added PARSE, OFETCH, STRINGD, CELLD, PLACE       | J.L. Bezemer     |060603|
| Removed DoPlace(), DoWord()                      | J.L. Bezemer     |060603|
| Changed DoQuote() to DoCommaQuote()              | J.L. Bezemer     |060603|
| Added DoLessEqual(), DoGreaterEqual()            | J.L. Bezemer     |060603|
| Added DoParseWord(), changed DoAbortQuote()      | J.L. Bezemer     |060603|
| Changed SKIP to OMIT, APPEND to UPDATE           | J.L. Bezemer     |120603|
| Added INCLUDE                                    | J.L. Bezemer     |120603|
| Changed RESULT to OUT                            | J.L. Bezemer     |020703|
| Added 4TH, Changed UPDATE to APPEND              | J.L. Bezemer     |070803|
| Changed 4TH to 4TH# due to naming conflicts      | J.L. Bezemer     |311003|
| Added SLEEP, changed InitObject()                | J.L. Bezemer     |031103|
| Fixed some TurboC warnings                       | J.L. Bezemer     |061103|
| Added 'mark' to hide some TurboC dependancies    | J.L. Bezemer     |071103|
| Added EOL, changed delimiter INCLUDE to WHITE    | J.L. Bezemer     |071103|
| Removed redundant " from tokenizer               | J.L. Bezemer     |071103|
| Changed some parameters from 'mark' to 'marker'  | J.L. Bezemer     |071103|
| Added CALL, NOT and [UNDEFINED]                  | J.L. Bezemer     |281103|
| Added VECTOR, DoIs(), DoFile(), DoDefer()        | J.L. Bezemer     |011203|
| Added CompileValue(), removed DoInitValue(), CALL| J.L. Bezemer     |011203|
| Added CompileMark(), cleaned comments            | J.L. Bezemer     |021203|
| Added DoInvert(), [INVERT]                       | J.L. Bezemer     |050104|
| Added Object->Offset initialization              | J.L. Bezemer     |050104|
| Removed WAIT                                     | J.L. Bezemer     |140104|
| Removed [INVERT], DoInvert()                     | J.L. Bezemer     |190104|
| Added IMMEDIATE                                  | J.L. Bezemer     |230104|
| Added S| and ,|                                  | J.L. Bezemer     |040204|
| Added 2DUP, 2DROP, 2SWAP, DoTwoDrop(), DoTwoDup()| J.L. Bezemer     |120304|
| Added 2>R, 2R>, DoTwoRGet(),DoTwoRPut(),DoTwoSwap| J.L. Bezemer     |120304|
| Added FORGET, +PLACE, DoForget(), DoPlusPlace()  | J.L. Bezemer     |140704|
| Added -ROT, DoMinRot()                           | J.L. Bezemer     |310704|
| Added /HOLD                                      | J.L. Bezemer     |100804|
| Added SOURCE, SOURCE!, DoSource(), DoSourceBang()| J.L. Bezemer     |151004|
| Added 2R@, R'@, DoTwoRCopy(), DoRTickCopy()      | J.L. Bezemer     |211004|
| Added BOUNDS, UNLOOP, DoBounds(), DoUnLoop()     | J.L. Bezemer     |211004|
| Added InlineWord()                               | J.L. Bezemer     |211004|
| Changed InlineWord() to InlineWords()            | J.L. Bezemer     |221004|
| Reorganized the inline macros                    | J.L. Bezemer     |231004|
| Merged ImmedList[] and ParseList[]               | J.L. Bezemer     |111104|
| Added DEFER@, DEFER!                             | J.L. Bezemer     |201104|
| Added DoDeferFetch() and DoDeferStore()          | J.L. Bezemer     |201104|
| Added TurboC fix to InlineWords()                | J.L. Bezemer     |051204|
| Added >BODY and DoToBody()                       | J.L. Bezemer     |201204|
| Added SCONSTANT, DecodeOperand(), DoSConstant()  | J.L. Bezemer     |221204|
| Fixed tiny bug in InLineWords()                  | J.L. Bezemer     |311204|
| Added :WITH, DoWith()                            | J.L. Bezemer     |280205|
| Restricted use of :WITH, changed DoWith()        | J.L. Bezemer     |010305|
| Changed DoRepeat(), removed DoAgain()            | J.L. Bezemer     |010305|
| Added CompileAgain()                             | J.L. Bezemer     |020305|
| Changed DoRepeat(), DoUntil()                    | J.L. Bezemer     |020305|
| Renamed O@ to @C, OFETCH to FETCHC               | J.L. Bezemer     |040305|
| Added DOES>                                      | J.L. Bezemer     |050305|
| Added STRUCT, END-STRUCT, FIELD, ->, INSTANCE    | J.L. Bezemer     |170505|
| Added DoField(), DoMember(),                     | J.L. Bezemer     |170505|
| Changed :WITH to :THIS, DoWith() to DoThis()     | J.L. Bezemer     |170505|
| Added ALIAS                                      | J.L. Bezemer     |230505|
| Changed STRUCT to FIELDS, END-STRUCT to STRUCTURE| J.L. Bezemer     |220805|
| Removed INSTANCE                                 | J.L. Bezemer     |230805|
| Added ENUM, DoEnum()                             | J.L. Bezemer     |190905|
| Added CompileConstant()                          | J.L. Bezemer     |220905|
| Removed TEXT                                     | J.L. Bezemer     |101105|
| Changed ) into an inline macro                   | J.L. Bezemer     |110106|
| Changed HI, FIRST, LAST into ENVIRONs            | J.L. Bezemer     |110106|
| Added SOURCE-ID, CIN and COUT                    | J.L. Bezemer     |110106|
| Changed FIELDS to STRUCT, STRUCTURE to END-STRUCT| J.L. Bezemer     |130106|
| Changed -> and FIELD; removed DoMember()         | J.L. Bezemer     |130106|
| Added +CONSTANT, DoPConstant()                   | J.L. Bezemer     |130106|
| Added FSEEK, FTELL                               | J.L. Bezemer     |180106|
| Added @GOTO                                      | J.L. Bezemer     |160206|
| Added [ALIAS], DoAlias()                         | J.L. Bezemer     |130406|
| Changed [ALIAS] to AKA, DoAlias() to DoAka()     | J.L. Bezemer     |190406|
| Changed FORGET to HIDE, DoForget() to DoHide()   | J.L. Bezemer     |210406|
| Renamed SLEEP to PAUSE; added FILES              | J.L. Bezemer     |181106|
| Added DoStarSlashMod() and SYNC                  | J.L. Bezemer     |030507|
| Added .|                                         | J.L. Bezemer     |040507|
| Added [NEGATE], DoNegate(); corrected -> entry   | J.L. Bezemer     |080807|
| Changed FIELD to +FIELD, added /STRING and CHOP  | J.L. Bezemer     |280807|
| Removed HEX, OCTAL, DECIMAL; added RADIX         | J.L. Bezemer     |201207|
| Added OFFSET, CCOMMA, DoOffset(), DoCComma()     | J.L. Bezemer     |201207|
| Changed DoCreate(), DoAka(), DoVariable()        | J.L. Bezemer     |201207|
| Changed DoSConstant(); added MakeSymbol()        | J.L. Bezemer     |201207|
| Added DoOpen()                                   | J.L. Bezemer     |170108|
| Added ERROR?, DoErrorQ(); removed AS             | J.L. Bezemer     |061108|
| Added BUFFER:                                    | J.L. Bezemer     |230209|
| Added [SIGN], DoSign(), [/], DoDivide()          | J.L. Bezemer     |170609|
| Removed RANDOM, MAX-RAND                         | J.L. Bezemer     |241009|
| Changed strtoc() to strtocell()                  | J.L. Bezemer     |211109|
| Added tail optimization to DoSColon()            | J.L. Bezemer     |161209|
| Changed DoAka(), GetWord(), GetConstant()        | J.L. Bezemer     |130210|
| Added FIELD:, DoFieldC()                         | J.L. Bezemer     |180310|
| Added DELFILE                                    | J.L. Bezemer     |220610|
| Added ENVFETCH                                   | J.L. Bezemer     |010710|
| Changed ENV@ to ENVIRON@                         | J.L. Bezemer     |140710|
| Added 2NIP, DoTwoNip()                           | J.L. Bezemer     |051110|
| Changed DoSColon(), CompileWord()                | J.L. Bezemer     |051110|
| Changed CompileWord(), added Optimized()         | J.L. Bezemer     |071110|
| Added OptimizeLiteral(), OptimizePLiteral()      | J.L. Bezemer     |071110|
| Added OptimizeExit()                             | J.L. Bezemer     |071110|
| Changed OptimizePLiteral(), added VARIABLE       | J.L. Bezemer     |160311|
| Changed OptimizePLiteral(), added Argument check | J.L. Bezemer     |190311|
| Added [FORCE], changed all optimizer functions   | J.L. Bezemer     |190311|
| Removed superfluous argument in OptimizeLiteral()| J.L. Bezemer     |200311|
| Added TAG, DoTag()                               | J.L. Bezemer     |070511|
| Changed DoTag(), DoAka(), CompileValue()         | J.L. Bezemer     |130511|
| Added >STRING, DoToString()                      | J.L. Bezemer     |150511|
| Added BREAK, AFTER, DoBreak()                    | J.L. Bezemer     |070811|
| Added REWIND, DoRewind()                         | J.L. Bezemer     |120811|
| Changed BREAK to DONE, DoBreak() to DoDone()     | J.L. Bezemer     |140811|
| Added [MAX], /FIELD, DoMax()                     | J.L. Bezemer     |050911|
| Replaced strtol() with str2cell(), cleaned up    | J.L. Bezemer     |091011|
| Added [PRAGMA], DoPragma()                       | J.L. Bezemer     |101111|
| Added CompileDoes(), DoDoes()                    | J.L. Bezemer     |291111|
| Changed :THIS to :REDO, DoThis() to DoRedo()     | J.L. Bezemer     |291111|
| Added setting ErrNo to DoDoes()                  | J.L. Bezemer     |301111|
| Added [ELSE], DoBElse(), changed SkipSource()    | J.L. Bezemer     |171211|
| Applied Coherent patches                         | J.L. Bezemer     |020112|
| Added [IGNORE], DoIgnore()                       | J.L. Bezemer     |180312|
| Fixed [IGNORE] bug                               | J.L. Bezemer     |280312|
| Changed AddSymbol(), added "Name too long" error | J.L. Bezemer     |090412|
| Added CFIELD:                                    | J.L. Bezemer     |310712|
| Added OptimizeVariable()                         | J.L. Bezemer     |010812|
| Removed INC, DEC; changed DoChop()               | J.L. Bezemer     |090812|
| Added OptimizeNegate()                           | J.L. Bezemer     |180812|
| Changed OptimizeLiteral(), OptimizePLiteral()    | J.L. Bezemer     |241012|
| Changed OptimizeExit(), OptimizeVariable()       | J.L. Bezemer     |241012|
| Changed Optimized(), CompileOffset()             | J.L. Bezemer     |241012|
| Added OptimizeDLiteral(), OptimizeMLiteral()     | J.L. Bezemer     |241012|
| Added CompileConstant(), DoDConstant()           | J.L. Bezemer     |241012|
| Added MLITERAL, DLITERAL                         | J.L. Bezemer     |241012|
| Added DoMConstant(), removed OptimizeNegate()    | J.L. Bezemer     |241012|
| Removed DoAdd(), DoMultiply(), DoDivide()        | J.L. Bezemer     |241012|
| Removed DoNegate(), LEFT2, RIGHT2                | J.L. Bezemer     |241012|
| Reinstated LEFT2 and RIGHT2                      | J.L. Bezemer     |251012|
| Changed OptimizeDLiteral(), OptimizeMLiteral()   | J.L. Bezemer     |271012|
| Removed LEFT2, added SMOVE                       | J.L. Bezemer     |021212|
| Added LATEST, DoLatest()                         | J.L. Bezemer     |161212|
| Changed GetSymbol(), removed DoLatest()          | J.L. Bezemer     |171212|
| Fixed several peephole optimizers for ErrLine = 0| J.L. Bezemer     |311212|
| Changed DoPLoop(), added optimization            | J.L. Bezemer     |060113|
| Changed SkipSource(), less murky                 | J.L. Bezemer     |130213|
| Changed SkipSource(), GetImmediate() - old bug!  | J.L. Bezemer     |150213|
| Added EQUATES, DoEquates()                       | J.L. Bezemer     |160313|
| Added :TOKEN, DoToken()                          | J.L. Bezemer     |220313|
| Fixed bug in DoCloseParen()                      | J.L. Bezemer     |260313|
| [*], [/], [+] and [NEGATE] removed               | J.L. Bezemer     |270913|
| Added quotations, [: and ;]                      | J.L. Bezemer     |141013|
| Rewrote GetSymbol(), less murky                  | J.L. Bezemer     |041213|
| Fixed silly calloc() error in DoOpen()           | J.L. Bezemer     |030114|
| Added C", C|, DoCQuote()                         | J.L. Bezemer     |140114|
+--------------------------------------------------+------------------+------+
|REMARKS                                           |    Programmer    | Date |
+--------------------------------------------------+------------------+------+
| Special thanks to Reuben Thomas for ANSI-C code  | J.L. Bezemer     |151199|
+--------------------------------------------------+------------------+------+

  Copyright (C) 1994,2014 J.L. Bezemer

  This file is part of 4tH

  4tH is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 3
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.


This is the actual 4tH single-pass compiler. It tokenizes all built-in
keywords, resolves jump-addresses and builds the symboltable. It returns
a pointer to the H-code in memory.

Prototype: Hcode* comp_4th (char *Program)
Returns  : a pointer to Hcode on succes; else NULL
Memory   : the size of the source, the size of a dict entry times the number
           of dict entries, a fixed linktable, a dynamic symboltable, an
           object header; most of it is freed or realloced at exit - only
           the resources of the Hcode remain
Example  :


#include "4th.h"
#include <stdlib.h>

#ifndef ARCHAIC
  int main (int argc, char **argv)
#else
  int main (argc, argv) int argc; char **argv;
#endif

{
  Hcode *object;
  char  *sources;
  size_t fsize;

  if (argc == 2)
    {
      if ((sources = open_4th (argv [1])) == NULL)
         printf ("Loading; \'%s\' does not exist or too large\n", argv [2]);
      else
        {
          object = comp_4th (sources);
          printf ("Compile; word %u: %s\n", object->ErrLine,
                  errs_4th [object->ErrNo]);
          dump_4th (object, stdout, 0, -1);
          return (EXIT_SUCCESS);
        }
    }
  return (EXIT_FAILURE);
}


Input    : None
Output   : depends on program
Related  : dump_4th(), exec_4th()
*/

#ifdef USRLIB4TH
#include <4th.h>
#include <sys/cmds_4th.h>
#else
#include "4th.h"
#include "cmds_4th.h"
#endif

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

#define LASTW     1                    /* last word compiled */
#define NEXTW     0                    /* next word to be compiled */

#define R_BEGIN   1
#define R_IF      2
#define R_DO      3
#define R_WHILE   4
#define R_COLON   5

#define W_SEARCH  0
#define W_EXEC    1
#define W_STRING  2

#define MISSING   (-1)
#define FOUND     (-2)

#define WHITE     "\x04\x1a\x09\x0a\x0d\x20"
#define EOL       "\x0a\x0d\x04\x1a"

#ifdef __TURBOC__
typedef unsigned mark;                 /* marker for parser */
#else
typedef long mark;                     /* 64K on TurboC */
#endif

typedef char ref;                      /* reference link table */

typedef struct {
  ref Mark;                            /* type of conditional */
  int Address;                         /* address of conditional */
} Link;

typedef struct {
  unit Token;                          /* compiled token */
  cell Value;                          /* compiled argument */
  char Name [SYMLEN];                  /* name of symbol */
} Symbol;

typedef struct {
  char *Prev;                          /* points to previously parsed word */
  char *Curr;                          /* points to currently parsed word */
  mark  Next;                          /* start of text to be parsed */
  mark  End;                           /* end of file (without terminator) */
} ParseRegs;

typedef struct {
   char  Wlen;                         /* length of symbol */
   char *Wname;                        /* name of symbol */
   unit  Wtok;                         /* 4th token of symbol */
} Word4th;

typedef struct {
   char  Clen;                         /* length of symbol */
   char *Cname;                        /* name of symbol */
   unit  Ctok;                         /* 4th token of symbol */
   cell  Cval;                         /* 4th value of symbol */
} Const4th;

typedef struct {
   char        Ilen;                   /* length of symbol */
   signed char InoSymbols;             /* number of symbols */
   signed char InoWords;               /* number of tokens */
   char       *Iname;                  /* name of symbol */
   char       *Idelimit;               /* string delimiter */
#ifdef ARCHAIC
   void      (*Ifun) ();               /* 4th function (K&R) */
#else
   void      (*Ifun) (void);           /* 4th function (ANSI) */
#endif
} Immed4th;

static char   *Cursor;                 /* word cursor */
static char   *CurrentWord;            /* word currently evaluated */
static char    Assert;                 /* assertion turned off */
static int     Fence;                  /* don't optimize beyond this point */
static int     Optimization;           /* peephole optimizer turned off */
static int     Base;                   /* holds the radix to convert nums */
static int     ToCS;                   /* top of Control Stack */
static int     SymTablep;              /* top of symbol table */
static int     SourceSymbols;          /* size of symbol table */
static int     SourceStrings;          /* number of individual strings */
static int     SourceCorrection;       /* correction for word allocation */
static int     CompiledStrings;        /* counts compiled sourcewords */
static Link   *ControlStack;           /* pointer to Control Stack */
static Symbol *SymTable;               /* pointer to symbol table */
static Hcode  *Object;                 /* pointer to program structure */

static void AddSymbol __PROTO((unit Stoken, cell Svalue, char* Sname));
static int  SearchDictionary __PROTO((char* Name, char Action));
static int  GetImmediate __PROTO((char *symbol, char mode));

/*
This routine compares two strings. Some implementations provide a case
insensitive function like stricmp(). If that is the case, this function
can be used. If such a function is not available, one is provided here.
It returns zero if both strings match and nonzero if they don't.
*/

#ifdef STRICMP
#define MatchName(a,b) stricmp(a,b)
#else
#ifndef ARCHAIC
  static int MatchName (char *str1, char * str2)
#else
  static int MatchName (str1, str2) char *str1; char * str2;
#endif
{
  for (;toupper ((int) *str1) == toupper ((int) *str2); str1++, str2++)
      if (*str1 == '\0') return (0);
  return (toupper ((int) *str1) - toupper ((int) *str2));
}
#endif


/*
This routine gets a string from the parsed text. It keeps track of the current
position of the cursor. White spaces are transparantly skipped.
*/

#ifndef ARCHAIC
  static void GetNextWord (void)
#else
  static void GetNextWord ()
#endif

{
  if (CompiledStrings < SourceStrings)
     {                                 /* Skip null strings */
       for (CurrentWord = Cursor; ! *CurrentWord; CurrentWord++);
       Cursor = CurrentWord + (strlen (CurrentWord) + 1);
       CompiledStrings++;              /* String was read */
     }
  else CurrentWord = NULL;             /* return if all strings read */
}


/*
This routine moves the string of any ." and ," command to the top of the
sourcefile and returns the addres where it has been stored
*/

#ifndef ARCHAIC
  static cell MoveString (void)
#else
  static cell MoveString ()
#endif

{
  cell t = (cell) Object->StringSiz;

  strcpy (Object->StringSeg + Object->StringSiz, CurrentWord);
  Object->StringSiz += (strlen (Object->StringSeg + Object->StringSiz) + 1);
  return (t);
}


/*
This word optimizes LITERALs by making divisions.
*/

#ifndef ARCHAIC
  static char OptimizeDLiteral (cell Argument)
#else
  static char OptimizeDLiteral (Argument) cell Argument;
#endif

{
  dict* Instruction = &(Object->CodeSeg [Object->ErrLine - 1]);
                                       /* a /literal(1) is useless */
  if ((Optimization) && (Argument == 1L)) return (TRUE);
  if ((Optimization) && (Object->ErrLine > Fence))
     {                                 /* if optimization is on */
       if (Argument == 0L)             /* check for division by zero */
          {
            Object->ErrNo = M4DIVBY0;  /* raise error */
            return (TRUE);             /* don't compile anything */
          }
       else
          {                            /* and throw exception if needed */
            if (Instruction->Word == LITERAL)
               {                       /* if previous bytecode was literal */
                 Instruction->Value /= Argument; return (TRUE);
               }                       /* divide bytecode by /literal */
                                       /* previous constant was a /literal */
            if (Instruction->Word == DLITERAL)
               {                       /* if previous bytecode was /literal */
                 Instruction->Value *= Argument; return (TRUE);
               }                       /* multiply both divisors */
          }
     }                                 /* at compile time */
  return (FALSE);                      /* signal nothing optimized */
}


/*
This word optimizes LITERALs by making multiplications.
*/

#ifndef ARCHAIC
  static char OptimizeMLiteral (cell Argument)
#else
  static char OptimizeMLiteral (Argument) cell Argument;
#endif

{
  dict* Instruction = &(Object->CodeSeg [Object->ErrLine - 1]);
                                       /* a *literal(1) is useless */
  if ((Optimization) && (Argument == 1L)) return (TRUE);
  if ((Optimization) && (Object->ErrLine > Fence))
     if ((Instruction->Word == LITERAL) || (Instruction->Word == MLITERAL))
        {                              /* if previous bytecode is suitable */
          Instruction->Value *= Argument; return (TRUE);
        }                              /* multiply bytecode by *literal */
                                       /* at compile time */
  return (FALSE);                      /* signal nothing optimized */
}


/*
This word optimizes LITERALs, PLITERALs and VARIABLEs by making additions.
*/

#ifndef ARCHAIC
  static char OptimizePLiteral (cell Argument)
#else
  static char OptimizePLiteral (Argument) cell Argument;
#endif

{
  dict* Instruction = &(Object->CodeSeg [Object->ErrLine - 1]);
                                       /* a +literal(0) is useless */
  if ((Optimization) && (Argument == 0L)) return (TRUE);
  if ((Optimization) && (Object->ErrLine > Fence))
     if ((Instruction->Word == LITERAL) || (Instruction->Word == PLITERAL)
                                        || (Instruction->Word == VARIABLE))
        {                              /* if optimization is on */
          Instruction->Value += Argument; return (TRUE);
        }                              /* add the +literal to bytecode */
                                       /* at compile time */
  return (FALSE);                      /* signal nothing optimized */
}


/*
This word optimizes LITERALs by creating +CONSTANTs, /CONSTANTs and *CONSTANTs
*/

#ifndef ARCHAIC
  static char OptimizeLiteral (unit Command)
#else
  static char OptimizeLiteral (Command) unit Command;
#endif

{
  dict* Instruction = &(Object->CodeSeg [Object->ErrLine - 1]);

  if ((Optimization) && (Object->ErrLine > Fence))
     if (Instruction->Word == LITERAL) /* is it a literal and optimization */
        {                              /* if '-' or 'NEGATE' */
          if ((Command == NEGATE) || (Command == MINUS))
             Instruction->Value = -(Instruction->Value); 
                                       /* change the sign accordingly */
          Object->ErrLine--;           /* prepare to optimize more */
          switch (Command)             /* move to previous bytecode */
            {                          /* select optimization routine */
               case (NEGATE): Object->ErrLine++; break;
               case (DIV):    Instruction->Word = DLITERAL;
                              if (! OptimizeDLiteral (Instruction->Value))
                                 Object->ErrLine++;
                              break;   /* no optimization, so adjust */
               case (MUL):    Instruction->Word = MLITERAL;
                              if (! OptimizeMLiteral (Instruction->Value))
                                 Object->ErrLine++;
                              break;   /* no optimization, so adjust */
               default:       Instruction->Word = PLITERAL;
                              if (! OptimizePLiteral (Instruction->Value))
                                 Object->ErrLine++;
                              break;   /* no optimization, so adjust */
            }                          /* at this stage something has */
          return (TRUE);               /* been optimized, so signal it */
        }

  return (FALSE);                      /* signal nothing optimized */
}


/*
This word optimizes a VARIABLE by changing it to VALUE or TO.
*/

#ifndef ARCHAIC
  static char OptimizeVariable (unit Command)
#else
  static char OptimizeVariable (Command) unit Command;
#endif 

{
  dict* Instruction = &(Object->CodeSeg [Object->ErrLine - 1]);

  if ((Optimization) && (Object->ErrLine > Fence))
     if (Instruction->Word == VARIABLE)  /* check for proper bytecode */
        {                                /* transform to a value */
          if (Command == FETCH) Instruction->Word = VALUE;
          else Instruction->Word = TO;
          return (TRUE);
        }                                /* nothing left to compile */

  return (FALSE);
}


/*
This word optimizes an EXIT by applying tail call optimization.
*/

#ifndef ARCHAIC
  static char OptimizeExit (void)
#else
  static char OptimizeExit ()
#endif 

{
  dict* Instruction = &(Object->CodeSeg [Object->ErrLine - 1]);

  if ((Optimization) && (Object->ErrLine > 0))
     if (Instruction->Word == CALL)    /* if call to user defined word */
        {                              /* apply tail call recursion */
          Instruction->Word = BRANCH; return (Object->ErrLine > Fence);
        }                              /* compile an EXIT? */

  return (FALSE);
}


/*
This word optimizes selected words using peephole optimization.
*/

#ifndef ARCHAIC
  static char Optimized (unit Command, cell Argument)
#else
  static char Optimized (Command, Argument) unit Command; cell Argument;
#endif

{
  switch (Command)
    {
      case (MUL):
      case (DIV):
      case (MINUS):
      case (PLUS):
      case (NEGATE):   return (OptimizeLiteral  (Command));
      case (STORE):
      case (FETCH):    return (OptimizeVariable (Command));
      case (PLITERAL): return (OptimizePLiteral (Argument));
      case (MLITERAL): return (OptimizeMLiteral (Argument));
      case (DLITERAL): return (OptimizeDLiteral (Argument));
      case (EXIT):     return (OptimizeExit     ());
      default:         return (FALSE);
    }
}


/*
This word simply compiles Command and Argument at Object->ErrLine.
*/

#ifndef ARCHAIC
  static void CompileWord (unit Command, cell Argument)
#else
  static void CompileWord (Command, Argument) unit Command; cell Argument;
#endif

{                                      /* resolve [IGNORE] directive */
  if ((Command == STRINGD) && (Argument < 0L)) return;
  if (! Object->ErrNo)                 /* no compiling if error */
     {                                 /* check if still within range */
       if (Object->ErrLine < Object->CodeSiz)
          {                            /* call peephole optimizer, */
            if (Optimized (Command, Argument)) return;
            Object->CodeSeg [Object->ErrLine].Word = Command;
            Object->CodeSeg [Object->ErrLine++].Value = Argument;
            Optimization = TRUE;       /* enable optimizer */
          }
       else Object->ErrNo = M4BADOBJ;
     }
}


/*
This word simply compiles CmdN commands (without argument) at Object->ErrLine.
It is used for inline macros.
*/

#ifndef ARCHAIC
  static void InlineWords (int CmdN, ...)
#else
  static void InlineWords (CmdN) int CmdN;
#endif

{
  va_list Cmds;
  int x;

  va_start (Cmds, CmdN); 
  for (x = 0; x < CmdN; x++) CompileWord ((unit) va_arg (Cmds, int), 0L);
  va_end (Cmds);
}


static Word4th WordList [] =  {        /* list of all "simple" commands */
  { 1, ".", DOT },                     /* in order of length, important! */
  { 1, "@", FETCH },
  { 1, "!", STORE },
  { 1, "+", PLUS },
  { 1, "-", MINUS },
  { 1, "*", MUL },
  { 1, "/", DIV },
  { 1, "=", EQ },
  { 1, ">", GT },
  { 1, "<", LT },
  { 1, "I", RCOPY },
  { 1, "J", RCOPY3 },
  { 1, "#", SHARP },
  { 2, "CR", CR },
  { 2, "@C", FETCHC },
  { 2, "C@", CFETCH },
  { 2, "C!", CSTORE },
  { 2, "2/", RIGHT2 },
  { 2, "*/", STARSLSH },
  { 2, "<>", NE },
  { 2, "0<", LT0 },
  { 2, "0>", GT0 },
  { 2, "TH", PLUS },
  { 2, ">R", RPUT },
  { 2, "R>", RGET },
  { 2, "R@", RCOPY },
  { 2, ".R", DOTR },
  { 2, "<#", LSHARP },
  { 2, "0=", EQ0 },
  { 2, "+!", ADDSTORE },
  { 2, "OR", OR },
  { 2, "#>", RSHARP },
  { 2, "#S", SHARPS },
  { 3, "0<>", NE0 },
  { 3, "NOT", EQ0 },
  { 3, "MOD", MOD },
  { 3, "DUP", DUP},
  { 3, "RP@", RPFETCH },
  { 3, "SP@", SPFETCH },
  { 3, "ROT", ROT },
  { 3, "AND", AND },
  { 3, "XOR", XOR },
  { 3, "ABS", ABS },
  { 3, "MIN", MIN },
  { 3, "MAX", MAX },
  { 3, "USE", USE },
  { 4, "SEEK", FSEEK },
  { 4, "TELL", FTELL },
  { 4, "HOLD", HOLD },
  { 4, "SIGN", SIGN },
  { 4, "EXIT", EXIT },
  { 4, "/MOD", SLASHMOD },
  { 4, "TIME", TIME },
  { 4, "EMIT", EMIT },
  { 4, "OVER", OVER },
  { 4, "SWAP", SWAP },
  { 4, "TYPE", TYPE },
  { 4, "FILL", FILL },
  { 4, "OMIT", OMIT },
  { 4, "DROP", DROP },
  { 4, "QUIT", QUIT },
  { 4, "MOVE", CMOVE },
  { 4, "OPEN", FOPEN },
  { 4, "ARGS", ARGS },
  { 4, "ARGN", ARGN },
  { 4, "SYNC", FSYNC },
  { 5, "ABORT", QUIT },
  { 5, "PARSE", PARSE },
  { 5, "PLACE", PLACE },
  { 5, "CLOSE", FCLOSE },
  { 5, "DEPTH", SPFETCH },
  { 5, "PAUSE", PAUSE },
  { 5, "COUNT", COUNT },
  { 5, "CMOVE", CMOVE },
  { 5, "SMOVE", SMOVE },
  { 5, "SHIFT", SHIFT },
  { 5, "LEAVE", LEAVE },
  { 5, "THROW", THROW },
  { 6, "REFILL", REFILL },
  { 6, "CMOVE>", CMOVE },
  { 6, "SPACES", SPACES },
  { 6, "NUMBER", NUMBER },
  { 6, "LSHIFT", SHIFT },
  { 6, "NEGATE", NEGATE },
  { 6, "ACCEPT", ACCEPT },
  { 6, "INVERT", INVERT },
  { 7, "EXECUTE", EXECUTE },
  { 8, "ENVIRON@", ENVFETCH },
  { 9, "-TRAILING", TRAILING },
  { 11, "DELETE-FILE", DELFILE },
  { CHAR_MAX, "", NOOP }        /* terminator of wordlist */
};


/*
This routine returns the index of the word in the wordlist (if found).
If it is not found in the wordlist it returns MISSING.
*/

#ifndef ARCHAIC
  static int GetWord (char *symbol, char mode)
#else
  static int GetWord (symbol, mode) char *symbol; char mode;
#endif

{
  int x;                               /* simple counter */
  unsigned len = strlen (symbol);

  for (x = 0; len > WordList [x].Wlen; x++);
  for (;len == WordList [x].Wlen; x++)
      if (! MatchName (WordList [x].Wname, symbol))
         {
           if (mode == W_EXEC) CompileWord (WordList [x].Wtok, 0L);
           return (x);
         }

  return (MISSING);
}


static Const4th ConstList [] =  {
  { 2, "1+", PLITERAL, 1L },
  { 2, "1-", PLITERAL, -1L },
  { 2, "2*", MLITERAL, 2L },
  { 2, "BL", LITERAL, (cell) ' ' },
  { 2, "HI", ENVIRON, VHI },
  { 2, "LO", LITERAL, PADSIZ+TIBSIZ },
  { 3, "TIB", LITERAL, TIB },
  { 3, "HEX", RADIX, 16L },
  { 3, "PAD", LITERAL, PAD },
  { 3, ">IN", LITERAL, VIN },
  { 3, "OUT", LITERAL, VOUT },
  { 3, "APP", LITERAL, VAR4TH },
  { 3, "CIN", ENVIRON, VCIN },
  { 4, "COUT", ENVIRON, VCOUT },
  { 4, "4TH#", LITERAL, Version4th },
  { 4, "/PAD", LITERAL, PADSIZ },
  { 4, "/TIB", LITERAL, TIBSIZ },
  { 4, "BASE", LITERAL, VBASE },
  { 4, "TRUE", LITERAL, F_T },
  { 4, "VARS", LITERAL, 0L },
  { 4, "PIPE", LITERAL, F4_PIPE },
  { 4, "LAST", ENVIRON, VLAST },
  { 5, "CHAR+", PLITERAL, 1L },
  { 5, "CHAR-", PLITERAL, -1L },
  { 5, "CELL+", PLITERAL, 1L },
  { 5, "CELL-", PLITERAL, -1L },
  { 5, "FIRST", ENVIRON, VFIRST },
  { 5, "/CELL", LITERAL, (cell) sizeof (cell) },
  { 5, "/CHAR", LITERAL, (cell) sizeof (unit) },
  { 5, "/HOLD", LITERAL, DOTSIZ },
  { 5, "FALSE", LITERAL, F_F },
  { 5, "WIDTH", LITERAL, SYMLEN - 1 },
  { 5, "MAX-N", LITERAL, CELL_MAX },
  { 5, "OCTAL", RADIX, 8L },
  { 5, "FILES", LITERAL, MAXDEVS },
  { 5, "INPUT", LITERAL, F4_READ },
  { 5, "STDIN", LITERAL, STD4IN },
  { 6, "STDOUT", LITERAL, STD4OUT },
  { 6, "OUTPUT", LITERAL, F4_WRITE },
  { 6, "APPEND", LITERAL, F4_APPND },
  { 6, "STRUCT", LITERAL, 0L },
  { 7, "(ERROR)", LITERAL, CELL_MIN },
  { 7, "DECIMAL", RADIX, 10L },
  { 9, "SOURCE-ID", ENVIRON, VCIN },
  { 11, "STACK-CELLS", LITERAL, STACKSIZ },
  { CHAR_MAX, "", LITERAL, 0L }        /* terminator of constant list */
};


/*
This routine returns the index of the word in the constlist (if found).
If it is not found in the constlist it returns MISSING.
*/

#ifndef ARCHAIC
  static int GetConstant (char *symbol, char mode)
#else
  static int GetConstant (symbol, mode) char *symbol; char mode;
#endif

{
  int x;                               /* simple counter */
  unsigned len = strlen (symbol);

  for (x = 0; len > ConstList [x].Clen; x++);
  for (;len == ConstList [x].Clen; x++)
      if (! MatchName (ConstList [x].Cname, symbol))
         {
           if (mode == W_EXEC)
              CompileWord (ConstList [x].Ctok, ConstList [x].Cval);
           return (x);
         }

  return (MISSING);
}


/*
This routine searches the symbol table for a certain symbol. If it is
succesful it will return the number of the entry, else MISSING.
Note LATEST is a special word that always returns the last definition.
*/

#ifndef ARCHAIC
  static int GetSymbol (char *Symbol, char mode)
#else
  static int GetSymbol (Symbol, mode) char *Symbol; char mode;
#endif

{
  int x;                               /* search index */
                                       /* LATEST returns last defined word */
  if ((! MatchName ("LATEST", Symbol)) && (SymTablep > 0)) x = SymTablep - 1;
  else                                 /* otherwise search the symboltable */
    for (x = 0; x < SymTablep; x++)    /* if found, stop the search */
        if (! MatchName (SymTable [x].Name, Symbol)) break;

  if (x < SymTablep)                   /* if found, compile the opcode */
     {                                 /* if seleced by mode */
       if (mode == W_EXEC)
          CompileWord (SymTable [x].Token, SymTable [x].Value);
       return (x);                     /* return the entry */
     }                                 /* otherwise signal 'not found' */

  return (MISSING);
}


/*
This function decodes a word declaration like in 'DEF <str>'. If a name
could be retrieved it returns TRUE. If not, it sets ErrNo and returns FALSE.
*/

#ifndef ARCHAIC
  static char DecodeWord (unsigned ErrCode)
#else
  static char DecodeWord (ErrCode) unsigned ErrCode;
#endif

{
  GetNextWord();
  if (CurrentWord == NULL) Object->ErrNo = ErrCode;
  else return (TRUE);
  return (FALSE);
}


/*
This function decodes a name declaration like in 'DEF <str>'. If the name
is in the symboltable, it returns the entry. If not, it sets ErrNo and returns
MISSING.
*/

#ifndef ARCHAIC
  static int DecodeName (void)
#else
  static int DecodeName ()
#endif

{
  int y = MISSING;

  if (DecodeWord (M4NODECL))
     if ((y = GetSymbol (CurrentWord, W_SEARCH)) == MISSING)
        Object->ErrNo = M4NONAME;

  return (y);
}


/*
This function decodes a destructive declaration like '<x> DEF'.
It checks all components and returns operand <x>.
*/

#ifndef ARCHAIC
  static cell DecodeOperand (unit OpCode, unsigned ErrCode)
#else
  static cell DecodeOperand (OpCode, ErrCode) unit OpCode; unsigned ErrCode;
#endif

{
  if (Object->ErrLine == 0) Object->ErrNo = M4NODECL;
  else
    {
      if (Object->CodeSeg [Object->ErrLine - 1].Word != OpCode)
         Object->ErrNo = ErrCode;
      else return (Object->CodeSeg [--Object->ErrLine].Value);
    }
  return (CELL_MIN);
}


/*
This function decodes a destructive declaration like '<n> DEF'.
It returns literal <n>.
*/

#ifndef ARCHAIC
  static cell DecodeLiteral (void)
#else
  static cell DecodeLiteral ()
#endif

{
  return (DecodeOperand (LITERAL, M4BADLIT));
}


/*
This function decodes a declaration like '<n> DEF <name>'. It checks all
components, sets CurrentWord to <name> and returns <n>.
*/

#ifndef ARCHAIC
  static cell DecodeSymbol (void)
#else
  static cell DecodeSymbol ()
#endif

{
  cell val = DecodeLiteral ();

  if (! Object->ErrNo)
     if (DecodeWord (M4NODECL)) return (val);

  return (CELL_MIN);
}


/*
This function creates a symbol from the CurrentWord after checking
it is there.
*/

#ifndef ARCHAIC
  static void MakeSymbol (unit Stoken, cell Svalue)
#else
  static void MakeSymbol (Stoken, Svalue) unit Stoken; cell Svalue;
#endif

{
  if (DecodeWord (M4NODECL)) AddSymbol (Stoken, Svalue, CurrentWord);
}


/*
This function skips source until the marker CloseWord is found. In order to
allow embedded pairs, the Level is taken into account. AltWord is usually
NULL, except when evaluating [ELSE]. Note that the string parameters of
immediate words are explicitly skipped, because this function cannot
distinguish words and strings.
*/

#ifndef ARCHAIC
  static void SkipSource (char *OpenWord, char *CloseWord, char *AltWord)
#else
  static void SkipSource (OpenWord, CloseWord, AltWord) 
         char *OpenWord; char *CloseWord; char *AltWord;
#endif

{
  int Level = 1;

  while (Level)                        /* execute at least once */
    {
      if (! DecodeWord (M4NODECL)) break;
      else                             /* if a word is available */
        {                              /* open new pair */
          if (! MatchName (CurrentWord, OpenWord)) Level++;
          if ((AltWord != NULL) && (Level == 1))
             if (! MatchName (CurrentWord, AltWord)) Level--;
          if  (! MatchName (CurrentWord, CloseWord)) Level--;
          if (GetImmediate (CurrentWord, W_STRING) > 0) DecodeWord (M4NOSTR);
        }                              /* stop if closing word found */
    }
}


/*
This word pushes a link on the stack. "marker" contains the reference,
Object->ErrLine is known.
*/

#ifndef ARCHAIC
  static void MarkLink (ref marker)
#else
  static void MarkLink (marker) ref marker;
#endif

{
  if (ToCS < LINKSIZ)
     {
       ControlStack [ToCS].Mark = marker;
       ControlStack [ToCS++].Address = Object->ErrLine - 1;
     }
  else Object->ErrNo = M4NONEST;       /* nesting too deep */
}


/*
This routine is in fact a translation of the Forth word ?PAIRS.
It returns the pushed address, provided the reference in "marker"
is correct.
*/

#ifndef ARCHAIC
  static int PairLink (ref marker)
#else
  static int PairLink (marker) ref marker;
#endif

{
  if (ToCS > 0)
     if (ControlStack [--ToCS].Mark == marker)
        return (ControlStack [ToCS].Address);

  Object->ErrNo = M4NOJUMP;
  return (INT_MIN);
}


/*
This routine makes a backlink. That means the address to be patched
is returned from the stack and points to an already compiled command.
"offset" is needed, because in some conditionals the word has not
been compiled yet (REPEAT).
*/

#ifndef ARCHAIC
  static void MakeLink (ref marker, int offset)
#else
  static void MakeLink (marker, offset) ref marker; int offset;
#endif

{
  int link = PairLink (marker);

  if (! Object->ErrNo)
     Object->CodeSeg [link].Value = Object->ErrLine - offset;
}


/*
This function compiles a marker.
*/

#ifndef ARCHAIC
  static void CompileMark (unit Mtoken, ref marker)
#else
  static void CompileMark (Mtoken, marker) unit Mtoken; ref marker;
#endif

{
  CompileWord (Mtoken, 0L);
  MarkLink (marker);
}


/*
This function compiles a string.
*/

#ifndef ARCHAIC
  static void CompileString (unit Stoken)
#else
  static void CompileString (Stoken) unit Stoken;
#endif

{
  if (DecodeWord (M4NOSTR))
     CompileWord (Stoken, MoveString ());
}


/*
This function compiles a REPEAT, AGAIN or UNTIL.
*/

#ifndef ARCHAIC
  static void CompileAgain (unit AgainToken)
#else
  static void CompileAgain (AgainToken) unit AgainToken;
#endif

{
  while ((ToCS > 0) && (ControlStack [ToCS - 1].Mark == R_WHILE))
        MakeLink (R_WHILE, NEXTW);
  CompileWord (AgainToken, PairLink (R_BEGIN));
}


/*
This function compiles a LOOP or +LOOP.
*/

#ifndef ARCHAIC
  static void CompileLoop (unit LoopToken)
#else
  static void CompileLoop (LoopToken) unit LoopToken;
#endif

{
  int link = PairLink (R_DO);

  if (! Object->ErrNo)
     {
       Object->CodeSeg [link].Value = Object->ErrLine;
       CompileWord (LoopToken, link);
     }
}


/*
This function compiles a VALUE, DEFER, FILE, IS or TO.
*/

#ifndef ARCHAIC
  static void CompileValue (unit ValueToken)
#else
  static void CompileValue (ValueToken) unit ValueToken;
#endif

{
  cell val;
  int  y;

  if (DecodeWord (M4NODECL))
    {
      if ((y = GetSymbol (CurrentWord, W_SEARCH)) == MISSING)
         AddSymbol (ValueToken, (val = Object->Variables++), CurrentWord);
      else
         {
           if (SymTable [y].Token != ValueToken) Object->ErrNo = M4NOTYPE;
           val = SymTable [y].Value;
         }

      CompileWord (TO, val);
    }
}


/*
This function compiles an ENUM or FIELD.
*/

#ifndef ARCHAIC
  static void CompileOffset (cell Increment, unit OffsToken)
#else
  static void CompileOffset (Increment, OffsToken) cell Increment;
         unit OffsToken;
#endif

{
  cell a = DecodeSymbol ();

  if (! Object->ErrNo) 
     {
       AddSymbol (OffsToken, a, CurrentWord);
       CompileWord (LITERAL, a + Increment);
     }
}


/*
This function compiles a CONSTANT, +CONSTANT, *CONSTANT or /CONSTANT.
*/

#ifndef ARCHAIC
  static void CompileConstant (unit ConstToken)
#else
  static void CompileConstant (ConstToken) unit ConstToken;
#endif

{
  cell val = DecodeSymbol ();
  if (! Object->ErrNo) AddSymbol (ConstToken, val, CurrentWord);
}


/*
This function compiles a :REDO or DOES>.
*/

#ifndef ARCHAIC
  static void CompileDoes (int p)
#else
  static void CompileDoes (p) int p;
#endif

{
  int x;

  if ((SymTable [p].Token != VARIABLE) && (SymTable [p].Token != LITERAL))
     Object->ErrNo = M4NOTYPE;
  else 
     {
       x = Object->ErrLine;
       CompileMark (BRANCH, R_COLON);
       CompileWord (SymTable [p].Token, SymTable [p].Value);
       SymTable [p].Token = CALL;
       SymTable [p].Value = x;
     }
}


/*
This function compiles an IF.
*/

#ifndef ARCHAIC
  static void DoIf (void)
#else
  static void DoIf ()
#endif

{
  CompileMark (BRANCH0, R_IF);
}


/*
This function compiles an ELSE.
*/

#ifndef ARCHAIC
  static void DoElse (void)
#else
  static void DoElse ()
#endif

{
  MakeLink (R_IF, NEXTW);
  CompileMark (BRANCH, R_IF);
}


/*
This function compiles a THEN.
*/

#ifndef ARCHAIC
  static void DoThen (void)
#else
  static void DoThen ()
#endif

{
  MakeLink (R_IF, LASTW); 
  Fence = Object->ErrLine;             /* disable optimizer */
}


/*
This function compiles a BEGIN.
*/

#ifndef ARCHAIC
  static void DoBegin (void)
#else
  static void DoBegin ()
#endif

{
  MarkLink (R_BEGIN);
  Fence = Object->ErrLine;             /* disable optimizer */
}


/*
This function compiles a WHILE.
*/

#ifndef ARCHAIC
  static void DoWhile (void)
#else
  static void DoWhile ()
#endif

{
  CompileMark (BRANCH0, R_WHILE);
}


/*
This function compiles a DONE.
*/

#ifndef ARCHAIC
  static void DoDone (void)
#else
  static void DoDone ()
#endif

{
  MakeLink (R_WHILE, NEXTW);
  CompileMark (BRANCH, R_WHILE);
}


/*
This function compiles REPEAT and AGAIN.
*/

#ifndef ARCHAIC
  static void DoRepeat (void)
#else
  static void DoRepeat ()
#endif

{
  CompileAgain (BRANCH);
}


/*
This function compiles an UNTIL.
*/

#ifndef ARCHAIC
  static void DoUntil (void)
#else
  static void DoUntil ()
#endif

{
  CompileAgain (BRANCH0);
}


/*
This function compiles a ?DO.
*/

#ifndef ARCHAIC
  static void DoQDo (void)
#else
  static void DoQDo ()
#endif

{
  CompileMark (QDO, R_DO);
}


/*
This function compiles a DO.
*/

#ifndef ARCHAIC
  static void DoDo (void)
#else
  static void DoDo ()
#endif

{
  CompileMark (DO, R_DO);
}


/*
This function compiles a LOOP.
*/

#ifndef ARCHAIC
  static void DoLoop (void)
#else
  static void DoLoop ()
#endif

{
  CompileLoop (LOOP);
}


/*
This function compiles a +LOOP. It does some optimization.
*/

#ifndef ARCHAIC
  static void DoPLoop (void)
#else
  static void DoPLoop ()
#endif

{                                      /* we have to catch it here */
  dict* Instruction = &(Object->CodeSeg [Object->ErrLine - 1]);
                                       /* otherwise it becomes ugly */
  if (Object->ErrLine > 0)             /* has anything been compiled */
     if ((Instruction->Word == LITERAL) && (Instruction->Value == 1L))
        {                              /* are we trying to compile 1 +LOOP */
          Object->ErrLine--; CompileLoop (LOOP); return;
        }                              /* if so, optimize it */

  CompileLoop (PLOOP);                 /* if not, compile a +LOOP */
}


/*
This function compiles a ':'.
*/

#ifndef ARCHAIC
  static void DoColon (void)
#else
  static void DoColon ()
#endif

{
  if (DecodeWord (M4NODECL))
     {
       AddSymbol (CALL, Object->ErrLine, CurrentWord);
       CompileMark (BRANCH, R_COLON);
     }
}


/*
This function compiles a ':TOKEN'.
*/

#ifndef ARCHAIC
  static void DoToken (void)
#else
  static void DoToken ()
#endif

{
  if (DecodeWord (M4NODECL))
     {
       AddSymbol (LITERAL, Object->ErrLine, CurrentWord);
       CompileMark (BRANCH, R_COLON);
     }
}


/*
This function compiles a :NONAME.
*/

#ifndef ARCHAIC
  static void DoNoName (void)
#else
  static void DoNoName ()
#endif

{
  CompileWord (LITERAL, Object->ErrLine + 1);
  CompileMark (BRANCH, R_COLON);
}


/*
This function compiles a ';'.
*/

#ifndef ARCHAIC
  static void DoSColon (void)
#else
  static void DoSColon ()
#endif

{
  CompileWord (EXIT, 0L);
  MakeLink (R_COLON, LASTW);
}


/*
This function compiles an OFFSET.
*/

#ifndef ARCHAIC
  static void DoOffset (void)
#else
  static void DoOffset ()
#endif

{
  MakeSymbol (OFFSET, Object->StringSiz);
}


/*
This function compiles a 'C,'.
*/

#ifndef ARCHAIC
  static void DoCComma (void)
#else
  static void DoCComma ()
#endif
{
  cell val = DecodeLiteral ();

  if (! Object->ErrNo) Object->StringSeg [Object->StringSiz++] = (char) val;
}


/*
This function compiles a C" or C|
*/

#ifndef ARCHAIC
  static void DoCQuote (void)
#else
  static void DoCQuote ()
#endif

{
  char *c;                             /* pointer to the current word */

  if (DecodeWord (M4NOSTR))            /* error if no string found */
     for (c = CurrentWord; *c; c++)    /* use all printable characters */
         if (isprint ((int) *c)) Object->StringSeg [Object->StringSiz++] = *c;
}                                      /* copy them to the String Segment */


/*
This function compiles a CREATE.
*/

#ifndef ARCHAIC
  static void DoCreate (void)
#else
  static void DoCreate ()
#endif

{
  MakeSymbol (LITERAL, Object->ErrLine);
}


/*
This function compiles a VARIABLE.
*/

#ifndef ARCHAIC
  static void DoVariable (void)
#else
  static void DoVariable ()
#endif

{
  MakeSymbol (VARIABLE, Object->Variables++);
}


/*
This function compiles an [IGNORE]. It works by providing an invalid value
to STRINGD, which is later detected and ignored by CompileWord().
*/

#ifndef ARCHAIC
  static void DoIgnore (void)
#else
  static void DoIgnore ()
#endif

{
  MakeSymbol (STRINGD, CELL_MIN);
}


/*
This function compiles a RECURSE.
*/

#ifndef ARCHAIC
  static void DoRecurse (void)
#else
  static void DoRecurse ()
#endif

{
  int x = ToCS;

  while (x > 0)
    if (ControlStack [--x].Mark == R_COLON)
       {
         CompileWord (CALL, ControlStack [x].Address);
         return;
       }

  Object->ErrNo = M4NONAME;
}


/*
This function compiles a VALUE or TO.
*/

#ifndef ARCHAIC
  static void DoValue (void)
#else
  static void DoValue ()
#endif

{
  CompileValue (VALUE);
}


/*
This function compiles an IS.
*/

#ifndef ARCHAIC
  static void DoIs (void)
#else
  static void DoIs ()
#endif

{
  CompileValue (VECTOR);
}


/*
This function compiles a DEFER.
*/

#ifndef ARCHAIC
  static void DoDefer (void)
#else
  static void DoDefer ()
#endif

{
  CompileWord (LITERAL, CELL_MIN);
  DoIs ();
}


/*
This function compiles a FILE.
*/

#ifndef ARCHAIC
  static void DoFile (void)
#else
  static void DoFile ()
#endif

{
  CompileWord (LITERAL, CELL_MIN);
  DoValue ();
}


/*
This function compiles an ENUM.
*/

#ifndef ARCHAIC
  static void DoEnum (void)
#else
  static void DoEnum ()
#endif

{
  CompileOffset (1, LITERAL);
}


/*
This function compiles a +FIELD.
*/

#ifndef ARCHAIC
  static void DoPField (void)
#else
  static void DoPField ()
#endif

{
  CompileOffset (DecodeLiteral (), PLITERAL);
}


/*
This function compiles a FIELD:.
*/

#ifndef ARCHAIC
  static void DoFieldC (void)
#else
  static void DoFieldC ()
#endif

{
  CompileOffset (1, PLITERAL);
}


/*
This function compiles a /CONSTANT.
*/

#ifndef ARCHAIC
  static void DoDConstant (void)
#else
  static void DoDConstant ()
#endif

{
  CompileConstant (DLITERAL);
}


/*
This function compiles a *CONSTANT.
*/

#ifndef ARCHAIC
  static void DoMConstant (void)
#else
  static void DoMConstant ()
#endif

{
  CompileConstant (MLITERAL);
}


/*
This function compiles a +CONSTANT.
*/

#ifndef ARCHAIC
  static void DoPConstant (void)
#else
  static void DoPConstant ()
#endif

{
  CompileConstant (PLITERAL);
}


/*
This function compiles a CONSTANT or END-STRUCT.
*/

#ifndef ARCHAIC
  static void DoConstant (void)
#else
  static void DoConstant ()
#endif

{
  CompileConstant (LITERAL);
}


/*
This function compiles an EQUATES.
*/

#ifndef ARCHAIC
  static void DoEquates (void)
#else
  static void DoEquates ()
#endif

{
  cell val = DecodeOperand (VARIABLE, M4BADVAR);

  if (! Object->ErrNo) MakeSymbol (VARIABLE, val);
}


/*
This function compiles a SCONSTANT.
*/

#ifndef ARCHAIC
  static void DoSConstant (void)
#else
  static void DoSConstant ()
#endif

{
  cell val = DecodeOperand (SQUOTE, M4BADSTR);

  if (! Object->ErrNo) MakeSymbol (SQUOTE, val);
}


/*
This function compiles a [PRAGMA].
*/

#ifndef ARCHAIC
  static void DoPragma (void)
#else
  static void DoPragma ()
#endif

{
  MakeSymbol (LITERAL, F_T);
}


/*
This function compiles a STRING.
*/

#ifndef ARCHAIC
  static void DoString (void)
#else
  static void DoString ()
#endif

{
  cell val = DecodeSymbol ();

  if (! Object->ErrNo)
     {
       AddSymbol (LITERAL, (cell) Object->Strings + TIBSIZ + PADSIZ,
                  CurrentWord);
       Object->Strings += (unsigned) val;
     }
}


/*
This function compiles an ARRAY.
*/

#ifndef ARCHAIC
  static void DoArray (void)
#else
  static void DoArray ()
#endif

{
  cell val = DecodeSymbol ();

  if (! Object->ErrNo)
     {
       AddSymbol (VARIABLE, (cell) Object->Variables, CurrentWord);
       Object->Variables += (unsigned) val;
     }
}


/*
This function compiles a '.
*/

#ifndef ARCHAIC
  static void DoTick (void)
#else
  static void DoTick ()
#endif

{
  int  y;

  if ((y = DecodeName ()) != MISSING)
     CompileWord (LITERAL, SymTable [y].Value);
}


/*
This function compiles an AKA.
*/

#ifndef ARCHAIC
  static void DoAka (void)
#else
  static void DoAka ()
#endif

{
  int y;

  if (DecodeWord (M4NODECL))           /* can a word be retrieved? */
     {                                 /* if so, is it a symbol? */
       if ((y = GetSymbol (CurrentWord, W_SEARCH)) != MISSING)
          MakeSymbol (SymTable [y].Token, SymTable [y].Value);
       else {                          /* if not, is it a simple word? */
              if ((y = GetWord (CurrentWord, W_SEARCH)) != MISSING)
                 MakeSymbol (WordList [y].Wtok, 0L);
              else {                   /* if not, is it a constant? */
                     if ((y = GetConstant (CurrentWord, W_SEARCH)) != MISSING)
                        MakeSymbol (ConstList [y].Ctok, ConstList [y].Cval);
                     else Object->ErrNo = M4NONAME;
                   }                   /* else issue an error message */
            }
     }
}


/*
This function compiles a :REDO.
*/

#ifndef ARCHAIC
  static void DoRedo (void)
#else
  static void DoRedo ()
#endif

{
  int y;

  if ((y = DecodeName ()) != MISSING) CompileDoes (y);
}


/*
This function compiles a DOES>.
*/

#ifndef ARCHAIC
  static void DoDoes (void)
#else
  static void DoDoes ()
#endif

{
  if (SymTablep > 0) CompileDoes (SymTablep - 1);
  else Object->ErrNo = M4NODECL;
}


/*
This function compiles a HIDE.
*/

#ifndef ARCHAIC
  static void DoHide (void)
#else
  static void DoHide ()
#endif

{
  int  y;

  if ((y = DecodeName ()) != MISSING)
     {
       SymTablep--; 
       if (SymTablep != y)
          {
            SymTable [y].Token = SymTable [SymTablep].Token;
            SymTable [y].Value = SymTable [SymTablep].Value;
            strcpy (SymTable [y].Name, SymTable [SymTablep].Name);
          }
     }
}


/*
This function compiles a TAG.
*/

#ifndef ARCHAIC
  static void DoTag (void)
#else
  static void DoTag ()
#endif

{
  int  y;

  if ((y = DecodeName ()) != MISSING)
     {
       if (SymTable [y].Token != OFFSET) Object->ErrNo = M4NOTYPE;
       else MakeSymbol (LITERAL, Object->StringSiz - SymTable [y].Value);
     }
}


/*
This function compiles a ','.
*/

#ifndef ARCHAIC
  static void DoComma (void)
#else
  static void DoComma ()
#endif

{
  if (Object->ErrLine == 0) Object->ErrNo = M4NODECL;
  else
    if (Object->CodeSeg [Object->ErrLine - 1].Word == LITERAL)
        Object->CodeSeg [Object->ErrLine - 1].Word = CELLD;
    else Object->ErrNo = M4BADLIT;
}


/*
This function compiles comment.
*/

#ifndef ARCHAIC
  static void DoComment (void)
#else
  static void DoComment ()
#endif

{
   (void) DecodeWord (M4NOSTR);
}


/*
This function compiles '."'.
*/

#ifndef ARCHAIC
  static void DoDotQuote (void)
#else
  static void DoDotQuote ()
#endif

{
  CompileString (PRINT);
}


/*
This function compiles a ,".
*/

#ifndef ARCHAIC
  static void DoCommaQuote (void)
#else
  static void DoCommaQuote ()
#endif

{
  CompileString (STRINGD);
}


/*
This function compiles a S".
*/

#ifndef ARCHAIC
  static void DoSQuote (void)
#else
  static void DoSQuote ()
#endif

{
  CompileString (SQUOTE);
}


/*
This function sets the radix to 2.
*/

#ifndef ARCHAIC
  static void DoBinary (void)
#else
  static void DoBinary ()
#endif

{
  Base = 2;
}


/*
This function sets the radix to 8.
*/

#ifndef ARCHAIC
  static void DoOctal (void)
#else
  static void DoOctal ()
#endif

{
  Base = 8;
}


/*
This function sets the radix to 10.
*/

#ifndef ARCHAIC
  static void DoDecimal (void)
#else
  static void DoDecimal ()
#endif

{
  Base = 10;
}


/*
This function sets the radix to 16.
*/

#ifndef ARCHAIC
  static void DoHex (void)
#else
  static void DoHex ()
#endif

{
  Base = 16;
}


/*
This function aborts a compilation.
*/

#ifndef ARCHAIC
  static void DoCompAbort (void)
#else
  static void DoCompAbort ()
#endif

{
  Object->ErrNo = M4CABORT;
}


/*
This function evaluates a [=].
*/

#ifndef ARCHAIC
  static void DoEquals (void)
#else
  static void DoEquals ()
#endif

{
  CompileWord (LITERAL, (DecodeLiteral () == DecodeLiteral () ? F_T : F_F));
}


/*
This function executes a [SIGN].
*/

#ifndef ARCHAIC
  static void DoSign (void)
#else
  static void DoSign ()
#endif

{
  cell val = DecodeLiteral ();

  CompileWord (LITERAL, (val ? (val > 0 ? 1L : -1L) : 0L));
}


/*
This function executes a [NOT].
*/

#ifndef ARCHAIC
  static void DoNot (void)
#else
  static void DoNot ()
#endif

{
  CompileWord (LITERAL, (DecodeLiteral () == F_F ? F_T : F_F));
}


/*
This function compiles a [MAX].
*/

#ifndef ARCHAIC
  static void DoMax (void)
#else
  static void DoMax ()
#endif

{
  cell a = DecodeLiteral ();
  cell b = DecodeLiteral ();

  CompileWord (LITERAL, a > b ? a : b);
}


/*
This function executes a [DEFINED].
*/

#ifndef ARCHAIC
  static void DoDefined (void)
#else
  static void DoDefined ()
#endif

{
  if (DecodeWord (M4NODECL))
     CompileWord (LITERAL, (SearchDictionary (CurrentWord, W_SEARCH) == MISSING
     ? F_F : F_T));
}


/*
This function executes a [UNDEFINED].
*/

#ifndef ARCHAIC
  static void DoUndefined (void)
#else
  static void DoUndefined ()
#endif

{
  DoDefined ();
  DoNot ();
}


/*
This function turns off optimization.
*/

#ifndef ARCHAIC
  static void DoForce (void)
#else
  static void DoForce ()
#endif

{
  Optimization = FALSE;
  Fence = Object->ErrLine + 1;
}


/*
This function toggles assertion.
*/

#ifndef ARCHAIC
  static void DoAssert (void)
#else
  static void DoAssert ()
#endif

{
  Assert = ! Assert;
}


/*
This function removes an assertion if Assert is false.
*/

#ifndef ARCHAIC
  static void DoAssertion (void)
#else
  static void DoAssertion ()
#endif

{
   if (! Assert) SkipSource ("ASSERT(", ")", NULL);
}


/*
This function evaluates an [IF].
*/

#ifndef ARCHAIC
  static void DoBIf (void)
#else
  static void DoBIf ()
#endif

{
   cell val = DecodeLiteral ();
   if (! Object->ErrNo) if (! val) SkipSource ("[IF]", "[THEN]", "[ELSE]");
}


/*
This function evaluates an [ELSE].
*/

#ifndef ARCHAIC
  static void DoBElse (void)
#else
  static void DoBElse ()
#endif

{
  SkipSource ("[IF]", "[THEN]", NULL);
}


/*
This function compiles a HERE.
*/

#ifndef ARCHAIC
  static void DoHere (void)
#else
  static void DoHere ()
#endif

{
  CompileWord (LITERAL, (cell) Object->ErrLine);
}


/*
This function does absolutely nothing.
*/

#ifndef ARCHAIC
  static void DoDummy (void) {}
#else
  static void DoDummy () {}
#endif


/*
This function compiles a CHAR or a [CHAR].
*/

#ifndef ARCHAIC
  static void DoChar (void)
#else
  static void DoChar ()
#endif

{
  if (DecodeWord (M4NOSTR)) CompileWord (LITERAL, (cell) CurrentWord [0]);
}


/*
This function compiles a )
*/

#ifndef ARCHAIC
  static void DoCloseParen (void)
#else
  static void DoCloseParen ()
#endif

{
  CompileWord (EQ0, 0L);
  CompileWord (BRANCH0, (cell) (Object->ErrLine + 2L));
  CompileWord (LITERAL, -(M4ASSERT));
  CompileWord (THROW, 0L);
}


/*
This function compiles an ABORT"
*/

#ifndef ARCHAIC
  static void DoAbortQuote (void)
#else
  static void DoAbortQuote ()
#endif

{
  CompileWord   (BRANCH0, (cell) (Object->ErrLine + 5L));
  CompileWord   (LITERAL, STD4OUT);
  CompileWord   (USE, 0L);
  CompileString (PRINT);
  InlineWords   (2, CR, QUIT);
}


/*
This function compiles a SOURCE
*/

#ifndef ARCHAIC
  static void DoSource (void)
#else
  static void DoSource ()
#endif

{
  CompileWord (LITERAL, VTIB);
  CompileWord (FETCH, 0L);
  CompileWord (LITERAL, VTIBS);
  CompileWord (FETCH, 0L);
}


/*
This function compiles a SOURCE!
*/

#ifndef ARCHAIC
  static void DoSourceBang (void)
#else
  static void DoSourceBang ()
#endif

{
  CompileWord (LITERAL, VTIBS);
  CompileWord (STORE, 0L);
  CompileWord (LITERAL, VTIB);
  CompileWord (STORE, 0L);
}


/*
This function compiles a CHOP
*/

#ifndef ARCHAIC
  static void DoChop (void)
#else
  static void DoChop ()
#endif

{
  CompileWord (PLITERAL, -1L);
  CompileWord (SWAP, 0L);
  CompileWord (PLITERAL, 1L);
  CompileWord (SWAP, 0L);
}


/*
This function compiles a BLANK
*/

#ifndef ARCHAIC
  static void DoBlank (void)
#else
  static void DoBlank ()
#endif

{
  CompileWord (LITERAL, (cell) ' ');
  CompileWord (FILL, 0L);
}


/*
This function compiles an ERASE
*/

#ifndef ARCHAIC
  static void DoErase (void)
#else
  static void DoErase ()
#endif

{
  CompileWord (LITERAL, 0L);
  CompileWord (FILL, 0L);
}


/*
This function compiles a SPACE
*/

#ifndef ARCHAIC
  static void DoSpace (void)
#else
  static void DoSpace ()
#endif

{
  CompileWord (LITERAL, (cell) ' ');
  CompileWord (EMIT, 0L);
}


/*
This function compiles an ERROR?
*/

#ifndef ARCHAIC
  static void DoErrorQ (void)
#else
  static void DoErrorQ ()
#endif

{
  CompileWord (LITERAL, CELL_MIN);
  InlineWords (2, OVER, EQ);
}


/*
This function compiles a REWIND
*/

#ifndef ARCHAIC
  static void DoRewind (void)
#else
  static void DoRewind ()
#endif

{
  CompileWord (LITERAL, 0L);
  InlineWords (2, SWAP, FSEEK);
}


/*
This function compiles a >BODY
*/

#ifndef ARCHAIC
  static void DoToBody (void)
#else
  static void DoToBody ()
#endif

{
  CompileWord (ENVIRON, VFIRST);
  CompileWord (PLUS, 0L);
}


/*
This function compiles a DEFER@
*/

#ifndef ARCHAIC
  static void DoDeferFetch (void)
#else
  static void DoDeferFetch ()
#endif

{
  CompileWord (ENVIRON, VFIRST);
  InlineWords (2, PLUS, FETCH);
}


/*
This function compiles a DEFER!
*/

#ifndef ARCHAIC
  static void DoDeferStore (void)
#else
  static void DoDeferStore ()
#endif

{
  CompileWord (ENVIRON, VFIRST);
  InlineWords (2, PLUS, STORE);
}


/*
This function compiles a >=
*/

#ifndef ARCHAIC
  static void DoGreaterEqual (void)
#else
  static void DoGreaterEqual ()
#endif

{
  InlineWords (2, LT, EQ0);
}


/*
This function compiles a <=
*/

#ifndef ARCHAIC
  static void DoLessEqual (void)
#else
  static void DoLessEqual ()
#endif

{
  InlineWords (2, GT, EQ0);
}


/*
This function compiles a 2DROP
*/

#ifndef ARCHAIC
  static void DoTwoDrop (void)
#else
  static void DoTwoDrop ()
#endif

{
  InlineWords (2, DROP, DROP);
}


/*
This function compiles a 2DUP
*/

#ifndef ARCHAIC
  static void DoTwoDup (void)
#else
  static void DoTwoDup ()
#endif

{
  InlineWords (2, OVER, OVER);
}


/*
This function compiles a 2NIP
*/

#ifndef ARCHAIC
  static void DoTwoNip (void)
#else
  static void DoTwoNip ()
#endif

{
  InlineWords (4, ROT, DROP, ROT, DROP);
}


/*
This function compiles a 2SWAP
*/

#ifndef ARCHAIC
  static void DoTwoSwap (void)
#else
  static void DoTwoSwap ()
#endif

{
  InlineWords (4, ROT, RPUT, ROT, RGET);
}


/*
This function compiles a 2>R
*/

#ifndef ARCHAIC
  static void DoTwoRPut (void)
#else
  static void DoTwoRPut ()
#endif

{
  InlineWords (2, RPUT, RPUT);
}


/*
This function compiles a 2R>
*/

#ifndef ARCHAIC
  static void DoTwoRGet (void)
#else
  static void DoTwoRGet ()
#endif

{
  InlineWords (2, RGET, RGET);
}


/*
This function compiles a 2R@
*/

#ifndef ARCHAIC
  static void DoTwoRCopy (void)
#else
  static void DoTwoRCopy ()
#endif

{
  InlineWords (4, RGET, RCOPY, OVER, RPUT);
}


/*
This function compiles a R'@
*/

#ifndef ARCHAIC
  static void DoRTickCopy (void)
#else
  static void DoRTickCopy ()
#endif

{
  InlineWords (4, RGET, RCOPY, SWAP, RPUT);
}


/*
This function compiles a UNLOOP
*/

#ifndef ARCHAIC
  static void DoUnLoop (void)
#else
  static void DoUnLoop ()
#endif

{
  InlineWords (4, RGET, RGET, DROP, DROP);
}


/*
This function compiles a BOUNDS
*/

#ifndef ARCHAIC
  static void DoBounds (void)
#else
  static void DoBounds ()
#endif

{
  InlineWords (3, OVER, PLUS, SWAP);
}


/*
This function compiles a +PLACE
*/

#ifndef ARCHAIC
  static void DoPlusPlace (void)
#else
  static void DoPlusPlace ()
#endif

{
  InlineWords (3, COUNT, PLUS, PLACE);
}


/*
This function compiles a >STRING
*/

#ifndef ARCHAIC
  static void DoToString (void)
#else
  static void DoToString ()
#endif

{
  InlineWords (2, OVER, PLACE);
}


/*
This function compiles a PARSE-WORD
*/

#ifndef ARCHAIC
  static void DoParseWord (void)
#else
  static void DoParseWord ()
#endif

{
  InlineWords (3, DUP, OMIT, PARSE);
}


/*
This function compiles a NIP
*/

#ifndef ARCHAIC
  static void DoNip (void)
#else
  static void DoNip ()
#endif

{
  InlineWords (2, SWAP, DROP);
}


/*
This function compiles a TUCK
*/

#ifndef ARCHAIC
  static void DoTuck (void)
#else
  static void DoTuck ()
#endif

{
  InlineWords (2, SWAP, OVER);
}


/*
This function compiles a -ROT
*/

#ifndef ARCHAIC
  static void DoMinRot (void)
#else
  static void DoMinRot ()
#endif

{
  InlineWords (2, ROT, ROT);
}


/*
This function compiles a RSHIFT
*/

#ifndef ARCHAIC
  static void DoRshift (void)
#else
  static void DoRshift ()
#endif

{
  InlineWords (2, NEGATE, SHIFT);
}


/*
This function compiles a ?
*/

#ifndef ARCHAIC
  static void DoQuestion (void)
#else
  static void DoQuestion ()
#endif

{
  InlineWords (2, FETCH, DOT);
}


/*
This function compiles a CATCH
*/

#ifndef ARCHAIC
  static void DoCatch (void)
#else
  static void DoCatch ()
#endif

{
  InlineWords (2, CATCH, CAUGHT);
}


/*
This function compiles a star/MOD
*/

#ifndef ARCHAIC
  static void DoStarSlashMod (void)
#else
  static void DoStarSlashMod ()
#endif

{
  InlineWords (4, RPUT, MUL, RGET, SLASHMOD);
}


/*
This function compiles a /STRING
*/

#ifndef ARCHAIC
  static void DoSlashString (void)
#else
  static void DoSlashString ()
#endif

{
  InlineWords (6, SWAP, OVER, MINUS, RPUT, PLUS, RGET);
}


/*
This list contains all immediate words. It is used for both parsing and
compiling. It contains the following fields:
the length of the keyword, the number of entries it creates in the symbol
table, the number of extra tokens it compiles, its name, an optional
set of string terminators and finally the C function that compiles the word.
*/

static Immed4th ImmedList [] = {
  { 1,  0, -1, "\'",          "",    DoTick },
  { 1,  0, -2, "\\",          EOL,   DoComment },
  { 1,  0, -2, "(",           ")",   DoComment },
  { 1,  0, -1, ",",           "",    DoComma },
  { 1,  1, -1, ":",           "",    DoColon },
  { 1,  0,  1, "?",           "",    DoQuestion },
  { 1,  0,  3, ")",           "",    DoCloseParen },
  { 1,  0,  0, ";",           "",    DoSColon },
  { 2,  0,  0, ";]",          "",    DoSColon },
  { 2,  0,  1, "[:",          "",    DoNoName },
  { 2,  0, -2, "#!",          EOL,   DoComment },
  { 2,  0, -1, ",\"",         "\"",  DoCommaQuote },
  { 2,  0, -1, ",|",          "|",   DoCommaQuote },
  { 2,  0, -1, ".\"",         "\"",  DoDotQuote },
  { 2,  0, -1, ".(",          ")",   DoDotQuote },
  { 2,  0, -1, ".|",          "|",   DoDotQuote },
  { 2,  0, -2, "C,",          "",    DoCComma },
  { 2,  0, -2, "C\"",         "\"",  DoCQuote },
  { 2,  0, -2, "C|",          "|",   DoCQuote },
  { 2,  0,  1, ">=",          "",    DoGreaterEqual },
  { 2,  0,  1, "<=",          "",    DoLessEqual },
  { 2,  0, -1, "S\"",         "\"",  DoSQuote },
  { 2,  0, -1, "S|",          "|",   DoSQuote },
  { 2,  1, -1, "TO",          "",    DoValue },
  { 2,  1, -1, "IS",          "",    DoIs },
  { 2,  0,  0, "IF",          "",    DoIf },
  { 2,  0,  0, "DO",          "",    DoDo },
  { 2,  0, -1, "->",          "",    DoDummy },
  { 3,  0,  1, "2R>",         "",    DoTwoRGet },
  { 3,  0,  1, "2>R",         "",    DoTwoRPut },
  { 3,  0,  3, "2R@",         "",    DoTwoRCopy },
  { 3,  0,  3, "R\'@",        "",    DoRTickCopy },
  { 3,  0, -1, "S>D",         "",    DoDummy },
  { 3,  0, -1, "D>S",         "",    DoDummy  },
  { 3,  0,  1, "NIP",         "",    DoNip },
  { 3,  1, -3, "AKA",         "",    DoAka },
  { 3,  0, -1, "[\']",        "",    DoTick },
  { 3,  0, -2, "[=]",         "",    DoEquals },
  { 3,  0,  0, "?DO",         "",    DoQDo },
  { 3,  1, -3, "TAG",         "",    DoTag },
  { 4,  0,  1, "2DUP",        "",    DoTwoDup },
  { 4,  0,  3, "2NIP",        "",    DoTwoNip },
  { 4,  0, -1, "CHAR",        WHITE, DoChar },
  { 4,  0, -2, "[IF]",        "",    DoBIf },
  { 4,  0, -1, "THEN",        "",    DoThen },
  { 4,  0,  1, "TUCK",        "",    DoTuck },
  { 4,  1,  0, "FILE",        "",    DoFile  },
  { 4,  0,  1, "-ROT",        "",    DoMinRot },
  { 4,  0,  0, "ELSE",        "",    DoElse },
  { 4,  0,  0, "LOOP",        "",    DoLoop },
  { 4,  0,  0, "HERE",        "",    DoHere },
  { 4,  1, -2, "ENUM",        "",    DoEnum },
  { 4, -1, -2, "HIDE",        "",    DoHide },
  { 4,  0,  3, "CHOP",        "",    DoChop },
  { 4,  0,  0, "DONE",        "",    DoDone },
  { 5,  0,  3, "*/MOD",       "",    DoStarSlashMod },
  { 5,  0, -2, "@GOTO",       EOL,   DoComment },
  { 5,  1, -1, "ALIAS",       "",    DoIs },
  { 5,  0,  0, ":REDO",       "",    DoRedo },
  { 5,  0,  1, "2DROP",       "",    DoTwoDrop },
  { 5,  0,  3, "2SWAP",       "",    DoTwoSwap },
  { 5,  1,  0, "DEFER",       "",    DoDefer },
  { 5,  0, -1, "[NOT]",       "",    DoNot },
  { 5,  0, -1, "ALIGN",       "",    DoDummy },
  { 5,  0,  1, "CATCH",       "",    DoCatch },
  { 5,  0,  1, "SPACE",       "",    DoSpace },
  { 5,  1, -3, "ARRAY",       "",    DoArray },
  { 5,  0, -1, "BEGIN",       "",    DoBegin },
  { 5,  0, -1, "CELLS",       "",    DoDummy },
  { 5,  0,  1, "DOES>",       "",    DoDoes },
  { 5,  0, -1, "CHARS",       "",    DoDummy },
  { 5,  1, -2, "TABLE",       "",    DoCreate },
  { 5,  1, -1, "VALUE",       "",    DoValue },
  { 5,  0, -1, "[HEX]",       "",    DoHex },
  { 5,  0,  1, ">BODY",       "",    DoToBody },
  { 5,  0,  1, "BLANK",       "",    DoBlank },
  { 5,  0,  1, "ERASE",       "",    DoErase },
  { 5,  0,  0, "+LOOP",       "",    DoPLoop },
  { 5,  0,  0, "WHILE",       "",    DoWhile },
  { 5,  0,  0, "AGAIN",       "",    DoRepeat },
  { 5,  0,  0, "UNTIL",       "",    DoUntil },
  { 5,  0, -2, "[MAX]",       "",    DoMax },
  { 6,  1, -1, ":TOKEN",      "",    DoToken },
  { 6,  0, -2, "/FIELD",      "",    DoMax },
  { 6,  1, -3, "+FIELD",      "",    DoPField },
  { 6,  1, -2, "FIELD:",      "",    DoFieldC },
  { 6,  0,  3, "UNLOOP",      "",    DoUnLoop },
  { 6,  0,  2, "BOUNDS",      "",    DoBounds },
  { 6,  0,  2, "ERROR?",      "",    DoErrorQ },
  { 6,  0,  2, "REWIND",      "",    DoRewind },
  { 6,  0,  3, "SOURCE",      "",    DoSource },
  { 6,  0,  2, "+PLACE",      "",    DoPlusPlace },
  { 6,  0,  1, "RSHIFT",      "",    DoRshift },
  { 6,  1, -2, "CREATE",      "",    DoCreate },
  { 6,  0, -1, "[ELSE]",      "",    DoBElse },
  { 6,  0, -1, "[THEN]",      "",    DoDummy },
  { 6,  0, -2, "[NEEDS",      "]",   DoComment },
  { 6,  1, -3, "STRING",      "",    DoString },
  { 6,  0,  4, "ABORT\"",     "\"",  DoAbortQuote },
  { 6,  0, -1, "[CHAR]",      WHITE, DoChar },
  { 6,  0,  0, "REPEAT",      "",    DoRepeat },
  { 6,  0,  2, "DEFER@",      "",    DoDeferFetch },
  { 6,  0,  2, "DEFER!",      "",    DoDeferStore },
  { 6,  1, -2, "OFFSET",      "",    DoOffset },
  { 6,  0, -1, "[SIGN]",      "",    DoSign },
  { 7,  1, -3, "EQUATES",     "",    DoEquates },
  { 7,  1, -2, "CFIELD:",     "",    DoFieldC },
  { 7,  0,  1, ">STRING",     "",    DoToString },
  { 7,  1, -3, "BUFFER:",     "",    DoString },
  { 7,  0,  5, "/STRING",     "",    DoSlashString },
  { 7,  0, -2, "INCLUDE",     WHITE, DoComment },
  { 7,  0, -1, "ASSERT(",     "",    DoAssertion },
  { 7,  0,  3, "SOURCE!",     "",    DoSourceBang },
  { 7,  0, -1, "[ABORT]",     "",    DoCompAbort },
  { 7,  0, -1, "[OCTAL]",     "",    DoOctal },
  { 7,  0, -1, "[FORCE]",     "",    DoForce },
  { 7,  0,  1, ":NONAME",     "",    DoNoName },
  { 7,  0, -1, "ALIGNED",     "",    DoDummy },
  { 7,  0,  0, "RECURSE",     "",    DoRecurse },
  { 8,  1, -3, "CONSTANT",    "",    DoConstant },
  { 8,  1, -2, "VARIABLE",    "",    DoVariable },
  { 8,  1, -2, "[PRAGMA]",    "",    DoPragma },
  { 8,  0, -1, "[ASSERT]",    "",    DoAssert },
  { 8,  0, -1, "[BINARY]",    "",    DoBinary },
  { 8,  1, -2, "[IGNORE]",    "",    DoIgnore },
  { 9,  0, -1, "[DECIMAL]",   "",    DoDecimal },
  { 9,  0, -1, "[DEFINED]",   WHITE, DoDefined },
  { 9,  1, -3, "+CONSTANT",   "",    DoPConstant },
  { 9,  1, -3, "*CONSTANT",   "",    DoMConstant },
  { 9,  1, -3, "/CONSTANT",   "",    DoDConstant },
  { 9,  1, -3, "SCONSTANT",   "",    DoSConstant },
  { 9,  0, -1, "IMMEDIATE",   "",    DoDummy },
  { 10, 1, -3, "END-STRUCT",  "",    DoConstant },
  { 10, 0,  2, "PARSE-WORD",  "",    DoParseWord },
  { 11, 0, -1, "[UNDEFINED]", WHITE, DoUndefined },
  { CHAR_MAX, 0,  0, "",      "",    DoDummy }
};


/*
This routine returns the index of the word in the immediate list (if found).
If it is not found in the immediate list it returns MISSING.
*/

#ifndef ARCHAIC
  static int GetImmediate (char *symbol, char mode)
#else
  static int GetImmediate (symbol, mode) char *symbol; char mode;
#endif

{                                      /* list of all "simple" commands */
  int x;                               /* simple counter */
  unsigned len = strlen (symbol);

  for (x = 0; len > ImmedList [x].Ilen; x++);
  for (;len == ImmedList [x].Ilen; x++)
      if (! MatchName (ImmedList [x].Iname, symbol))
         {
           if (mode == W_EXEC) (*(ImmedList [x].Ifun)) ();
           if (mode == W_STRING) x = strlen (ImmedList [x].Idelimit);
           return (x);
         }

  return (MISSING);
}


/*
This routine searches the entire dictionary for a specific name and performs
the action as indicated.
*/

#ifndef ARCHAIC
  static int SearchDictionary (char* Name, char Action)
#else
  static int SearchDictionary (Name, Action) char* Name; char Action;
#endif

{
  if ((GetWord     (Name, Action) == MISSING)
  && (GetConstant  (Name, Action) == MISSING)
  && (GetImmediate (Name, Action) == MISSING)
  && (GetSymbol    (Name, Action) == MISSING))
       return (MISSING);
  else return (FOUND);
}


/*
This routine is actually a modified version of strpbrk() which keeps
track of the current position and previously parsed strings. The current
position is later used to include files at their proper place. This
function terminates strings and updates all pointers.
*/

#ifndef ARCHAIC
  static char ScanText (char *delim, ParseRegs *Parser)
#else
  static char ScanText (delim, Parser) char *delim; ParseRegs *Parser;
#endif

{
  char *x;

  for (Parser->Prev = Parser->Curr,
       Parser->Curr = Object->StringSeg + Parser->Next;
       Object->StringSeg [Parser->Next] != '\0'; ++Parser->Next)
       for (x = delim; *x != '\0'; ++x)
         if (Object->StringSeg [Parser->Next] == *x)
           {
             Object->StringSeg [Parser->Next++] = '\0';
             return (TRUE);
           }

  return (FALSE);
}


/*
This routine shifts the second part of the original source
to the end of the file
*/

#ifndef ARCHAIC
  static void MakeRoom (ParseRegs *Parser, long Included)
#else
  static void MakeRoom (Parser, Included) ParseRegs *Parser; long Included;
#endif

{
  long cnt;                            /* how many chars to be moved */
  long x;                              /* simple counter */
  char *o;                             /* origin */
  char *d;                             /* destination */

  cnt = Parser->End - Parser->Next;
  o = Object->StringSeg + Parser->End;
  Parser->End += (mark) (Included + 1L);
  d = Object->StringSeg + Parser->End;
                                       /* calculate the offsets */
  for (x = 0; x <= cnt; o--, d--, x++) *d = *o;
  *d = '\n';                           /* terminate the last line */
}


/*
This function will try open the issued filename. If it fails, it queries
the environment for a default directory. When DIR4TH has been defined it
will retry to open the file.
*/

#ifndef ARCHAIC
  static FILE* DoOpen (char* filename)
#else
  static FILE* DoOpen (filename) char* filename;
#endif

{
  FILE* Fp = fopen (filename, "rb");   /* file pointer */
  char* path;                          /* default 4tH directory */
  char* fullname;                      /* pointer to fullname */
                                       /* if open failed and path is set */
  if (Fp == NULL)                      /* allocate enough space */
     if ((path = getenv ("DIR4TH")) != NULL)
        if ((fullname = (char*) calloc (strlen (path) + strlen (filename) + 1,
           sizeof (char))) != NULL)
           {                           /* construct the full name */
             strcat (strcpy (fullname, path), filename);
             Fp = fopen (fullname, "rb");
             free (fullname);          /* try to open file and free space */
           }

  return (Fp);                         /* return file pointer */
}


/*
This routine is almost identical to the original open_4th() function. It
determines the length of the file, expands the space allocated to the
source accordingly, moves the contents and reads the file to be included
at the proper place.
*/

#ifndef ARCHAIC
  static void DoNeeds (ParseRegs *Parser)
#else
  static void DoNeeds (Parser) ParseRegs *Parser;
#endif

{
  char *p;                             /* buffer that holds text */
  FILE *SourceFp;                      /* file pointer to textfile */
  long  FileSiz;                       /* length of file */
                                       /* assume we'll have IO errors */
  Object->ErrNo = M4IOERR;             /* open the include file */
  if ((SourceFp = DoOpen (Parser->Curr)) != NULL)
     {                                 /* try to find it's length */
       if (! fseek (SourceFp, 0L, SEEK_END))
         if ((FileSiz = ftell (SourceFp)) != -1L)
           if (! fseek (SourceFp, 0L, SEEK_SET))
              {
                if ((p = (char *) realloc (Object->StringSeg, (size_t)
                   (FileSiz + 2L + Parser->End) * sizeof (char))) == NULL)
                   Object->ErrNo = M4NOMEM;
                else                   /* enlarge the source buffer */
                   {                   /* if ok, use it and move contents */
                     Object->StringSeg = Parser->Prev = Parser->Curr = p;
                     MakeRoom (Parser, FileSiz);
                     if (fread (Object->StringSeg + Parser->Next, sizeof (char),
                        (size_t) FileSiz, SourceFp) == (size_t) FileSiz)
                        Object->ErrNo = M4NOERRS;
                   }                   /* now read the file into place */
              }
       if (fclose (SourceFp)) Object->ErrNo = M4IOERR;
     }                                 /* return current position in buffer */
}


/*
This routine parses a string. Words with strings usually require a
special delimiter. If a string is succesfully parsed, the routine will
return "one string found" and change the pointer Next. If not, ErrNo is
set and the routine returns zero. It also determines whether the "[NEEDS"
directive is called.
*/

#ifndef ARCHAIC
  static char ParseString (ParseRegs *Parser, char *Delimiter)
#else
  static char ParseString (Parser, Delimiter) ParseRegs *Parser;
         char *Delimiter;
#endif

{
  if (! ScanText (Delimiter, Parser)) Object->ErrNo = M4NOSTR;
  else                                 /* Termination not found */
     {                                 /* Null string found */
       if (strlen (Parser->Curr) == 0) Object->ErrNo = M4NULSTR;
       else
         {
           if ((! MatchName ("[NEEDS",  Parser->Prev)) ||
               (! MatchName ("INCLUDE", Parser->Prev))) DoNeeds (Parser);
           return (1);                 /* Now check for an inclusion.. */
         }                             /* String has been found */
     }

  return (0);
}


/*
This routine checks whether the parsed word requires special action. It can
compile to more or less words, require an entry in the symbol table or have
a string attached.
*/

#ifndef ARCHAIC
  static char ParseDirective (ParseRegs *Parser)
#else
  static char ParseDirective (Parser) ParseRegs *Parser;
#endif

{
  int x;                               /* simple counter */
  unsigned len = strlen (Parser->Curr);
                                       /* set pointer */
  for (x = 0; len > ImmedList [x].Ilen; x++);
  for (;len == ImmedList [x].Ilen; x++)
      if (! MatchName (ImmedList [x].Iname, Parser->Curr))
         {                             /* found; now calculate */
           SourceSymbols    += (int) ImmedList [x].InoSymbols;
           SourceCorrection += (int) ImmedList [x].InoWords;
           if (strlen (ImmedList [x].Idelimit) > 0)
              return (ParseString (Parser, ImmedList [x].Idelimit));
           break;                      /* parse string */
         }

  return (0);                          /* no or no valid string */
}


/*
This routine parses the text that is presented to the compiler. It returns
the number of words (Code Segment entries) it has found. 'SourceSymbols'
holds the number of symboltable entries. 'SourceStrings' holds the number
of words in the source; see: GetNextWord().
*/

#ifndef ARCHAIC
  static int ParseText (void)
#else
  static int ParseText ()
#endif

{
  ParseRegs Parser;
  int SourceWords = 0;
  int MaxSymbols  = 0;                 /* Highwatermark symboltable */

  if (Object->StringSeg)               /* If it is a valid pointer */
     {                                 /* While whitespace found */
       for (Parser.Prev = Parser.Curr = Object->StringSeg, Parser.Next = 0,
            Parser.End = strlen (Object->StringSeg);
           (ScanText (WHITE, &Parser)) && (! Object->ErrNo);)
           {                           /* Begin a new string */
             if (strlen (Parser.Curr) > 0)
                {                      /* Is it a definition? */
                  SourceStrings++;
                  SourceStrings += (int) ParseDirective (&Parser);
                  if (SourceSymbols > MaxSymbols) MaxSymbols = SourceSymbols;
                }                      /* Highwatermark reached? */
           }
                                       /* Get last word after WS */
       if (strlen (Parser.Curr) > 0) SourceStrings++;
       SourceWords = SourceStrings + SourceCorrection;
       SourceSymbols = MaxSymbols;     /* Set SourceSymbols to highwatermark */
     }                                 /* Calculate number of words */

  if ((SourceWords < 1) && (! Object->ErrNo))
     Object->ErrNo = M4NOPROG;         /* If nothing compiled and no errors */
                                       /* Then there is no real source code */
  return (Object->ErrNo ? 0 : ++SourceWords);
}                                      /* return no. of words, correct lit. */


/*
This routine will add a symbol to the symboltable. It checks on overflow.
It sets Object->ErrNo to the appropriate number when it fails.
*/

#ifndef ARCHAIC
  static void AddSymbol (unit Stoken, cell Svalue, char* Sname)
#else
  static void AddSymbol (Stoken, Svalue, Sname)
         unit Stoken; cell Svalue; char* Sname;
#endif

{
  if (SymTablep < SourceSymbols)
    if (strlen (Sname) < SYMLEN)       /* name within bounds? */
      if (SearchDictionary (Sname, W_SEARCH) == MISSING)
         {                             /* not already defined? */
           SymTable [SymTablep].Token = Stoken;
           SymTable [SymTablep].Value = Svalue;
           strcpy (SymTable [SymTablep++].Name, Sname);
         }
      else Object->ErrNo = M4DUPNAM;
    else Object->ErrNo = M4BADNAM;
  else Object->ErrNo = M4BADOBJ;
}


/*
This routine simply frees the memory allocated to the symboltable and
the linktable. It resets the pointers too, so it can be called again
without any problem.
*/

#ifndef ARCHAIC
  static void FreeResource (void)
#else
  static void FreeResource ()
#endif

{
  if (ControlStack)
     {
       free (ControlStack);
       ControlStack = NULL;
     }

  if (SymTable)
     {
       free (SymTable);
       SymTable = NULL;
     }
}


/*
This routine aborts the current compile, cleans up and returns the header.
*/

#ifndef ARCHAIC
  static Hcode* AbortCompile (void)
#else
  static Hcode* AbortCompile ()
#endif

{
  FreeResource ();

  if (Object->CodeSeg)
     {
       free (Object->CodeSeg);
       Object->CodeSiz = 0;
       Object->CodeSeg = NULL;
     }

  if (Object->StringSeg)
     {
       free (Object->StringSeg);
       Object->StringSiz = 0;
       Object->StringSeg = NULL;
     }

  Object->Reliable = FALSE;

  return (Object);
}


/*
Initializes the object and all global variables
*/

#ifndef ARCHAIC
  static int InitObject (char* sources)
#else
  static int InitObject (sources) char* sources;
#endif

{
  Assert           = FALSE;            /* assertion turned off */
  Optimization     = TRUE;             /* peephole optimizer turned on */
  Fence            = 0;                /* set optimizer limit */
  Base             = 10;               /* set radix to decimal */
  ToCS             = 0;                /* top of Control Stack */
  SymTablep        = 0;                /* top of symbol table */
  SourceSymbols    = 0;                /* size of symbol table */
  SourceStrings    = 0;                /* number of individual strings */
  SourceCorrection = 0;                /* correction for word allocation */
  CompiledStrings  = 0;                /* reset counter of compiled words */
  ControlStack     = NULL;             /* pointer to Control Stack */
  SymTable         = NULL;             /* pointer to symbol table */

  Object->StringSeg = sources;
  Object->CodeSeg   = NULL;
  Object->UnitSeg   = NULL;
  Object->CellSeg   = NULL;
  Object->StringSiz = 0;
  Object->Offset    = 0;
  Object->Variables = 0;
  Object->Strings   = 0;
  Object->ErrNo     = M4NOERRS;        /* reset variables in header */
  Object->ErrLine   = 0;
  return ((Object->CodeSiz = ParseText ()));
}


/*
This routine allocates all necessary resources like symboltable, linktable
and the codesegment. The value of ErrNo is returned.
*/

#ifndef ARCHAIC
  static unsigned AllocResource (void)
#else
  static unsigned AllocResource ()
#endif

{
  if ((Object->CodeSeg = (dict*)
     calloc (Object->CodeSiz, sizeof (dict))) == NULL)
     Object->ErrNo = M4NOMEM;

  if (SourceSymbols)
     if ((SymTable = (Symbol*) calloc (SourceSymbols, sizeof(Symbol))) == NULL)
        Object->ErrNo = M4NOMEM;

  if ((ControlStack = (Link*) calloc (LINKSIZ, sizeof (Link))) == NULL)
     Object->ErrNo = M4NOMEM;

  return (Object->ErrNo);
}


/*
This routine reallocates the String Segment and Code Segment. It returns FALSE
when everything is all right.
*/

#ifndef ARCHAIC
  static char ReallocSegs (void)
#else
  static char ReallocSegs ()
#endif

{
  dict *Dp;
  char *Sp;

  FreeResource ();                     /* free link- and symboltables */

  if (Object->StringSiz == 0)          /* discard String Segment */
     {                                 /* when there are no strings */
       free (Object->StringSeg);
       Object->StringSeg = NULL;
     }
  else                                 /* adjust String Segment */
     if ((Sp = (char*) realloc (Object->StringSeg,
        Object->StringSiz * sizeof (char))) != NULL) Object->StringSeg = Sp;
     else                              /* if realloc fails, free segment */
        {
          Object->ErrNo = M4NOMEM;
          return (TRUE);
        }
                                       /* check if program */
  if ((Object->CodeSiz = Object->ErrLine) == 0)
     {
       if (! Object->ErrNo) Object->ErrNo = M4NOPROG;
       return (TRUE);
     }
  else                                 /* adjust Code Segment */
     if ((Dp = (dict*) realloc (Object->CodeSeg,
        Object->CodeSiz * sizeof (dict))) != NULL) Object->CodeSeg = Dp;
     else                              /* if realloc fails, free segment */
        {
          Object->ErrNo = M4NOMEM;
          return (TRUE);
        }

  return (FALSE);
}


#ifndef ARCHAIC
  Hcode *comp_4th (char *Source)
#else
  Hcode *comp_4th (Source) char *Source;
#endif

{
  cell     Value;                      /* temporary cell value */

  if ((Object = (Hcode*) calloc (1, sizeof (Hcode))) == NULL)
    {
      free (Source);
      return (NULL);                   /* allocate objectheader */
    }
                                       /* initialize header */
  if (InitObject (Source) < 1) return (AbortCompile ());
  if (AllocResource ())        return (AbortCompile ());
                                       /* allocate all resources */
  Cursor = Object->StringSeg; GetNextWord ();
                                       /* initialize parser */
  for (;(CurrentWord != NULL) && (! Object->ErrNo); GetNextWord ())
      {
        if (SearchDictionary (CurrentWord, W_EXEC) == MISSING)
           {
             Value = str2cell (CurrentWord, Base);
             if (Value == CELL_MIN) Object->ErrNo = M4NONAME;
             else CompileWord (LITERAL, Value);
           }
      }                                /* now compile */
                                       /* reallocate segments */
  if (ReallocSegs ()) return (AbortCompile ());
  if ((ToCS != 0) && (! Object->ErrNo)) Object->ErrNo = M4NOJUMP;
                                       /* check empty linktable */
  Object->Reliable = Object->ErrNo ? FALSE : TRUE;
  return (Object);                     /* return compiled code */
}
