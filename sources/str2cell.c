/*
+-------+-----------------+------+-----------------+-------+-----------------+
|Program| STR2CELL.C      |Header| CMDS_4TH.H      |Library| 4TH             |
+-------+-----------------+------+-----------------+-------+----------+------+
|HISTORY                                           |    Programmer    | Date |
+--------------------------------------------------+------------------+------+
| Linux 2.6.25 version                             | J.L. Bezemer     |081011|
+--------------------------------------------------+------------------+------+
|MODIFICATION LOG                                  |    Programmer    | Date |
+--------------------------------------------------+------------------+------+
| None                                             |                  |      |
+--------------------------------------------------+------------------+------+
|REMARKS                                           |    Programmer    | Date |
+--------------------------------------------------+------------------+------+
| None                                             |                  |      |
+--------------------------------------------------+------------------+------+

  Copyright (C) 2011 J.L. Bezemer

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


This routine converts a string to a number between -MAX-N and
MAX-N. It returns (ERROR) on error. An error occurs when the number is out
of range or when the string does not represent a valid number in the current
base. Leading whitespace is skipped.

Prototype: void str2cell (char *str, cell base)
Returns  : cell
Memory   : None
Example  :

#include "cmds_4th.h"
#include <stdlib.h>
#include <stdio.h>

#ifndef ARCHAIC
  int main (int argc, char **argv)
#else
  int main (argc, argv) int argc; char **argv;
#endif

{
  printf ("%ld\n", str2cell ("     +2147483647", 10));
  printf ("%ld\n", str2cell ("     -2147483647", 10));

  return (EXIT_SUCCESS);
}

Input    : None
Output   : 2147483647
           -2147483647
Related  : exec_4th(), comp_4th()
*/

#ifdef USRLIB4TH
#include <4th.h>
#else
#include "4th.h"
#endif

#include <ctype.h>


#ifndef ARCHAIC
  cell str2cell (char *str, cell base)
#else
  cell str2cell (str, base) char *str; cell base;
#endif

{
  char sign = FALSE;                   /* assume positive integer */
  cell cutoff = (CELL_MAX/base);       /* maximum value of accumulator */
  cell cutlim = (CELL_MAX%base);       /* maximum addition to accumulator */
  cell acc = 0L;                       /* reset accumulator */
  cell c;                              /* value of digit */
                                       /* eliminate leading whitespace */
  for(; *str == '\t' || *str == '\r' || *str == '\f' ||
        *str == '\v' || *str == '\n' || *str == ' '; str++);
                                       /* skip plus sign */
  if (*str == '+') str++;
                                       /* skip minus sign and set sign */
  if (*str == '-')
     {
       str++; sign = TRUE;
     }
                                       /* check for NULL string */
  if (*str == 0) return (CELL_MIN);
                                       /* convert string */
  for (; *str; str++)
      {                                /* get digit and convert */
        if ((c = toupper (*str) - '0') < ('A' - '0')) c = (c > 9) ? base : c;
        else c += (('0' + 10) - 'A');
                                       /* check range */
        if ((c < 0) || (c >= base) || acc > cutoff ||
           ((acc == cutoff) && (c > cutlim))) return (CELL_MIN);
                                       /* return error if out of range */
        acc *= base;                   /* shift accumulator */
        acc += c;                      /* add digit */
      }

  return (sign ? -acc : acc);          /* apply sign and return */
}

