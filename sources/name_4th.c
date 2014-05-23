/*
+-------+-----------------+------+-----------------+-------+-----------------+
|Program| NAME_4TH.C      |Header| 4TH.H           |Library| 4TH             |
+-------+-----------------+------+-----------------+-------+----------+------+
|HISTORY                                           |    Programmer    | Date |
+--------------------------------------------------+------------------+------+
| Turbo C V2.0 version                             | J.L. Bezemer     |190497|
+--------------------------------------------------+------------------+------+
|MODIFICATION LOG                                  |    Programmer    | Date |
+--------------------------------------------------+------------------+------+
| Added ARGS and ARGN                              | J.L. Bezemer     |240797|
| Added BRANCHXT and reorganized tokens            | J.L. Bezemer     |120997|
| Removed BRANCHXT                                 | J.L. Bezemer     |170997|
| Changed "-trail" to "-trailing"                  | J.L. Bezemer     |250997|
| Removed SHOW and RCOPY2                          | J.L. Bezemer     |260997|
| Removed INC2 and DEC2; added QDO                 | J.L. Bezemer     |151097|
| Removed QUERY; added REFILL                      | J.L. Bezemer     |311097|
| Changed NOT to INVERT                            | J.L. Bezemer     |011197|
| Added CATCH and CAUGHT                           | J.L. Bezemer     |191197|
| Added SQUOTE                                     | J.L. Bezemer     |200298|
| Removed WORD; added TOKEN and SKIP               | J.L. Bezemer     |190201|
| Removed TTY and FILE; added USE                  | J.L. Bezemer     |280202|
| Removed COPY, NOOP, TOKEN, FETCHPRM, GE, LE      | J.L. Bezemer     |060603|
| Added PARSE, OFETCH, STRINGD, CELLD, PLACE       | J.L. Bezemer     |060603|
| Changed SKIP to OMIT                             | J.L. Bezemer     |120603|
| Added SLEEP                                      | J.L. Bezemer     |031103|
| Added VECTOR                                     | J.L. Bezemer     |011203|
| Changed CELL to , and STRING to ,"               | J.L. Bezemer     |041203|
| Removed WAIT                                     | J.L. Bezemer     |140104|
| Changed OFETCH to FETCHC                         | J.L. Bezemer     |040305|
| Removed CLSPAREN, HI, FIRST, LAST; added ENVIRON | J.L. Bezemer     |110106|
| Added PLITERAL                                   | J.L. Bezemer     |130106|
| Added FSEEK, FTELL                               | J.L. Bezemer     |180106|
| Changed SLEEP to PAUSE                           | J.L. Bezemer     |181106|
| Added FSYNC; removed STSLHMOD                    | J.L. Bezemer     |030507|
| Added RADIX, OFFSET; removed HEX, DECIMAL, OCTAL | J.L. Bezemer     |201207|
| Removed RANDOM                                   | J.L. Bezemer     |241009|
| Added DELFILE                                    | J.L. Bezemer     |220610|
| Added ENVFETCH                                   | J.L. Bezemer     |010710|
| Changed "env@" to "environ@"                     | J.L. Bezemer     |140710|
| Removed INC, DEC                                 | J.L. Bezemer     |090812|
| Removed LEFT2, RIGHT2, added MLITERAL, DLITERAL  | J.L. Bezemer     |241012|
| Reinstated LEFT2 and RIGHT2                      | J.L. Bezemer     |251012|
| Mapped STRINGD to NOOP                           | J.L. Bezemer     |291012|
| Removed LEFT2, added SMOVE                       | J.L. Bezemer     |021212|
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


This array contains the names of all words of the portable 4tH compiler.
Please refer to other 4th functions for further documentation.
*/

char *name_4th [] = {
  ",\"",         "execute",  "cr",       "spaces",   "emit",      ".\"",
  ".",           "@",        "!",        "catch",    "(catch)",   "+",
  "-",           "*",        "/",        "mod",      "swap",      "dup",
  "over",        "rot",      "drop",     "=",        "<",         ">",
  "<>",          "invert",   "0<",       "0>",       "0branch",   "branch",
  "@c",          "and",      "or",       "xor",      "shift",     "abs",
  "negate",      "quit",     "min",      "max",      ">r",        "r>",
  "r@",          "0<>",      "0=",       "accept",   "radix",     "offset",
  "rp@",         "sp@",      "literal",  "+literal", "*literal",  "/literal",
  "?do",         "do",       "loop",     "+loop",    "leave",     "close",
  "open",        "use",      "+!",       "/mod",     "*/",        "exit",
  "j",           ".r",       "number",   "variable", "-trailing", "call",
  "refill",      "c@",       "c!",       "type",     "fill",      "count",
  "cmove",       "place",    "omit",     "parse",    "<#",        "#",
  "#>",          "#s",       "sign",     "hold",     "to",        "value",
  "time",        ",",        "s\"",      "pause",    "vector",    "environ",
  "throw",       "args",     "argn",     "seek",     "tell",      "sync",
  "delete-file", "smove",    "2/",       "environ@"
};
