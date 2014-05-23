/*
+-------+-----------------+------+-----------------+-------+-----------------+
|Program| FREE_4TH.C      |Header| 4TH.H           |Library| EXTLIB          |
+-------+-----------------+------+-----------------+-------+----------+------+
|HISTORY                                           |    Programmer    | Date |
+--------------------------------------------------+------------------+------+
| Turbo C V2.0 version                             | HanSoft          |140495|
+--------------------------------------------------+------------------+------+
|MODIFICATION LOG                                  |    Programmer    | Date |
+--------------------------------------------------+------------------+------+
| Renamed members of Hcode structure               | J.L Bezemer      |270996|
| Added LOCAL_H support                            | J.L. Bezemer     |220597|
| Removed EasyC syntax                             | J.L. Bezemer     |150198|
| Updated version info                             | J.L. Bezemer     |180198|
| Added SLEEP support                              | J.L. Bezemer     |031103|
+--------------------------------------------------+------------------+------+
|REMARKS                                           |    Programmer    | Date |
+--------------------------------------------------+------------------+------+
| None                                             |                  |      |
+--------------------------------------------------+------------------+------+

  Copyright (C) 1997,2003 J.L. Bezemer

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


This small routine takes the fuzz out of freeing a 4tH program. It checks the
pointers and frees them if possible

Prototype: void free_4th (Hcode *Program)
Returns  : Nothing
Memory   : None
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
          printf ("Compile; word %u: %s\n", object->ErrLine,
                 errs_4th [object->ErrNo]);
          dump_4th (object, stdout, 0, -1);
          free_4th (object);
          return (EXIT_SUCCESS);
        }
    }
  return (EXIT_FAILURE);
}


Input    : None
Output   : depends on program
Related  : dump_4th(), exec_4th(), comp_4th()
*/

#ifdef USRLIB4TH
#include <4th.h>
#else
#include "4th.h"
#endif

#include <stdlib.h>


#ifndef ARCHAIC
  void free_4th (Hcode* Object)
#else
  void free_4th (Object) Hcode* Object;
#endif

{
  if (Object)
     {
       if (Object->StringSeg) free (Object->StringSeg);
       if (Object->CodeSeg)   free (Object->CodeSeg);
       if (Object->UnitSeg)   free (Object->UnitSeg);
       if (Object->CellSeg)   free (Object->CellSeg);
       free (Object);
     }
}

