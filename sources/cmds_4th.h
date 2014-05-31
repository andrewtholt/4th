/*
  cmds_4th.h

  Command definitions for portable Forth compiler.

  Copyright (c) J.L. Bezemer 1994,2012

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
*/

#ifndef _CMD_4TH_H
#define _CMD_4TH_H

#define NOOP       0
#define STRINGD    0
#define EXECUTE    1
#define CR         2
#define SPACES     3
#define EMIT       4
#define PRINT      5
#define DOT        6
#define FETCH      7
#define STORE      8
#define CATCH      9

#define CAUGHT    10
#define PLUS      11
#define MINUS     12
#define MUL       13
#define DIV       14
#define MOD       15
#define SWAP      16
#define DUP       17
#define OVER      18
#define ROT       19

#define DROP      20
#define EQ        21
#define LT        22
#define GT        23
#define NE        24
#define INVERT    25
#define LT0       26
#define GT0       27
#define BRANCH0   28
#define BRANCH    29

#define FETCHC    30
#define AND       31
#define OR        32
#define XOR       33
#define SHIFT     34
#define ABS       35
#define NEGATE    36
#define QUIT      37
#define MIN       38
#define MAX       39

#define RPUT      40
#define RGET      41
#define RCOPY     42
#define NE0       43
#define EQ0       44
#define ACCEPT    45
#define RADIX     46
#define OFFSET    47
#define RPFETCH   48
#define SPFETCH   49

#define LITERAL   50
#define PLITERAL  51
#define MLITERAL  52
#define DLITERAL  53
#define QDO       54
#define DO        55
#define LOOP      56
#define PLOOP     57
#define LEAVE     58
#define FCLOSE    59

#define FOPEN     60
#define USE       61
#define ADDSTORE  62
#define SLASHMOD  63
#define STARSLSH  64
#define EXIT      65
#define RCOPY3    66
#define DOTR      67
#define NUMBER    68
#define VARIABLE  69

#define TRAILING  70
#define CALL      71
#define REFILL    72
#define CFETCH    73
#define CSTORE    74
#define TYPE      75
#define FILL      76
#define COUNT     77
#define CMOVE     78
#define PLACE     79

#define OMIT      80
#define PARSE     81
#define LSHARP    82
#define SHARP     83
#define RSHARP    84
#define SHARPS    85
#define SIGN      86
#define HOLD      87
#define TO        88
#define VALUE     89

#define TIME      90
#define CELLD     91
#define SQUOTE    92
#define PAUSE     93
#define VECTOR    94
#define ENVIRON   95
#define THROW     96
#define ARGS      97
#define ARGN      98
#define FSEEK     99

#define FTELL    100
#define FSYNC    101
#define DELFILE  102
#define SMOVE    103
#define RIGHT2   104
#define ENVFETCH 105
//
// ATH Added
//
#define SEMTRAN 106
#define GETSEMVALUE 107
#define SETSEMVALUE 108
#define GETSEM 109
#define RELSEM 110
#define RMSEM 111

#define SHMGET 112
#define SHMAT 113
#define SHMDT 114
#define SHMRM 115
#define MEMCAT 116    // Memory C@
#define MEMCSTORE 117 // Memory C!
#define MEMWAT 118 // Memory 16 bit @
#define MEMWSTORE 119 // Memory 16 bit !
#define MEMAT 120 // Memory 16 bit @
#define MEMSTORE 121 // Memory 16 bit !
#define FCNTL 122 

/* ranges */
// #define LastWord4th  ENVFETCH
#define LastWord4th  FCNTL
#define LastMsg4th   M4CABORT

/* flags */
#define F_T        1L
#define F_F        0L

/* file modes */
#define F4_READ      1L
#define F4_WRITE     2L
#define F4_APPND     4L
#define F4_PIPE      8L

/* devices */
#define STD4IN       0L
#define STD4OUT      1L

/* header */
#define Version4th   0x362
#define App4th       0L

/* compiler */
#define LINKSIZ      64
#define SYMLEN       24

/* interpreter */
#define STACKSIZ     512
#define TIBSIZ       256
#define PADSIZ       768
#define DOTSIZ       128
#define MAXDEVS        8
#define PIPEWAIT 102400L

/* variables and environs */
#define SYS4TH   3
#define VAR4TH  10
#define ENV4TH   5

#define VHI      0
#define VFIRST   1
#define VLAST    2
#define VCIN     3
#define VCOUT    4

#define VBASE    5
#define VIN      6
#define VOUT     7
#define VTIB     8
#define VTIBS    9

/* load+save */
#define HMASK   UCHAR_MAX
#define HBITS   CHAR_BIT
#define HNTINY  SCHAR_MAX
#define HNSMALL SHRT_MAX
#define HSPOS   0
#define HSNEG   1
#define HCCELL  0
#define HCSIGN  1
#define HCBYTE  2
#define HCSHRT  4
#define HCZERO  8
#define HCONE  16

/* generation */
#define UNITSLINE 9
#define DICTSLINE 3

/* no not change */
#define TIB    0
#define PAD    TIBSIZ
#define STRTOP ((TIBSIZ+PADSIZ)-DOTSIZ)
#define Sp0    0
#define Rp0    (STACKSIZ-1)

/* internal functions */
#ifdef ARCHAIC
#define __PROTO(p) ()
#else
#define __PROTO(p) p
#endif

#ifdef __TURBOC__
#if __STDC__
#define _Cdecl
#else
#define _Cdecl cdecl
#endif
cell _Cdecl str2cell (char *str, cell base);
#else
extern cell str2cell __PROTO ((char *str, cell base));
#endif

#endif


