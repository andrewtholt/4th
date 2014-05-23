/*
+-------+-----------------+------+-----------------+-------+-----------------+
|Program| 4TH.C           |Module| None            |Library| None            |
+-------+-----------------+------+-----------------+-------+----------+------+
|HISTORY                                           |    Programmer    | Date |
+--------------------------------------------------+------------------+------+
| Turbo C V2.0 version                             | J.L. Bezemer     |191094|
| DJGPP V2.72 version                              | J.L. Bezemer     |220797|
| Turbo C++ for Windows version                    | J.L. Bezemer     |131199|
| Linux V2.2.10 version                            | J.L. Bezemer     |190600|
+--------------------------------------------------+------------------+------+
|MODIFICATION LOG                                  |    Programmer    | Date |
+--------------------------------------------------+------------------+------+
| Added code for larger model executables          | J.L. Bezemer     |251094|
| Changed program to 4tH toolkit V1.1              | J.L. Bezemer     |030395|
| Changed program to 4tH toolkit V1.2              | J.L. Bezemer     |180395|
| Some minor changes, dump_4th() to dumps stdout   | J.L. Bezemer     |210395|
| Fixed bug using NULL pointer by dump_4th()       | J.L. Bezemer     |070495|
| Changed program to 4tH toolkit V2.0              | J.L. Bezemer     |200495|
| Added additional memory msgs and output file     | J.L. Bezemer     |070995|
| Added more elaborate scheme for memory msgs      | J.L. Bezemer     |080995|
| Added support for EXPECT infile                  | J.L. Bezemer     |140995|
| Added support for FILE commands                  | J.L. Bezemer     |180995|
| Changed program to fit 4th V2.8a                 | J.L. Bezemer     |080296|
| Added support for cell                           | J.L. Bezemer     |100296|
| Added support for Hcode                          | J.L. Bezemer     |120296|
| Added dump_4th() code when error                 | J.L. Bezemer     |280296|
| Fixed bug in error representation                | J.L. Bezemer     |050396|
| Redesigned program completely                    | J.L. Bezemer     |250596|
| Redesigned program for new Hcode format          | J.L. Bezemer     |021096|
| Compacted code a little                          | J.L. Bezemer     |071096|
| Rewrite from scratch                             | J.L. Bezemer     |210797|
| Added ARGS and ARGN support; removed <limits.h>  | J.L. Bezemer     |250797|
| Moved exec_4th() to end (high chance of errors)  | J.L. Bezemer     |270797|
| Added 'verbose' option and Msg4tH()              | J.L. Bezemer     |310797|
| Removed EasyC syntax                             | J.L. Bezemer     |150198|
| Updated version info                             | J.L. Bezemer     |180298|
| Added C source generation                        | J.L. Bezemer     |311099|
| Redesigned main() and added Load4tH(), etc.      | J.L. Bezemer     |011199|
| Removed Version4th in Execute4tH()               | J.L. Bezemer     |011199|
| Changed some constants, macro's and Msg4tH()     | J.L. Bezemer     |021199|
| Added HGenerate4tH() and Edit4tH()               | J.L. Bezemer     |021199|
| Removed some checks from Edit4tH()               | J.L. Bezemer     |031199|
| Changed CGenerate4tH() due to library change     | J.L. Bezemer     |031199|
| Changed HGenerate4tH() due to library change     | J.L. Bezemer     |041199|
| Added an interactive mode and Menu4tH()          | J.L. Bezemer     |111199|
| Changed layout of menu to Turbo Pascal style     | J.L. Bezemer     |131199|
| Fixed free_4th() bugs; added Turbo C directives  | J.L. Bezemer     |131199|
| Changed main() and GetOptions() for Windows      | J.L. Bezemer     |151199|
| Changed fload() to open_4th(); library change    | J.L. Bezemer     |151199|
| Added smart decompile to Decompile4tH()          | J.L. Bezemer     |161199|
| Added Discard4tH()                               | J.L. Bezemer     |161199|
| Removed Discard4tH(); changed Abort4tH()         | J.L. Bezemer     |241199|
| Changed Menu4tH(), Edit4tH() and Decompile4tH()  | J.L. Bezemer     |241199|
| Added new macros to minimize recompilations      | J.L. Bezemer     |241199|
| Added 'quiet' option and renamed editor includes | J.L. Bezemer     |170600|
| Discarded GetOptions(); rewrote main()           | J.L. Bezemer     |190600|
| Fixed Linux warnings (no need; code is OK)       | J.L. Bezemer     |190600|
| Fixed bug: object dropped on screenfile command  | J.L. Bezemer     |210600|
| Fixed tiny command compat. bug in HGenerate4tH() | J.L. Bezemer     |210600|
| Fixed bug in Msg4tH() and CGenerate4tH()         | J.L. Bezemer     |040802|
| Added 'Arguments' in Menu4tH()                   | J.L. Bezemer     |200103|
| Added ZAURUS code                                | J.L. Bezemer     |160303|
| Added support for binfmt_misc                    | J.L. Bezemer     |050403|
| Changed Edit4tH() due to library change          | J.L. Bezemer     |060603|
| Added 'volatile' keyword on Menu4tH()            | J.L. Bezemer     |051103|
| Cleaned up comments                              | J.L. Bezemer     |131103|
| Changed copyright message                        | J.L. Bezemer     |090404|
| Changed copyright message                        | J.L. Bezemer     |140704|
| Overflow in Menu4tH() fixed                      | J.L. Bezemer     |110804|
| Removed #elif to accomodate PellesC              | J.L. Bezemer     |221105|
| Removed HGenerate4tH()                           | J.L. Bezemer     |111207|
| Changed copyright message                        | J.L. Bezemer     |060609|
| Removed extra linefeed from copyright message    | J.L. Bezemer     |241009|
| Replaced free_4th() with DROPOBJECT              | J.L. Bezemer     |201109|
| Applied Coherent patch WRITETEXT                 | J.L. Bezemer     |290312|
| Fixed fgets() warning in PromptFor()             | J.L. Bezemer     |271012|
+--------------------------------------------------+------------------+------+
|REMARKS                                           |    Programmer    | Date |
+--------------------------------------------------+------------------+------+
| Demonstration for 4th toolkit                    | J.L. Bezemer     |191094|
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
*/

#ifdef USRLIB4TH
#include <4th.h>
#include <cmds_4th.h>
#else
#include "4th.h"
#include "cmds_4th.h"
#endif

#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>
#include <setjmp.h>
#include <string.h>
                                       /* this is the menu */
#ifdef ZAURUS
#define Menu "\n\
(S)creen file: %s\n\
(O)bject file: %s\n\
\n\
(C)ompile   (R)un   (E)dit\n\
(G)enerate  (B)uild (Q)uit\n\
(D)ecompile (A)rguments\n\
\n\
>"
#else
#define Menu "\n\
(S)creen file: %s\n\
(O)bject file: %s\n\
\n\
(E)dit  (C)ompile   (R)un    (A)rguments\n\
\n\
(Q)uit  (G)enerate  (B)uild  (D)ecompile\n\
\n\
>"
#endif

#define REENTRY 1
#define MAXDUMP 9                      /* no. lines on decompile */
#define MAXARGS 16                     /* number of arguments allowed */

#define MBADCMD 0                      /* Bad selection of commands message */
#define M4THERR 1                      /* 4tH error message */
#define MCANNOT 2                      /* Cannot do message */
#define MRESULT 3                      /* Result message */
#define MNOCODE 4                      /* No object code */
#define MCRIGHT 5                      /* Copyright message */
                                       /* Commands, executed in this order */
#define CMD_SHOW   1
#define CMD_MENU   2
#define CMD_EDIT   4
#define CMD_COMP   8
#define CMD_LOAD  16
#define CMD_CGEN  32
#define CMD_SAVE  64
#define CMD_DUMP 128
#define CMD_EXEC 256
#define CMD_VERB 512
                                       /* these macros handle the commands */
#define IsSelected(a)   ((Cmds)&(a))
#define Enable(a)       ((Cmds)|=(a))
#define Disable(a)      ((Cmds)&=(~(a)))
                                       /* these macros check/flag compiles */
#define ISCOMPILED   (Object?0:CMD_COMP)
#define DROPOBJECT   {free_4th(Object);Object=NULL;}
                                       /* load editor bytecode */
#ifdef __TURBOC__
#include "teditor.h"
#else
#ifdef ZAURUS
#include "zeditor.h"
#else
#include "editor.h"
#endif
#endif

#ifdef ARCHAIC
#define WRITETEXT "w"
#else
#define WRITETEXT "wt"
#endif

short    Cmds     = 0;                 /* issued commands */
Hcode   *Object   = NULL;              /* compiled program */
char     InterActive = FALSE;          /* true when using the menu */
jmp_buf  Shell;                        /* buffer for shell error-return */
                                       /* prototype for ExecuteCommands() */
void ExecuteCommands __PROTO((char *OutName, int argn, char **args));


/*
This routine terminates the program unless in interactive mode.
*/

#ifndef ARCHAIC
  void Abort4tH (void)
#else
  void Abort4tH ()
#endif

{
  if (InterActive) longjmp (Shell, REENTRY);
  else
     {
       DROPOBJECT;
       exit (EXIT_FAILURE);
     }
}


/*
This routine handles all error messages of 4tH. It is called with the number
of the error message selected (MsgNo) and all arguments for the error message
itself. A switch statement handles the error itself, selecting a specific
action for a specific error message. If none is required (informative) it only
contains 'break'. Otherwise a call to Abort4tH() follows.
*/

#ifndef ARCHAIC
  void ErrMsg (int MsgNo, ...)
#else
  void ErrMsg (MsgNo) int MsgNo;
#endif

{                                      /* array with error messages */
  static char *Msg [] =
  {
    "%s\tInvalid combination of commands\n",
    "%s\tWord %u: %s\n",
    "%s\tCannot %s file \'%s\'\n",
    "%s\tResult: %ld\n",
    "%s\tNo object compiled or loaded!\n",
    "4tH library v%x.%x - Copyright 1994,2012 J.L. Bezemer\n"
  };

  va_list ErrArgs;

  va_start (ErrArgs, MsgNo);           /* print error message */
  vfprintf (stderr, Msg [MsgNo], ErrArgs);
  va_end (ErrArgs);

  fflush (stderr);                     /* prevent garbled output */

  switch (MsgNo)                       /* select action for message */
    {
      case (M4THERR): if (Object->ErrNo) Abort4tH (); break;
      case (MCRIGHT):
      case (MRESULT): break;           /* no action required */
      default:        Abort4tH (); break;
    }
}


/*
This routine issues a 4tH message if an error occured or verbose is on. Note
that Msg4tH() can only work when an Hcode object is available!
*/

#ifndef ARCHAIC
  void Msg4tH (char* Stage)
#else
  void Msg4tH (Stage) char* Stage;
#endif

{
  if (! Object) ErrMsg (MNOCODE, Stage);
  else
    if ((Object->ErrNo) || (IsSelected (CMD_VERB)))
       ErrMsg (M4THERR, Stage, Object->ErrLine, errs_4th [Object->ErrNo]);
}


/*
This routine prints a prompt and allows a string of input. Used in interactive
mode to input commands, filenames, etc.
*/

#ifndef ARCHAIC
  void PromptFor (char *Prompt, char Entry [], int Size, ...)
#else
  void PromptFor (Prompt, Entry, Size) char *Prompt; char Entry []; int Size;
#endif

{
  va_list Args;

  va_start (Args, Size);
  vfprintf (stdout, Prompt, Args);     /* print the prompt */
  va_end (Args);

  (void) fgets (Entry, Size, stdin);   /* get input */
  Entry [strlen (Entry) - 1] = '\0';   /* delete the newline character */
}


/*
This routine interacts with the user in interactive mode. It basically
prints a prompt, then interfaces with the usual routine.
*/

#ifndef ARCHAIC
  void Menu4tH (char *InName, char *OutName)
#else
  void Menu4tH (InName, OutName) char *InName; char *OutName;
#endif

{
  char  Command [16];                  /* holds the command line */
  char  CmdLine [128];                 /* holds the arguments */
  char  SourceN [128] = "new.scr";     /* holds the source file name */
  char  TargetN [128] = "out";         /* holds the target file name */
  char *(Args [MAXARGS]);              /* interface to ExecuteCommands() */
  char  space;                         /* boolean for scanning arguments */
  volatile int Argn;                   /* number of arguments */
  int   x;                             /* simple counter */

  Args [0] = SourceN;                  /* assign first argument to CmdLine */
  Args [1] = NULL;                     /* terminate arguments */
  Argn = 1;                            /* initially we pass one argument */
  InterActive = TRUE;                  /* signal we're in interactive mode */
                                       /* copy the filenames, if any */
  if ((InName)  && (strlen (InName)  < sizeof (SourceN)))
     strcpy (SourceN, InName);         /* and check for overflows */

  if ((OutName) && (strlen (OutName) < sizeof (TargetN)))
     strcpy (TargetN, OutName);

  setjmp (Shell);                      /* Return from error */

  for (;;)
    {
      Cmds = 0;                        /* reset all commands */
      PromptFor (Menu, Command, sizeof (Command), Args [0], TargetN);
                                       /* now interpret the command string */
      switch (tolower (Command [0]))
      {
        case ('r'): Enable (CMD_EXEC | ISCOMPILED); break;
        case ('b'): Enable (CMD_SAVE | ISCOMPILED); break;
        case ('g'): Enable (CMD_CGEN | ISCOMPILED); break;
        case ('d'): Enable (CMD_DUMP | ISCOMPILED); break;
        case ('e'): DROPOBJECT; Enable (CMD_EDIT);  break;
        case ('c'): DROPOBJECT; Enable (CMD_COMP);  break;
        case ('s'): DROPOBJECT; PromptFor ("Screen file name: ", SourceN,
                               sizeof (SourceN)); break;
        case ('o'): PromptFor ("Object file name: ", TargetN,
                               sizeof (TargetN)); break;
        case ('a'): PromptFor ("Arguments: ", CmdLine, sizeof (CmdLine));
                    for (space = TRUE, Argn = 1, x = 0;
                        (Argn < MAXARGS - 1) && (CmdLine [x] != '\0'); x++)
                      {                /* max 14 args, scan till end of cmd */
                        if (CmdLine [x] == ' ')
                           {           /* if space, terminate and signal */
                             CmdLine [x] = '\0';
                             space = TRUE;
                           }
                        else           /* if it is a character, test for */
                           {           /* previous space and assign */
                             if (space == TRUE) Args [Argn++] = CmdLine + x;
                             space = FALSE;
                           }           /* signal this was not a space */
                      }                /* terminate argument list */
                    Args [Argn] = NULL; break;
        case ('q'): return;            /* Cmds has been reset at this point */
      }                                /* execute the commands */

      ExecuteCommands (TargetN, Argn, Args);
    }                                  /* free any objects */
}


/*
This routine loads the editor and passes the filename as an argument.
Since the edited source needs compilation the compiler is turned on when
further processing is required. 'args[0]' holds the filename, which will
later be passed to the compiler.
*/

#ifndef ARCHAIC
  void Edit4tH (int argn, char **args)
#else
  void Edit4tH (argn, args) int argn; char **args;
#endif

{
  if (IsSelected (CMD_LOAD))           /* check for command conflicts */
     ErrMsg (MBADCMD, "Exiting;");
  else if ((Object = fetch_4th (EmbeddedHX)) == NULL)
          ErrMsg (MCANNOT, "Exiting;", "edit", args [0]);
       else
          {
            fflush (stderr);           /* prevent garbled output */
            exec_4th (Object, argn, args, 0);
            fflush (stdout);           /* execute the editor */

            Msg4tH ("Editing;");       /* show any messages */
            DROPOBJECT;                /* unload editor */
                                       /* and force recompilation */
            if (IsSelected (CMD_CGEN | CMD_SAVE | CMD_DUMP | CMD_EXEC))
               Enable (CMD_COMP);      /* if any further commands */
          }
}


/*
This routine simply decompiles an object. It flushes stderr and stdout since
that may cause garbled output on some platforms.
*/

#ifndef ARCHAIC
  void Decompile4tH (void)
#else
  void Decompile4tH ()
#endif

{
  int a = 0;                           /* begin dumping from here */
  int b = -1;                          /* do a full listing */

  if (Object)                          /* do we have an object */
     if (Object->ErrNo)                /* did we have an error */
        {                              /* adjust the range */
          b = (Object->ErrLine < MAXDUMP ? MAXDUMP : Object->ErrLine + 1);
          a = (b < Object->CodeSiz ? b : Object->CodeSiz) - MAXDUMP;
        }                              /* doesn't have to be exact! */
                                       /* dump_4th() handles clipping */
  dump_4th (Object, stdout, a, b);     /* decompile object to stdout */
  fflush (stdout);                     /* flush any output */
}


/*
This routine compiles an object.
*/

#ifndef ARCHAIC
  void Compile4tH (char *InName)
#else
  void Compile4tH (InName) char *InName;
#endif

{
  char  *Source;                       /* source program */

  if (IsSelected (CMD_LOAD))           /* check for command conflicts */
     ErrMsg (MBADCMD, "Exiting;");
  else
     {                                 /* now load the source */
       if ((Source = open_4th (InName)) == NULL)
          ErrMsg (MCANNOT, "Exiting;", "load", InName);
       else                            /* ok, now compile it */
          {                            /* probably out of memory */
            if ((Object = comp_4th (Source)) == NULL)
               ErrMsg (MCANNOT, "Exiting;", "compile", InName);
            else if ((! Object->ErrNo) || (! IsSelected (CMD_DUMP)))
               Msg4tH ("Compiling;");  /* show status if not decompiling */
          }
     }
}


/*
This routine loads an HX file.
*/

#ifndef ARCHAIC
  void Load4tH (char *InName)
#else
  void Load4tH (InName) char *InName;
#endif

{
  if (IsSelected (CMD_COMP))
     ErrMsg (MBADCMD, "Exiting;");
  else
     {
       if ((Object = load_4th (InName)) == NULL)
          ErrMsg (MCANNOT, "Exiting;", "load", InName);
       else                            /* probably out of memory */
          Msg4tH ("Loading;");
     }                                 /* show status of loading */
}


/*
This routine saves an HX file.
*/

#ifndef ARCHAIC
  void Save4tH (char *OutName)
#else
  void Save4tH (OutName) char *OutName;
#endif

{
  if (IsSelected (CMD_CGEN))
     ErrMsg (MBADCMD, "Exiting;");
  else
     {                                 /* assign default name */
       if (! OutName) OutName = "out.hx";
       save_4th (Object, OutName);
       Msg4tH ("Saving;\t");
     }                                 /* save file and give status */
}


/*
This routine generates a standalone C source.
*/

#ifndef ARCHAIC
  void CGenerate4tH (char *OutName)
#else
  void CGenerate4tH (OutName) char *OutName;
#endif

{
  FILE  *CFp;                          /* C source output file */

  if (IsSelected (CMD_SAVE))           /* check for command conflicts */
     ErrMsg (MBADCMD, "Exiting;");
  else
     {                                 /* assign default name */
       if (! OutName) OutName = "out.c";
       if ((! Object) || ((CFp = fopen (OutName, WRITETEXT)) == NULL))
          ErrMsg (MCANNOT, "Exiting;", "open", OutName);
       else
          {
            cgen_4th (Object, CFp);
            Msg4tH ("Generating;");    /* generate file and give status */
            if (fclose (CFp)) ErrMsg (MCANNOT, "Exiting;", "close", OutName);
          }                            /* close the source file */
     }
}


/*
This routine executes an object. It flushes stderr and stdout since
that may cause garbled output on some platforms.
*/

#ifndef ARCHAIC
  void Execute4tH (int argn, char **args)
#else
  void Execute4tH (argn, args) int argn; char **args;
#endif

{
  cell   Result;                       /* holds the result from the program */

  fflush (stderr);                     /* prevent garbled output */
  Result = exec_4th (Object, argn, args, 0);
  fflush (stdout);                     /* execute the object */
  Msg4tH ("Executing;");
  if (Result != CELL_MIN) ErrMsg (MRESULT, "Executing;", Result);
}                                      /* show only significant results */


/*
This routine decodes the command string, which is issued on the command line.
The results are encoded into 'Cmds'. This ensures that the commands are
executed in the proper order.
*/

#ifndef ARCHAIC
  void DecodeCommands (char *CmdString)
#else
  void DecodeCommands (CmdString) char *CmdString;
#endif

{
  int x;                               /* simple counter */

  for (x = 0; CmdString [x]; x++)      /* now decode the command string */
      switch (tolower (CmdString [x]))
        {
          case ('q'): Disable (CMD_SHOW); break;
          case ('m'): Enable  (CMD_MENU); break;
          case ('v'): Enable  (CMD_VERB); break;
          case ('c'): Enable  (CMD_COMP); break;
          case ('e'): Enable  (CMD_EDIT); break;
          case ('l'): Enable  (CMD_LOAD); break;
          case ('d'): Enable  (CMD_DUMP); break;
          case ('s'): Enable  (CMD_SAVE); break;
          case ('x'): Enable  (CMD_EXEC); break;
          case ('g'): Enable  (CMD_CGEN); break;
        }
}


/*
This routine executes the decoded commands. The results are encoded into
'Cmds'. This ensures that the commands are executed in the proper order
and makes it easy to check for invalid combinations.
*/

#ifndef ARCHAIC
  void ExecuteCommands (char *OutName, int argn, char **args)
#else
  void ExecuteCommands (OutName, argn, args) char *OutName;
                        int argn; char **args;
#endif

{
  short x;                             /* simple counter */
                                       /* now execute the commands */
  for (x = CMD_SHOW; x < CMD_VERB; x <<= 1)
      switch (IsSelected (x))          /* in the proper order */
        {
          case (CMD_SHOW): ErrMsg (MCRIGHT, Version4th/256, Version4th%256);
                           break;
          case (CMD_MENU): Menu4tH      (args [0], OutName); break;
          case (CMD_EDIT): Edit4tH      (argn, args); break;
          case (CMD_COMP): Compile4tH   (args [0]);   break;
          case (CMD_LOAD): Load4tH      (args [0]);   break;
          case (CMD_CGEN): CGenerate4tH (OutName);    break;
          case (CMD_SAVE): Save4tH      (OutName);    break;
          case (CMD_DUMP): Decompile4tH ();           break;
          case (CMD_EXEC): Execute4tH   (argn, args); break;
        }
}


/*
This is the main program. It checks the arguments and decodes the command
string. After that the options are checked in a specific order and the
appropriate action is taken. This prevents double commands and an
inappropriate order of execution. The price is some flexibility.
*/


#ifndef ARCHAIC
  int main (int argc, char **argv)
#else
  int main (argc, argv) int argc; char **argv;
#endif

{
  char *OutName = NULL;                /* holds the output filename */
  int ShiftArgs = 1;                   /* shift arguments if Cmd string */
                                       /* how many arguments are there? */
  if ((argc == 2) || ((argv [0][strlen (argv [0]) - 1] == 'x') && (argc > 1)))
     Enable (CMD_LOAD | CMD_EXEC);     /* if a filename or 4thx called */
  else                                 /* execute .HX file */
     switch (argc)                     /* otherwise check args */
       {
         case (0) :                    /* start up the menu */
         case (1) : Enable (CMD_MENU | CMD_SHOW); break;
         case (3) : Enable (CMD_SHOW); DecodeCommands (argv [1]); ShiftArgs++;
                    break;             /* interpret the Cmd string */
         default  : Enable (CMD_SHOW); DecodeCommands (argv [1]); ShiftArgs++;
                    OutName = argv [argc - 1]; break;
       }                               /* outfile has been given? */

  ExecuteCommands (OutName, argc - ShiftArgs, argv + ShiftArgs);
  DROPOBJECT;                          /* discard the Hcode */
  return (EXIT_SUCCESS);               /* program terminated ok */
}
