/*
+-------+-----------------+------+-----------------+-------+-----------------+
|Program| ERRS_4TH.C      |Header| 4TH.H           |Library| CEXT            |
+-------+-----------------+------+-----------------+-------+----------+------+
|HISTORY                                           |    Programmer    | Date |
+--------------------------------------------------+------------------+------+
| Turbo C V2.0 version                             | J.L. Bezemer     |181094|
| DPX/2 340 version                                | J.L. Bezemer     |181094|
| Coherent V4.2 version                            | J.L. Bezemer     |201094|
| Linux 2.2.10 version                             | J.L. Bezemer     |170600|
+--------------------------------------------------+------------------+------+
|MODIFICATION LOG                                  |    Programmer    | Date |
+--------------------------------------------------+------------------+------+
| Added M4UNKKEY                                   | J.L. Bezemer     |201094|
| Added M4IOERR and M4INTERR                       | J.L. Bezemer     |271094|
| Full update on error messages                    | J.L. Bezemer     |220995|
| Renamed ErrList4th[] to errs_4th[]               | J.L. Bezemer     |270996|
| Added M4BADPTR, updated mnemonics                | J.L. Bezemer     |191196|
| Removed M4UNKTOK                                 | J.L. Bezemer     |031296|
| Removed M4INTERR                                 | J.L. Bezemer     |060297|
| Added M4ASSERT, updated mnemonics                | J.L. Bezemer     |110497|
| Added M4THROW                                    | J.L. Bezemer     |190497|
| Removed M4TABFUL; changed M4THROW                | J.L. Bezemer     |200497|
| Changed M4THROW                                  | J.L. Bezemer     |230497|
| Made THROW codes more ANS-Forth compatible       | J.L. Bezemer     |120997|
| Added M4CABORT                                   | J.L. Bezemer     |170600|
| Added M4NOTYPE                                   | J.L. Bezemer     |130511|
| Added M4BADNAM                                   | J.L. Bezemer     |090412|
+--------------------------------------------------+------------------+------+
|REMARKS                                           |    Programmer    | Date |
+--------------------------------------------------+------------------+------+
| None                                             |                  |      |
+--------------------------------------------------+------------------+------+

  Copyright (C) 1994,2012 J.L. Bezemer

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


This array contains the error-messages of the portable 4tH compiler. Please
refer to other 4th functions for further documentation. In a lot of ways it
is very like sys_errlist [].
*/

char *errs_4th [] = {
  "No errors",
  "Out of memory",
  "Bad object",
  "Stack overflow",
  "Stack empty",
  "Return stack overflow",
  "Return stack empty",
  "Bad string",
  "Bad variable",
  "Bad address",
  "Divide by zero",
  "Bad token",
  "Wrong type",
  "Undefined name",
  "I/O error",
  "Assertion failed" ,
  "Unhandled exception" ,
  "Bad radix",
  "Bad stream",
  "Bad literal",
  "Bad pointer",
  "Nesting too deep",
  "No program",
  "Incomplete declaration",
  "Unmatched conditional",
  "Unterminated string",
  "Null string",
  "Duplicate name",
  "Name too long",
  "Compilation aborted"
 };

