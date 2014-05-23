#undef STRINGD
#undef EXECUTE
#undef CR
#undef SPACES
#undef EMIT
#undef PRINT
#undef DOT
#undef FETCH
#undef STORE
#undef CATCH
#undef CAUGHT
#undef PLUS
#undef MINUS
#undef MUL
#undef DIV
#undef MOD
#undef SWAP
#undef DUP
#undef OVER
#undef ROT
#undef DROP
#undef EQ
#undef LT
#undef GT
#undef NE
#undef INVERT
#undef LT0
#undef GT0
#undef BRANCH0
#undef BRANCH
#undef FETCHC
#undef AND
#undef OR
#undef XOR
#undef SHIFT
#undef ABS
#undef NEGATE
#undef QUIT
#undef MIN
#undef MAX
#undef RPUT
#undef RGET
#undef RCOPY
#undef NE0
#undef EQ0
#undef ACCEPT
#undef RADIX
#undef OFFSET
#undef RPFETCH
#undef SPFETCH
#undef LITERAL
#undef PLITERAL
#undef MLITERAL
#undef DLITERAL
#undef QDO
#undef DO
#undef LOOP
#undef PLOOP
#undef LEAVE
#undef FCLOSE
#undef FOPEN
#undef USE
#undef ADDSTORE
#undef SLASHMOD
#undef STARSLSH
#undef EXIT
#undef RCOPY3
#undef DOTR
#undef NUMBER
#undef VARIABLE
#undef TRAILING
#undef CALL
#undef REFILL
#undef CFETCH
#undef CSTORE
#undef TYPE
#undef FILL
#undef COUNT
#undef CMOVE
#undef PLACE
#undef OMIT
#undef PARSE
#undef LSHARP
#undef SHARP
#undef RSHARP
#undef SHARPS
#undef SIGN
#undef HOLD
#undef TO
#undef VALUE
#undef TIME
#undef CELLD
#undef SQUOTE
#undef PAUSE
#undef VECTOR
#undef ENVIRON
#undef THROW
#undef ARGS
#undef ARGN
#undef FSEEK
#undef FTELL
#undef FSYNC
#undef DELFILE
#undef SMOVE
#undef RIGHT2
#undef ENVFETCH

  static void *commands [] = {
    &&L_STRINGD,       &&L_EXECUTE,       &&L_CR,            &&L_SPACES,
    &&L_EMIT,          &&L_PRINT,         &&L_DOT,           &&L_FETCH,
    &&L_STORE,         &&L_CATCH,         &&L_CAUGHT,        &&L_PLUS,
    &&L_MINUS,         &&L_MUL,           &&L_DIV,           &&L_MOD,
    &&L_SWAP,          &&L_DUP,           &&L_OVER,          &&L_ROT,
    &&L_DROP,          &&L_EQ,            &&L_LT,            &&L_GT,
    &&L_NE,            &&L_INVERT,        &&L_LT0,           &&L_GT0,
    &&L_BRANCH0,       &&L_BRANCH,        &&L_FETCHC,        &&L_AND,
    &&L_OR,            &&L_XOR,           &&L_SHIFT,         &&L_ABS,
    &&L_NEGATE,        &&L_QUIT,          &&L_MIN,           &&L_MAX,
    &&L_RPUT,          &&L_RGET,          &&L_RCOPY,         &&L_NE0,
    &&L_EQ0,           &&L_ACCEPT,        &&L_RADIX,         &&L_OFFSET,
    &&L_RPFETCH,       &&L_SPFETCH,       &&L_LITERAL,       &&L_PLITERAL,
    &&L_MLITERAL,      &&L_DLITERAL,      &&L_QDO,           &&L_DO,
    &&L_LOOP,          &&L_PLOOP,         &&L_LEAVE,         &&L_FCLOSE,
    &&L_FOPEN,         &&L_USE,           &&L_ADDSTORE,      &&L_SLASHMOD,
    &&L_STARSLSH,      &&L_EXIT,          &&L_RCOPY3,        &&L_DOTR,
    &&L_NUMBER,        &&L_VARIABLE,      &&L_TRAILING,      &&L_CALL,
    &&L_REFILL,        &&L_CFETCH,        &&L_CSTORE,        &&L_TYPE,
    &&L_FILL,          &&L_COUNT,         &&L_CMOVE,         &&L_PLACE,
    &&L_OMIT,          &&L_PARSE,         &&L_LSHARP,        &&L_SHARP,
    &&L_RSHARP,        &&L_SHARPS,        &&L_SIGN,          &&L_HOLD,
    &&L_TO,            &&L_VALUE,         &&L_TIME,          &&L_CELLD,
    &&L_SQUOTE,        &&L_PAUSE,         &&L_VECTOR,        &&L_ENVIRON,
    &&L_THROW,         &&L_ARGS,          &&L_ARGN,          &&L_FSEEK,
    &&L_FTELL,         &&L_FSYNC,         &&L_DELFILE,       &&L_SMOVE,
    &&L_RIGHT2,        &&L_ENVFETCH,      &&L_UNKNOWN,       &&L_UNKNOWN,
    &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,
    &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,
    &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,
    &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,
    &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,
    &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,
    &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,
    &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,
    &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,
    &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,
    &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,
    &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,
    &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,
    &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,
    &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,
    &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,
    &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,
    &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,
    &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,
    &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,
    &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,
    &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,
    &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,
    &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,
    &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,
    &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,
    &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,
    &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,
    &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,
    &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,
    &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,
    &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,
    &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,
    &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,
    &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,
    &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,
    &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN,       &&L_UNKNOWN
  };
