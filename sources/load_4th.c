/*
+-------+-----------------+------+-----------------+-------+-----------------+
|Program| LOAD_4TH.C      |Header| 4TH.H           |Library| CEXT            |
+-------+-----------------+------+-----------------+-------+----------+------+
|HISTORY                                           |    Programmer    | Date |
+--------------------------------------------------+------------------+------+
| Turbo C V2.0 version                             | J.L. Bezemer     |250495|
+--------------------------------------------------+------------------+------+
|MODIFICATION LOG                                  |    Programmer    | Date |
+--------------------------------------------------+------------------+------+
| Fixed string-area bug                            | J.L. Bezemer     |280495|
| Definitely fixed void bug                        | J.L. Bezemer     |010595|
| Added ErrLin4th                                  | J.L. Bezemer     |030595|
| New Version4th added                             | J.L. Bezemer     |140995|
| Updated errors                                   | J.L. Bezemer     |220995|
| Added support for Hcode                          | J.L. Bezemer     |120296|
| Changed header to check alignment; fixed bug     | J.L. Bezemer     |130396|
| Removed LoadBlock(); added LoadByte(), LoadCell()| J.L. Bezemer     |100496|
| Added LoadInfo(), LoadHeader() and LoadCode()    | J.L. Bezemer     |100496|
| Added LoadString(), LoadCheck()                  | J.L. Bezemer     |100496|
| Fixed bugs in LoadString() and LoadCheck()       | J.L. Bezemer     |110496|
| Added RaiseError()                               | J.L. Bezemer     |120496|
| Rewrote most for new Hcode format                | J.L. Bezemer     |021096|
| Renamed Appl4th to App4th                        | J.L. Bezemer     |031296|
| Added LOCAL_H support                            | J.L. Bezemer     |220597|
| Removed <limits.h>                               | J.L. Bezemer     |250797|
| Added BRANCHXT; changed header fieldname         | J.L. Bezemer     |120997|
| Removed BRANCHXT                                 | J.L. Bezemer     |170997|
| Added QDO                                        | J.L. Bezemer     |151097|
| Forgot to close file if calloc() failed          | J.L. Bezemer     |171097|
| Removed EasyC syntax                             | J.L. Bezemer     |150198|
| Updated version info                             | J.L. Bezemer     |180298|
| Added SQUOTE                                     | J.L. Bezemer     |200298|
| Added inst_4th() and support functions           | J.L. Bezemer     |081298|
| Added some documentation                         | J.L. Bezemer     |101298|
| Added LoadValue(); more compact HX format        | J.L. Bezemer     |140999|
| Cleaned up encoding constants                    | J.L. Bezemer     |150999|
| Replaced bytecode datatype by unit datatype      | J.L. Bezemer     |301099|
| Return CodeSiz in ErrLine when successful        | J.L. Bezemer     |031199|
| Fixed major bug; CSIn now properly initialized   | J.L. Bezemer     |111199|
| Added CELLD, STRINGD; removed NOOP               | J.L. Bezemer     |060603|
| Renamed inst_4th() to fetch_4th()                | J.L. Bezemer     |060603|
| Added VECTOR                                     | J.L. Bezemer     |011203|
| Added dormant HX support                         | J.L. Bezemer     |050104|
| Added hidden variables support                   | J.L. Bezemer     |120304|
| Changed 'n' to unsigned in LoadString()          | J.L. Bezemer     |231205|
| Added ENVIRON                                    | J.L. Bezemer     |110106|
| Added PLITERAL                                   | J.L. Bezemer     |130106|
| Added RADIX, OFFSET                              | J.L. Bezemer     |201207|
| Converted LoadCheck() to a macro                 | J.L. Bezemer     |100708|
| Fixed deallocation error in LoadHX()             | J.L. Bezemer     |060111|
| Fixed TurboC warning on long constant in LoadHX()| J.L. Bezemer     |290312|
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


These functions load HX bytecode into memory. Compatibility is tested!

Prototype: Hcode* load_4th (char *filename)
Returns  : Object is compatible and loadable; NULL if not.
Memory   : header, object and string-area's are allocated on success
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

  object = load_4th ("easter.hx");
  dump_4th (object, stdout, 0, -1);
  free_4th (object);
  return (EXIT_SUCCESS);
}

Input    : None
Output   : depends on program
Related  : inst_4th()


Prototype: Hcode* inst_4th (unit *embedded)
Returns  : Object is compatible and loadable; NULL if not.
Memory   : header, object and string-area's are allocated on success
Example  :

#include "4th.h"
#include <stdlib.h>

#ifndef ARCHAIC
  int main (int argc, char **argv)
#else
  int main (argc, argv) int argc; char **argv;
#endif

{
  static unit EmbeddedHX [] = {
    '\x01', '\x02', '\x04', '\x00', '\xff', '\xff', '\xff', '\x7f',
    '\x04', '\x3b', '\x03', '\x08', '\x02', '\x02', '\x02', '\x0d',
    '\x08', '\x08', '\x05', '\x08', '\x02', '\x48', '\x65', '\x6c',
    '\x6c', '\x6f', '\x20', '\x77', '\x6f', '\x72', '\x6c', '\x64',
    '\x21', '\x00', '\x92', '\x00'
  };

  Hcode *object;

  object = inst_4th (EmbeddedHX);
  dump_4th (object, stdout, 0, -1);
  free_4th (object);
  return (EXIT_SUCCESS);
}

Input    : None
Output   : depends on program
Related  : load_4th()
*/

#ifdef USRLIB4TH
#include <4th.h>
#include <sys/cmds_4th.h>
#else
#include "4th.h"
#include "cmds_4th.h"
#endif

#define LoadCheck() {LoadUnit();if(CSIn)RaiseError(M4BADOBJ);}

#include <stdlib.h>
#include <string.h>

static FILE*     HXIn;                  /* pointer to HX-file */
static unit*     BytecodeIn;            /* pointer to embedded HX */
static Hcode*    Object;                /* Hcode pointer */
static int       CSIn;                  /* checksum for reading */


#ifdef ARCHAIC
  static int (*LoadByte) ();           /* loader function (K&R) */
#else
  static int (*LoadByte) (void);       /* loader function (ANSI) */
#endif

/*
This function only sets ErrNo if no errors have occured yet.
*/

#ifndef ARCHAIC
  static void RaiseError (unsigned error)
#else
  static void RaiseError (error) unsigned error;
#endif

{
  if (! Object->ErrNo) Object->ErrNo = error;
}


/*
This low level function only loads a byte from the HX-file.
*/

#ifndef ARCHAIC
  static int LoadFileByte (void)
#else
  static int LoadFileByte ()
#endif

{
  int Hc;

  if ((Hc = fgetc (HXIn)) == EOF) RaiseError (M4IOERR);
  return (Hc);
}


/*
This low level function only loads a byte from the embedded HX-code.
*/

#ifndef ARCHAIC
  static int LoadEmbedByte (void)
#else
  static int LoadEmbedByte ()
#endif

{
  return (*(BytecodeIn++));
}


/*
This function only loads an addressunit from the HX-code if there have been
no errors up to now. Furthermore a checksum is calculated.
*/

#ifndef ARCHAIC
  static int LoadUnit (void)
#else
  static int LoadUnit ()
#endif

{
  int Hc;

  if (! Object->ErrNo)
     {
       Hc = (*(LoadByte)) ();
       CSIn ^= Hc;
       return (Hc);
     }

  return (0);
}


/*
This function loads a value in tiny, small or full length
*/

#ifndef ARCHAIC
  static cell LoadValue (size_t Max, char Sign)
#else
  static cell LoadValue (Max, Sign) size_t Max; char Sign;
#endif

{
  size_t n;                            /* number of bytes in a cell */
  cell Value = 0L;

  for (n = 0; n < (Max * HBITS); n += HBITS)
      Value += (((cell) LoadUnit ()) << n);

  return ((Sign ? -Value : Value));
}


/*
This function loads an integer value up to the size of a cell from an HX-file.
Like Forth, its components are broken up into an non-negative number and a
sign-byte.
*/

#ifndef ARCHAIC
  static cell LoadCell (void)
#else
  static cell LoadCell ()
#endif

{
  char Type  = (char) LoadUnit ();

  switch ((Type & (~HCSIGN)))    /* select the type of encoding */
    {
      case (HCZERO): return (Type & HSNEG ? CELL_MIN : 0L);
      case (HCONE ): return (Type & HSNEG ? -1L : 1L);
      case (HCBYTE): return (LoadValue (sizeof (char), Type & HSNEG));
      case (HCSHRT): return (LoadValue (sizeof (short), Type & HSNEG));
      case (HCCELL): return (LoadValue (sizeof (cell), Type & HSNEG));
      default      : RaiseError (M4BADOBJ); return (0L);
    }
}


/*
This function checks whether the loaded executable is compatible with the
4tH virtual machine. If not, ErrNo4th is set.
*/

#ifndef ARCHAIC
  static void LoadInfo (void)
#else
  static void LoadInfo ()
#endif

{
  if (LoadUnit () == (char) sizeof (char))
     if (LoadUnit () == (char) sizeof (short))
        if (LoadUnit () == (char) sizeof (cell))
           if (LoadCell () == CELL_MAX)
              if (LoadCell () == (cell) Version4th)
                 if (LoadCell () == (cell) App4th) return;

  RaiseError (M4BADOBJ);
}


/*
This function creates and loads the Code Segment.
*/

#ifndef ARCHAIC
  static void LoadCode (void)
#else
  static void LoadCode ()
#endif

{
  int n;

  if (Object->ErrNo) Object->CodeSeg = NULL;
  else
    if ((Object->CodeSeg = (dict*) calloc ((size_t) Object->CodeSiz,
       sizeof (dict))) == NULL)
       RaiseError (M4NOMEM);
    else
       {
         for (n = 0; n < Object->CodeSiz; n++)
             {
               Object->CodeSeg [n].Word = (unit) LoadUnit ();
               switch (Object->CodeSeg [n].Word)
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
                   case (CALL): Object->CodeSeg [n].Value = LoadCell ();
                                break;
                   default:     Object->CodeSeg [n].Value = 0L;
                                break;
                 }
             }
       }
}


/*
This function creates and loads the String Segment.
*/

#ifndef ARCHAIC
  static void LoadString (void)
#else
  static void LoadString ()
#endif

{
  unsigned n;

  if ((Object->ErrNo) || (Object->StringSiz == 0)) Object->StringSeg = NULL;
  else
    if ((Object->StringSeg = (char*) calloc ((size_t)
       Object->StringSiz, sizeof (char))) == NULL)
       RaiseError (M4NOMEM);
    else
       for (n = 0; n < Object->StringSiz; n++)
           Object->StringSeg [n] = (char) LoadUnit ();
}


/*
This function creates and loads the Unit Segment.
*/

#ifndef ARCHAIC
  static void LoadUnits (void)
#else
  static void LoadUnits ()
#endif

{
  int n;
  int u = Object->Strings + TIBSIZ + PADSIZ + 1;

  if ((Object->ErrNo) || (Object->Offset == 0)) Object->UnitSeg = NULL;
  else
    if ((Object->UnitSeg = (unit*) calloc ((size_t) u, sizeof (unit))) == NULL)
       RaiseError (M4NOMEM);
    else
       for (n = 0; n < u; n++) Object->UnitSeg [n] = (unit) LoadUnit ();
}


/*
This function creates and loads the Cell Segment.
*/

#ifndef ARCHAIC
  static void LoadCells (void)
#else
  static void LoadCells ()
#endif

{
  int n;
  int c = Object->Variables + Object->Offset + STACKSIZ + SYS4TH;

  if ((Object->ErrNo) || (Object->Offset == 0)) Object->CellSeg = NULL;
  else
    if ((Object->CellSeg = (cell*) calloc ((size_t) c, sizeof (cell))) == NULL)
       RaiseError (M4NOMEM);
    else
       for (n = 0; n < c; n++) Object->CellSeg [n] = LoadCell ();
}


/*
This routine creates, loads and initializes the header.
*/

#ifndef ARCHAIC
  static void LoadHeader (void)
#else
  static void LoadHeader ()
#endif

{
  Object->CodeSiz   = (int)      LoadCell ();
  Object->StringSiz = (unsigned) LoadCell ();
  Object->Offset    = (unsigned) LoadCell ();
  Object->Variables = (unsigned) LoadCell ();
  Object->Strings   = (unsigned) LoadCell ();
}


/*
This is a generalized way to read in HX code, in whatever way it is stored
*/

#ifndef ARCHAIC
  static void LoadHX (void)
#else
  static void LoadHX ()
#endif

{
  if ((Object = (Hcode*) calloc (1, sizeof (Hcode))) == NULL) return;

  CSIn = 0;                            /* reset checksum */
  Object->ErrNo = M4NOERRS;            /* reset errors */

  LoadInfo   ();                       /* load version info */
  LoadHeader ();                       /* load header */
  LoadCode   ();                       /* load code segment */
  LoadString ();                       /* load string segment */
  LoadUnits  ();                       /* load unit segment */
  LoadCells  ();                       /* load cell segment */
  LoadCheck  ();                       /* load checksum */
                                       /* on error: release all segments */
  if (Object->ErrNo)
    {
      if (Object->StringSeg) free (Object->StringSeg);
      if (Object->CodeSeg)   free (Object->CodeSeg);
      if (Object->UnitSeg)   free (Object->UnitSeg);
      if (Object->CellSeg)   free (Object->CellSeg);
      Object->CodeSiz  = Object->StringSiz = Object->Offset  =
      Object->Strings  = Object->Variables = Object->ErrLine = 0;
      Object->StringSeg = NULL;
      Object->CodeSeg   = NULL;
      Object->UnitSeg   = NULL;
      Object->CellSeg   = NULL;
      Object->Reliable  = FALSE;
    }
  else                                 /* flag all ok */
    {
      Object->ErrLine  = Object->CodeSiz;
      Object->Reliable = TRUE;
    }
}


/*
The API hook to read HX files. It opens the file and sets up the proper
parameters. It returns a pointer to Hcode if successful, otherwise
a NULL pointer.
*/

#ifndef ARCHAIC
  Hcode* load_4th (char *filename)
#else
  Hcode* load_4th (filename) char* filename;
#endif

{
  if ((HXIn = fopen (filename, "rb")) == NULL) return (NULL);
  LoadByte = LoadFileByte;
  LoadHX ();
  if (fclose (HXIn)) RaiseError (M4IOERR);

  return (Object);
}


/*
The API hook to read embedded HX code. It sets up the proper
parameters. It returns a pointer to Hcode if successful, otherwise
a NULL pointer.
*/

#ifndef ARCHAIC
  Hcode* fetch_4th (unit *embedded)
#else
  Hcode* fetch_4th (embedded) unit *embedded;
#endif

{
  BytecodeIn = embedded;
  LoadByte = LoadEmbedByte;
  LoadHX ();
  return (Object);
}
