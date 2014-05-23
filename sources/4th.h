/*
  4th.h

  Definitions for portable Forth compiler.

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

#ifndef _FORTH_H
#define _FORTH_H

#include <stdio.h>
#include <limits.h>

#define TRUE    (1)
#define FALSE   (0)

#define M4NOERRS  0
#define M4NOMEM   1
#define M4BADOBJ  2
#define M4SOVFLW  3                    /* -3 stack overflow */
#define M4SEMPTY  4                    /* -4 stack underflow */
#define M4ROVFLW  5                    /* -5 return stack overflow */
#define M4REMPTY  6                    /* -6 return stack underflow */
#define M4BADSTR  7
#define M4BADVAR  8
#define M4BADADR  9                    /* -9 invalid memory address */
#define M4DIVBY0 10                    /* -10 division by zero */
#define M4BADTOK 11
#define M4NOTYPE 12                    /* -12 argument type mismatch */
#define M4NONAME 13                    /* -13 undefined word */
#define M4IOERR  14
#define M4ASSERT 15
#define M4THROW  16
#define M4BADRDX 17
#define M4BADDEV 18
#define M4BADLIT 19
#define M4BADPTR 20
#define M4NONEST 21
#define M4NOPROG 22
#define M4NODECL 23
#define M4NOJUMP 24
#define M4NOSTR  25
#define M4NULSTR 26
#define M4DUPNAM 27
#define M4BADNAM 28
#define M4CABORT 29

#define CELL_MIN LONG_MIN
#define CELL_MAX LONG_MAX

typedef long cell;
typedef unsigned char unit;

typedef struct {
   unit  Word;
   cell  Value;
} dict;

typedef struct {
   int      CodeSiz;
   dict    *CodeSeg;
   unsigned StringSiz;
   char    *StringSeg;
   cell    *CellSeg;
   unit    *UnitSeg;
   unsigned Offset;
   unsigned Variables;
   unsigned Strings;
   unsigned ErrNo;
   int      ErrLine;
   char     Reliable;
} Hcode;

#ifdef ARCHAIC
#define __PROTO(p) ()
#else
#define __PROTO(p) p
#endif

#ifdef __TURBOC__
#if __STDC__
#define _Cdecl
#else
#define _Cdecl  cdecl
#endif

Hcode      *_Cdecl  load_4th (char *filename);
Hcode      *_Cdecl  fetch_4th (unit *embedded);
size_t      _Cdecl  store_4th (Hcode* Object, unit *Memory, size_t Limit);
void        _Cdecl  save_4th (Hcode *Object, char* filename);
void        _Cdecl  cgen_4th (Hcode *Object, FILE *SourceFp);
char        _Cdecl  dump_4th (Hcode *Object, FILE *Output, int From, int To);
void        _Cdecl  free_4th (Hcode *Object);
char       *_Cdecl  open_4th (char *SourceName);
Hcode      *_Cdecl  comp_4th (char *source);
cell        _Cdecl  exec_4th (Hcode *Object, unsigned ArgN, char** ArgS,
                              unsigned VarN, ...);

extern char *_Cdecl errs_4th [];
extern char *_Cdecl name_4th [];

#else

extern Hcode   *load_4th  __PROTO ((char *filename));
extern Hcode   *fetch_4th __PROTO ((unit *embedded));
extern size_t   store_4th __PROTO ((Hcode* Object, unit *Memory, size_t Limit));
extern void     save_4th  __PROTO ((Hcode *Object, char* filename));
extern void     cgen_4th  __PROTO ((Hcode *Object, FILE *SourceFp));
extern char     dump_4th  __PROTO ((Hcode *Object, FILE *Output, int From, int To));
extern void     free_4th  __PROTO ((Hcode *Object));
extern char    *open_4th  __PROTO ((char *SourceName));
extern Hcode   *comp_4th  __PROTO ((char *source));
extern cell     exec_4th  __PROTO ((Hcode *Object, unsigned ArgN, char** ArgS, unsigned VarN, ...));

extern char* errs_4th [];
extern char* name_4th [];

#endif
#endif

