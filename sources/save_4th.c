/*
+-------+-----------------+------+-----------------+-------+-----------------+
|Program| SAVE_4TH.C      |Header| 4TH.H           |Library| 4TH             |
+-------+-----------------+------+-----------------+-------+----------+------+
|HISTORY                                           |    Programmer    | Date |
+--------------------------------------------------+------------------+------+
| Turbo C V2.0 version                             | J.L. Bezemer     |210495|
| Linux V2.2.10 version                            | J.L. Bezemer     |190600|
+--------------------------------------------------+------------------+------+
|MODIFICATION LOG                                  |    Programmer    | Date |
+--------------------------------------------------+------------------+------+
| Added ErrLin4th                                  | J.L. Bezemer     |030595|
| Added support for Hcode                          | J.L. Bezemer     |120296|
| Added SaveBlock()                                | J.L. Bezemer     |130396|
| Removed SaveBlock(); added SaveByte(), SaveCell()| J.L. Bezemer     |100496|
| Added SaveInfo(), SaveHeader() and SaveCode()    | J.L. Bezemer     |100496|
| Added SaveString()                               | J.L. Bezemer     |100496|
| Rewrote in order to accomodate new Hcode format  | J.L. Bezemer     |021096|
| Renamed Appl4th to App4th                        | J.L. Bezemer     |031296|
| Added LOCAL_H support                            | J.L. Bezemer     |220597|
| Removed <stdio.h> and <limits.h>                 | J.L. Bezemer     |250797|
| Added BRANCHXT; changed header fieldname         | J.L. Bezemer     |120997|
| Removed BRANCHXT                                 | J.L. Bezemer     |170997|
| Added QDO                                        | J.L. Bezemer     |151097|
| Removed EasyC syntax                             | J.L. Bezemer     |150198|
| Checks open file before closing                  | J.L. Bezemer     |180298|
| Added SQUOTE                                     | J.L. Bezemer     |200298|
| Added SaveValue(); more compact HX format        | J.L. Bezemer     |140999|
| Cleaned up encoding constants                    | J.L. Bezemer     |150999|
| Fixed serious bug in SaveCell()                  | J.L. Bezemer     |111099|
| Always return CodeSiz in ErrLine                 | J.L. Bezemer     |031199|
| Fixed major bug; CSOut now properly initialized  | J.L. Bezemer     |111199|
| Fixed small error in K&R prototype               | J.L. Bezemer     |291299|
| Fixed some Linux warnings (no need; code is OK)  | J.L. Bezemer     |190600|
| Added CELLD, STRINGD; removed NOOP               | J.L. Bezemer     |060603|
| Added SaveUnit(), SaveHX() and store_4th()       | J.L. Bezemer     |230603|
| Fixed tiny bug in SaveEmbedByte()                | J.L. Bezemer     |010703|
| Added VECTOR                                     | J.L. Bezemer     |011203|
| Added dormant HX support                         | J.L. Bezemer     |050104|
| Added hidden variables support                   | J.L. Bezemer     |120304|
| Changed 'n' to unsigned in SaveString()          | J.L. Bezemer     |231205|
| Added ENVIRON                                    | J.L. Bezemer     |110106|
| Added PLITERAL                                   | J.L. Bezemer     |130106|
| Added RADIX, OFFSET                              | J.L. Bezemer     |201207|
| Applied Coherent patches                         | J.L. Bezemer     |020112|
| Added DLITERAL, MLITERAL                         | J.L. Bezemer     |241012|
+--------------------------------------------------+------------------+------+
|REMARKS                                           |    Programmer    | Date |
+--------------------------------------------------+------------------+------+
| None                                             |                  |      |
+--------------------------------------------------+------------------+------+

  Copyright (C) 1997,2012 J.L. Bezemer

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


This routine writes the contents of an object to disk. It can then be loaded
with load_4th(). The object is pointed to by Program, filename must contain
a valid filename.

Prototype: void save_4th (Hcode *Program, char *filename)
Returns  : nothing
Memory   : none
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

  if (argc == 2)
    {
      if ((sources = open_4th (argv [1])) == NULL)
         printf ("Loading; \'%s\' does not exist or too large\n", argv [1]);
      else
        {
          object = comp_4th (sources);
          if (object)
              printf ("Compile; word %u: %s\n", object->ErrLine,
                     errs_4th [object->ErrNo]);
          save_4th (object, "out.hx");
          return (object->ErrNo ? EXIT_FAILURE : EXIT_SUCCESS);
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

#define SaveCheck() SaveUnit(CSOut)

static FILE*     HXOut;                /* pointer to HX-file */
static size_t    MaxBytes;             /* size of array */
static size_t    Stored;
static unit*     BytecodeOut;          /* pointer to embedded HX */
static int       CSOut;                /* checksum */
static unsigned* SaveErr;


#ifndef ARCHAIC
  static void (*SaveByte) (int Value);           /* save function (ANSI) */
#else
  static void (*SaveByte) ();                    /* save function  (K&R) */
#endif

/*
This low level function only saves a byte to the HX-file. In fact
a dedicated version of fputc().
*/

#ifndef ARCHAIC
  static void SaveFileByte (int Value)
#else
  static void SaveFileByte (Value) int Value;
#endif

{
  if (fputc (Value, HXOut) == EOF) *SaveErr = M4IOERR;
}


/*
This low level function only saves a byte to embedded HX-code.
*/

#ifndef ARCHAIC
  static void SaveEmbedByte (int Value)
#else
  static void SaveEmbedByte (Value) int Value;
#endif

{
  if (Stored < MaxBytes)
     {
       *(BytecodeOut++) = Value;
       Stored++;
     }
  else *SaveErr = M4NOMEM;
}


/*
This function only saves a byte to the HX-file if there have been no errors up
to now. Furthermore a checksum is generated.
*/

#ifndef ARCHAIC
  static void SaveUnit (int Value)
#else
  static void SaveUnit (Value) int Value;
#endif

{
  if (! *SaveErr)
     {
       (*(SaveByte)) (Value);
       CSOut ^= Value;
     }
}


/*
This function saves a value in tiny, small or full length.
*/

#ifndef ARCHAIC
  static void SaveValue (cell Value, size_t Max)
#else
  static void SaveValue (Value, Max) cell Value; size_t Max;
#endif

{

  size_t n;

  for (n = 0 ; n < Max; n++)
      {                                /* save each byte */
        SaveUnit ((int) (Value & (cell) HMASK));
        Value >>= HBITS;               /* get the next byte */
      }
}


/*
This function saves an integer value up to the size of a cell to an HX-file.
Like Forth, its components are broken up into an non-negative number and a
sign-byte.
*/

#ifndef ARCHAIC
  static void SaveCell (cell Value)
#else
  static void SaveCell (Value) cell Value;
#endif

{
  int Sign;
                                       /* handle special cases first */
      if      (Value == -1L)      SaveUnit  (HCONE  | HSNEG);
      else if (Value ==  0L)      SaveUnit  (HCZERO | HSPOS);
      else if (Value ==  1L)      SaveUnit  (HCONE  | HSPOS);
      else if (Value == CELL_MIN) SaveUnit  (HCZERO | HSNEG);
      else {
             if ((Sign = (Value < 0 ? HSNEG : HSPOS)) == TRUE) Value = -Value;
                                       /* take care of the sign */
             if (Value <= (cell) HNTINY)
                {                      /* this fits in a byte */
                   SaveUnit  (HCBYTE | Sign);
                   SaveValue (Value, sizeof (char));
                }
             else if (Value <= (cell) HNSMALL)
                {                      /* this fits in a short */
                   SaveUnit  (HCSHRT | Sign);
                   SaveValue (Value, sizeof (short));
                }
             else
                {                      /* this number needs full cell */
                   SaveUnit  (HCCELL | Sign);
                   SaveValue (Value, sizeof (cell));
                }
      }
}


/*
This function saves all info which identifies the HX-program.
*/

#ifndef ARCHAIC
  static void SaveInfo (void)
#else
  static void SaveInfo ()
#endif

{
  SaveUnit (sizeof (char));
  SaveUnit (sizeof (short));
  SaveUnit (sizeof (cell));
  SaveCell (CELL_MAX);                 /* save sizes of numbers */
  SaveCell ((cell) Version4th);        /* save version info */
  SaveCell ((cell) App4th);
}


/*
This function saves all information which describes the programs runtime-
environment.
*/

#ifndef ARCHAIC
  static void SaveHeader (Hcode* ObjHead)
#else
  static void SaveHeader (ObjHead) Hcode* ObjHead;
#endif

{
  SaveCell ((cell) ObjHead->CodeSiz);
  SaveCell ((cell) ObjHead->StringSiz);
  SaveCell ((cell) ObjHead->Offset);
  SaveCell ((cell) ObjHead->Variables);
  SaveCell ((cell) ObjHead->Strings);
}


/*
This function saves the program-code in a condensed format. Only those
words which need an argument have their arguments saved.
*/

#ifndef ARCHAIC
  static void SaveCode (Hcode* ObjCode)
#else
  static void SaveCode (ObjCode) Hcode* ObjCode;
#endif

{
  int n;

  for (n = 0; n < ObjCode->CodeSiz; n++)
      {
        SaveUnit  ((int) ObjCode->CodeSeg [n].Word);

        switch (ObjCode->CodeSeg [n].Word)
          {
            case (VARIABLE):
            case (VALUE):
            case (ENVIRON):
            case (VECTOR):
            case (TO):
            case (CELLD):
            case (STRINGD):
            case (LITERAL):
            case (PLITERAL):
            case (MLITERAL):
            case (DLITERAL):
            case (PRINT):
            case (SQUOTE):
            case (BRANCH):
            case (BRANCH0):
            case (QDO):
            case (LOOP):
            case (PLOOP):
            case (RADIX):
            case (OFFSET):
            case (CALL): SaveCell (ObjCode->CodeSeg [n].Value); break;
          }
      }
}


/*
This function simply saves the contents of the StringSegment.
*/

#ifndef ARCHAIC
  static void SaveString (Hcode* ObjStr)
#else
  static void SaveString (ObjStr) Hcode* ObjStr;
#endif

{
  unsigned n;

  for (n = 0; n < ObjStr->StringSiz; n++)
      SaveUnit  ((int) ObjStr->StringSeg [n]);
}


/*
This function simply saves the contents of the Environment.
*/

#ifndef ARCHAIC
  static void SaveEnv (Hcode* ObjEnv)
#else
  static void SaveEnv (ObjEnv) Hcode* ObjEnv;
#endif

{
  int n;
  int u = ObjEnv->Strings + TIBSIZ + PADSIZ + 1;
  int c = ObjEnv->Variables + ObjEnv->Offset + STACKSIZ + SYS4TH;

  if (! ObjEnv->Offset) return;

  for (n = 0; n < u; n++) SaveUnit ((int) ObjEnv->UnitSeg [n]);
  for (n = 0; n < c; n++) SaveCell (ObjEnv->CellSeg [n]);
}


/*
This function sets up some common variables and writes the HX code.
*/

#ifndef ARCHAIC
  static void SaveHX (Hcode* Obj)
#else
  static void SaveHX (Obj) Hcode* Obj;
#endif

{
  CSOut        = 0;                  /* reset checksum */
  SaveErr      = &(Obj->ErrNo);      /* global pointer */
  Obj->ErrNo   = M4NOERRS;           /* reset errors */
  Obj->ErrLine = Obj->CodeSiz;       /* signal all saved */

  SaveInfo   ();
  SaveHeader (Obj);
  SaveCode   (Obj);
  SaveString (Obj);
  SaveEnv    (Obj);
  SaveCheck  ();
}


/*
The API hook to write HX file. It sets up the proper
parameters. It returns nothing. Be sure to check the
ErrNo member.
*/

#ifndef ARCHAIC
  void save_4th (Hcode* Object, char* filename)
#else
  void save_4th (Object, filename) Hcode* Object; char* filename;
#endif

{
  if (Object)                        /* check if object is reliable */
    if (Object->Reliable)
      {
        if ((HXOut = fopen (filename, "wb")) == NULL)
           Object->ErrNo = M4IOERR;
        else
           {
             SaveByte = SaveFileByte;
             SaveHX (Object);
             if (fclose (HXOut)) Object->ErrNo = M4IOERR;
           }
      }
}


/*
The API hook to write embedded HX code. It sets up the proper
parameters. It returns the number of bytes written if
(partially) successful, otherwise zero. Be sure to check the
ErrNo member.
*/

#ifndef ARCHAIC
  size_t store_4th (Hcode* Object, unit *Memory, size_t Limit)
#else
  size_t store_4th (Object, Memory, Limit) Hcode* Object; char* Memory;
                    size_t Limit;
#endif

{
  if (Object)              /* check if object is reliable */
    if (Object->Reliable)
      {
         Stored      = 0;
         MaxBytes    = Limit;
         BytecodeOut = Memory;
         SaveByte    = SaveEmbedByte;

         SaveHX (Object);
         return (Stored);
      }
  return (0);
}

