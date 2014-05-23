/*
+-------+-----------------+------+-----------------+-------+-----------------+
|Program| OPEN_4TH        |Header| 4TH.H           |Library| EXTLIB          |
+-------+-----------------+------+-----------------+-------+----------+------+
|HISTORY                                           |    Programmer    | Date |
+--------------------------------------------------+------------------+------+
| TurboC V2.0 version                              | J.L. Bezemer     |151199|
| DJGPP V2.72 version                              | J.L. Bezemer     |151199|
| Linux V2.2.10 version                            | J.L. Bezemer     |190600|
+--------------------------------------------------+------------------+------+
|MODIFICATION LOG                                  |    Programmer    | Date |
+--------------------------------------------------+------------------+------+
| Fixed some Linux warnings (no need; code is OK)  | J.L. Bezemer     |190600|
| Rewrote function for V3.3d, Release 2            | J.L. Bezemer     |300103|
| Added (char *)                                   | J.L. Bezemer     |311009|
+--------------------------------------------------+------------------+------+
|REMARKS                                           |    Programmer    | Date |
+--------------------------------------------------+------------------+------+
| None                                             |                  |      |
+--------------------------------------------------+------------------+------+

  Copyright (C) 1996,2003 J.L. Bezemer

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


Returns a pointer to a character array containing the command
'[NEEDS <source>]'. Returns NULL-pointer on error.

Prototype: char *open_4th (char* Source)
Returns  : Pointer to character array on success; else NULL
Memory   : The name of the file plus 9 characters
Example  :


#include "4th.h"
#include <stdlib.h>

#ifndef ARCHAIC
  int main (int argc, char **argv)
#else
  int main (argc, argv) int argc; char **argv;
#endif

begin

  Hcode *object;
  char  *sources;

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
Output   : depends on machine
Related  : comp_4th()
*/

#define  KEYWORD 7

#include <stdlib.h>
#include <string.h>

#ifndef ARCHAIC
  char *open_4th (char* Source)
#else
  char *open_4th (Source) char *Source;
#endif

{
  char *p;

  if ((p = (char *) calloc (strlen (Source) +  KEYWORD + 2, sizeof (char)))
     == NULL) return (NULL);
  else return (strcat (strcat (strcat (p, "[NEEDS "), Source), "]"));
}

