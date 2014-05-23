/*
+-------+-----------------+------+-----------------+-------+-----------------+
|Program| PP4TH.C         |Module| None            |Library| None            |
+-------+-----------------+------+-----------------+-------+----------+------+
|HISTORY                                           |    Programmer    | Date |
+--------------------------------------------------+------------------+------+
| Linux V2.6.25 version                            | J.L. Bezemer     |030114|
| Coherent V4.2.10 version                         | J.L. Bezemer     |050114|
| Turbo C V2 version                               | J.L. Bezemer     |050114|
+--------------------------------------------------+------------------+------+
|MODIFICATION LOG                                  |    Programmer    | Date |
+--------------------------------------------------+------------------+------+
| Added MakeInFile() and AllocString()             | J.L. Bezemer     |040114|
| Added DIR4TH support for the preprocessor        | J.L. Bezemer     |040114|
| Cleanup layout and fixed minor BaseName() issues | J.L. Bezemer     |050114|
| Added small Coherent fix in MakePpName()         | J.L. Bezemer     |050114|
| Added small Turbo C fix in Prep4tH()             | J.L. Bezemer     |050114|
| Changed heap memory management, ExecuteCommands()| J.L. Bezemer     |060114|
| Small changes in Prep4tH() and ExecuteCommands() | J.L. Bezemer     |060114|
| Free memory on error in Abort4tH() by DEALLOC()  | J.L. Bezemer     |060114|
| Changed preprocessor extension to .4PI           | J.L. Bezemer     |100114|
| Changed MakePpName() and ReplaceExt()            | J.L. Bezemer     |100114|
| Removed superfluous parameter from Prep4tH()     | J.L. Bezemer     |110114|
| -D and -i enable preprocessor in DecodeOptions() | J.L. Bezemer     |190214|
+--------------------------------------------------+------------------+------+
|REMARKS                                           |    Programmer    | Date |
+--------------------------------------------------+------------------+------+
| Demonstration for 4th toolkit                    | J.L. Bezemer     |030114|
+--------------------------------------------------+------------------+------+

  Copyright (C) 2014 J.L. Bezemer

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
#include <string.h>

#ifdef UNIX
#include <unistd.h>
#endif

#define MAXDUMP 9                      /* no. lines on decompile */
#define LENEXT  4                      /* size of an extension */

#define M4THERR  0                     /* 4tH error message */
#define MCANNOT  1                     /* Cannot do message */
#define MRESULT  2                     /* Result message */
#define MNOCODE  3                     /* No object code */
#define MCRIGHT  4                     /* Copyright message */
#define MNOARGS  5                     /* Option requires argument */
#define MBADOPT  6                     /* Unknown option */
#define MBADCMD  7                     /* Bad selection of commands message */
#define MPP4ERR  8                     /* Preprocessor error */
#define MPP4OK   9                     /* Preprocessor error */
#define MNOMEM  10                     /* Out of memory */
#define MUSAGE  11                     /* Usage */
                                       /* Commands, executed in this order */
#define CMD_SHOW   1
#define CMD_PREP   2
#define CMD_COMP   4
#define CMD_WIPE   8
#define CMD_CGEN  16
#define CMD_SAVE  32
#define CMD_DUMP  64
#define CMD_EXEC 128
#define CMD_VERB 256

#ifdef NOUNLINK                        /* use ANSI equivalent instead */
#define unlink(a) remove(a)
#endif
                                       /* these macros handle the commands */
#define IsSelected(a)   ((Cmds)&(a))
#define AreSelected(a)  (((Cmds)&(a))==(a))
#define Enable(a)       ((Cmds)|=(a))
#define Disable(a)      ((Cmds)&=(~(a)))
                                       /* these macros check/flag compiles */
#define DROPOBJECT   {free_4th(Object);Object=NULL;}
#define DEALLOC(a)   {if((a)!=NULL){free((a));(a)=NULL;}}
                                       /* load editor bytecode */
#ifdef ARCHAIC
#define WRITETEXT "w"
#else
#define WRITETEXT "wt"
#endif

#include "pp4th.h"
                                       /* global variables */
char   **PArgs   = NULL;               /* preprocessor argv */
int      PArgn   = 0;                  /* preprocessor argc */
short    Cmds    = 0;                  /* issued commands */
int      optind  = 0;                  /* argv index after getopt() */
char    *optarg;                       /* argument pointer */
char    *PpFile  = NULL;               /* holds the temporary filename */
char    *OutFile = NULL;               /* holds the output filename */
char    *InFile  = NULL;               /* holds the input filename */
Hcode   *Object  = NULL;               /* compiled program */


#if defined (_WIN32) || defined (__TURBOC__) || defined (__DJGPP__) || defined (__OS2__) || defined (__MSDOS__)
#define DOSALIKE
#define ISDIR(a) (((a) == '/') || ((a) == '\\'))
#else
#define ISDIR(a) ((a) == '/')
#endif

/*
The situation around basename() is so messy that a custom function was
defined. Virtually every single platform has its own include files and
behavior. This one should work in most circumstances. If it doesn't, it
isn't my fault. Note it may return a NULL pointer or an empty string.
This function is derived from code in the public domain.
*/

#ifndef ARCHAIC
  char *BaseName (char *full_name)
#else
  char *BaseName (full_name) char *full_name;
#endif

{
  char* base;                          /* pointer to the basename */
                                       /* return a NULL pointer if NULL */
  if (full_name == NULL) return (NULL);
                                       /* we're dealing with some MS-like */
#ifdef DOSALIKE                        /* operating system */
  if (strlen (full_name) > 1)          /* discard drive information */
     if ((isalpha (full_name [0])) && (full_name [1] == ':'))
        full_name += 2;
#endif
                                       /* scan for last directory */
  for (base = full_name; *full_name; full_name++)
      if (ISDIR (*full_name)) base = full_name + 1;
                                       /* if match, set basename */
  return (base);                       /* return the basename */
}


/*
This routine terminates the program
*/

#ifndef ARCHAIC
  void Abort4tH (void)
#else
  void Abort4tH ()
#endif

{
  DEALLOC (PArgs); DEALLOC (PpFile); DROPOBJECT; exit (EXIT_FAILURE);
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
    "%s\tWord %u: %s\n",
    "%s\tCannot %s file \'%s\'\n",
    "%s\tResult: %ld\n",
    "%s\tNo object compiled or loaded!\n",
    "4tH library v%x.%x - Copyright 1994,2014 J.L. Bezemer\n",
    "%s\tOption -%c requires argument\n",
    "%s\tUnknown option -%c\n",
    "%s\tInvalid combination of commands\n",
    "%s\t%s\n",
    "%s\t%s\n",
    "%s\tOut of memory\n",
    "Usage: pp4th [-Vvicsgdxpk] [-D symbol] [-o outfile] infile [arguments]\n"
  };

  va_list ErrArgs;

  va_start (ErrArgs, MsgNo);           /* print error message */
  vfprintf (stderr, Msg [MsgNo], ErrArgs);
  va_end (ErrArgs);

  fflush (stderr);                     /* prevent garbled output */

  switch (MsgNo)                       /* select action for message */
    {
      case (M4THERR): if (Object->ErrNo) Abort4tH (); break;
      case (MPP4OK):                   /* only when verbose mode is set */
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
Allocate an array of argument pointers (like argv)
*/

#ifndef ARCHAIC
  char** AllocParms (int count)
#else
  char** AllocParms (count) int count;
#endif

{                                      /* allocate a bunch of char pointers */
  char **p = (char **) calloc (count, sizeof(char*));
                                       /* report if we're out of memory */
  if (p == NULL) ErrMsg (MNOMEM, "Exiting;");
  return (p);                          /* otherwise return the pointer */
}


/*
Allocate a string, including NULL terminator
*/

#ifndef ARCHAIC
  char* AllocString (int count)
#else
  char* AllocString (count) int count;
#endif

{                                      /* allocate a bunch of chars + NULL */
  char *p = (char *) calloc (count + 1, sizeof(char));
                                       /* report if we're out of memory */
  if (p == NULL) ErrMsg (MNOMEM, "Exiting;");
  return (p);                          /* otherwise return the pointer */
}


/*
Copy a string to the preprocessor filename
*/

#ifndef ARCHAIC
  char* CopyName (char *base)
#else
  char* CopyName (base) char *base;
#endif

{                                     /* reserve space for the extension */
  char *p = AllocString (strlen (base) + LENEXT);

  return (strcpy (p, base));          /* return the preprocessor target */
}


/*
Append an extension to the preprocessor filename
*/

#ifndef ARCHAIC
  char* AppendExt (char *base)
#else
  char* AppendExt (base) char *base;
#endif

{                                      /* just add .4th to this one */
  return (strcat (CopyName (base), ".4pi"));
}                                      /* since it has no extension */


/*
Replace an extension in the preprocessor filename by another
*/

#ifndef ARCHAIC
  char* ReplaceExt (char *base)
#else
  char* ReplaceExt (base) char *base;
#endif

{                                      /* we know it has an extension */
  char *p = CopyName (base);           /* now copy the name */
  char *q = strrchr (p, '.');          /* determine the place of extension */
                                       /* make sure it didn't drop off */
  if (q != NULL) *q = '\0';            /* now cut off the extension */

  return (strcat (p, ".4pi"));         /* note we reserved space for it */
}


/*
Generate a temporary preprocessor filename, just in case. If no viable
preprocessor filename has been given, assign a temporary filename. The
extension .4pp is recognized and triggers the preprocessor.
*/

#ifndef ARCHAIC
  char* MakePpName (char *infile)
#else
  char* MakePpName (infile) char *infile;
#endif

{
  char* ext;
  char* base = BaseName (infile);      /* get basename of the infile */
  char* TempName = "tempfile.4pi";     /* temporary file */
                                       /* can't determine a basename */
  if (base == NULL) return (CopyName (TempName));
  if (strlen (base) == 0) return (CopyName (TempName));
                                       /* so go for the tempfile */
  ext = strrchr (base, '.');           /* now get the extension */
                                       /* doesn't have an extension */
  if (ext == NULL) return (AppendExt (base));
                                       /* basename starts with dot */
  if ((strlen (base) == strlen (ext)) && (strlen (base) > 1) &&
     (base [1] != '.'))                /* but not a double dot */
     return (AppendExt (base));
                                       /* return a tempfile for the rest */
  if (strlen (base) == strlen (ext)) return (CopyName (TempName));

  if (strlen (ext) == 4)               /* check for special extensions */
     if ((ext [1] == '4') && (tolower (ext [2]) == 'p') &&
        (tolower (ext [3]) == 'p'))    /* turn on the preprocessor */
        Enable (CMD_PREP);             /* for that one */

  return (ReplaceExt (base));
}                                      /* replace all extensions with .4pi */


/*
Check if the infile can be read, take DIR4TH into consideration if needed
*/

#ifndef ARCHAIC
  char* MakeInFile (char *infile)
#else
  char* MakeInFile (infile) char *infile;
#endif

{
  FILE* Fp = fopen (infile, "r");      /* open file in read mode */
  char* path;                          /* contents of $DIR4TH */
  char* fullname;                      /* pointer to allocated string */
                                       /* abort if it doesn't open properly */
  if (Fp == NULL)                      /* if the file cannot be read */
     {                                 /* get the contents of DIR4TH */
       if ((path = getenv ("DIR4TH")) != NULL)
          {                            /* compose the full name */
            fullname = AllocString (strlen (path) + strlen (infile));
            strcat (strcpy (fullname, path), infile);
            Fp = fopen (fullname, "r");
            if (Fp != NULL)            /* now try  to open it again */
               {                       /* if it can be read */
                 fclose (Fp);          /* close the file right away */
                 return (fullname);    /* and return the full name */
               }
          }                            /* if DIR4TH is not set or */
                                       /* it can't be read, issue a message */
       ErrMsg (MCANNOT, "Exiting;", "open", infile); return (NULL);
     }
  else
     {
       fclose (Fp);                    /* close it right away */
       return (strcpy (AllocString (strlen (infile)), infile));
     }                                 /* give it something to free up */
}


/*
This routine loads the preprocessor and passes the arguments.
*/

#ifndef ARCHAIC
  void Prep4tH (void)
#else
  void Prep4tH ()
#endif

{
  static char *Msg [] =                /* the preprocessor messages */
  {
    "No errors",
    "Bad number",
    "Cannot open include file",
    "Cannot read include file",
    "Directive not allowed here",
    "Duplicate macro",
    "Include file nested too deep",
    "Internal error",
    "Macro space exhausted",
    "Missing string",
    "Seek failed",
    "String stack empty",
    "String stack full",
    "String stack not empty",
    "String too long",
    "Too many macros",
    "Undefined macro",
    "Unexpected end of file",
    "Unexpected macro",
    "Bytecode interface error"
  };

  int Result;                          /* holds the result from the program */

  if ((Object = fetch_4th (EmbeddedHX)) == NULL)
     ErrMsg (MCANNOT, "Exiting;", "preprocess", InFile);
  else
     {
       InFile = MakeInFile (InFile);   /* make sure we can read the file */
       PArgs [PArgn++] = InFile;       /* add it to the bytecode options */
                                       /* we don't want the bytecode msg */
       if ((IsSelected (CMD_COMP)) || (OutFile == NULL))
          PArgs [PArgn++] = PpFile;    /* if we need compiling or we don't */
       else PArgs [PArgn++] = OutFile; /* have an outfile specified */
                                       /* then use the preprocessed file */
       PArgs [PArgn] = NULL;           /* terminate the argv[][] array */
                                       /* error code returned by Result */
       fflush (stderr);                /* prevent garbled output */
       Result = (int) exec_4th (Object, PArgn, PArgs, 0);
       fflush (stdout);                /* execute the preprocessor */
                                       /* system errors always go first */
       free (InFile); InFile = PpFile; /* free memory, use prep file */
                                       /* since compilation MAY BE next */
       if (Object->ErrNo) Msg4tH ("Preprocessing;");
       else if (Result)
                ErrMsg (MPP4ERR, "Preprocessing;", Msg [Result]);
            else if (IsSelected (CMD_VERB))
                    ErrMsg (MPP4OK, "Preprocessing;", Msg [Result]);
                                       /* only report in verbose mode */
       DROPOBJECT;                     /* unload preprocessor */
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
  void Compile4tH (void)
#else
  void Compile4tH ()
#endif

{
  char  *Source;                       /* source program */

  if ((Source = open_4th (InFile)) == NULL)
     ErrMsg (MCANNOT, "Exiting;", "load", InFile);
  else                                 /* ok, now compile it */
     {                                 /* probably out of memory */
       if ((Object = comp_4th (Source)) == NULL)
          ErrMsg (MCANNOT, "Exiting;", "compile", InFile);
       else if ((! Object->ErrNo) || (! IsSelected (CMD_DUMP)))
               Msg4tH ("Compiling;");  /* show status if not decompiling */
     }
}


/*
This routine saves an HX file.
*/

#ifndef ARCHAIC
  void Save4tH (void)
#else
  void Save4tH ()
#endif

{
  if (IsSelected (CMD_CGEN))
     ErrMsg (MBADCMD, "Exiting;");
  else
     {                                 /* assign default name */
       if (! OutFile) OutFile = "out.hx";
       save_4th (Object, OutFile);
       Msg4tH ("Saving;\t");
     }                                 /* save file and give status */
}


/*
This routine generates a standalone C source.
*/

#ifndef ARCHAIC
  void CGenerate4tH (void)
#else
  void CGenerate4tH ()
#endif

{
  FILE  *CFp;                          /* C source output file */

  if (IsSelected (CMD_SAVE))           /* check for command conflicts */
     ErrMsg (MBADCMD, "Exiting;");
  else
     {                                 /* assign default name */
       if (! OutFile) OutFile = "out.c";
       if ((! Object) || ((CFp = fopen (OutFile, WRITETEXT)) == NULL))
          ErrMsg (MCANNOT, "Exiting;", "open", OutFile);
       else
          {
            cgen_4th (Object, CFp);
            Msg4tH ("Generating;");    /* generate file and give status */
            if (fclose (CFp)) ErrMsg (MCANNOT, "Exiting;", "close", OutFile);
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
This is a version of the public domain getopt() implementation by Henry
Spencer originally posted to 'net.sources'. This function is in the public
domain.
*/

#ifndef ARCHAIC
  int GetOpt (int argc, char **argv, char *optstring)
#else
  int GetOpt (argc, argv, optstring) int argc; char **argv; char *optstring;
#endif

{
  char c;                              /* character to return */
  char *place;                         /* location in optstring */

  static char *scan = NULL;            /* scan pointer */

  optarg = NULL;                       /* reset argument pointer */
                                       /* if startup */
  if ((scan == NULL) || (*scan == '\0'))
     {                                 /* skip program name */
       if (optind == 0) optind++;
                                       /* return after all options */
       if ((optind >= argc) || (argv [optind][0] != '-') ||
          (argv [optind][1] == '\0'))
          return (-1);
                                       /* return on -- option */
       if ((argv [optind][1] == '-') && (argv [optind][2] == '\0'))
          {
            optind++;                  /* go to the next option */
            return (-1);               /* and signal we're done */
          }

       scan = argv [optind] + 1;       /* begin scanning after the '-' */
       optind++;                       /* go to the next argument */
     }

  c = *scan++;                         /* now go looking for the option */
  place = strchr (optstring, c);       /* in the option string */

  if ((! place) || (c == ':'))         /* if we didn't find it */
     {                                 /* a colon is not a valid option */
       ErrMsg (MBADOPT, "Parsing;", c); return ((int) '?');
     }                                 /* issue an error message */

  place++;                             /* see if the option needs argument */

  if (*place == ':')                   /* if an argument is required */
     {
       if (*scan != '\0')              /* is it part of the option */
          {
            optarg = scan;             /* if so, assign it */
            scan = NULL;
          }
       else if (optind < argc)         /* if we're not at the last option */
               {                       /* it is the entire next option */
                 optarg = argv [optind];
                 optind++;             /* go to the next option */
               }
            else                       /* ok, we're missing an option */
               {                       /* so issue an error message */
                 ErrMsg (MNOARGS, "Parsing;", c); return ((int) ':');
               }
     }

  return ((int) c);                    /* finally, we found the option */
}


/*
This routine decodes the command string, which is issued on the command line.
The results are encoded into 'Cmds'. This ensures that the commands are
executed in the proper order.
*/

#ifndef ARCHAIC
  void DecodeOptions (int Argc, char **Argv)
#else
  void DecodeOptions (Argc, Argv) int Argc; char **Argv;
#endif

{
  int c;                               /* option character */

  PArgs = AllocParms (Argc * 2);       /* reserve space for -D options */
  PArgs [PArgn++] = Argv [0];          /* pass program name to preprocessor */

  while ((c = GetOpt (Argc, Argv, "VvpkicdsxgD:o:")) != -1)
    switch (c)
      {
        case ('V'): Enable (CMD_SHOW); break;
        case ('v'): Enable (CMD_VERB); break;
        case ('p'): Enable (CMD_PREP); break;
        case ('k'): Disable (CMD_WIPE); break;
        case ('i'): Enable (CMD_PREP); PArgs [PArgn++] = "-v"; break;
        case ('D'): Enable (CMD_PREP); PArgs [PArgn++] = "-D";
                    PArgs [PArgn++] = optarg; break;
        case ('o'): OutFile = optarg; break;
        case ('c'): Enable (CMD_COMP); break;
        case ('d'): Enable (CMD_DUMP|CMD_COMP); break;
        case ('s'): Enable (CMD_SAVE|CMD_COMP); break;
        case ('x'): Enable (CMD_EXEC|CMD_COMP); break;
        case ('g'): Enable (CMD_CGEN|CMD_COMP); break;
      }
}


/*
This routine executes the decoded commands. The results are encoded into
'Cmds'. This ensures that the commands are executed in the proper order
and makes it easy to check for invalid combinations.
*/

#ifndef ARCHAIC
  void ExecuteCommands (int CArgn, char **CArgs)
#else
  void ExecuteCommands (CArgn, CArgs) int CArgn; char **CArgs;
#endif

{
  short x;                             /* simple counter */
                                       /* there is nothing to do! */
  if (! IsSelected (CMD_PREP|CMD_COMP)) Enable (CMD_COMP|CMD_VERB);
                                       /* now execute the commands */
  for (x = CMD_SHOW; x < CMD_VERB; x <<= 1)
      {
        switch (IsSelected (x))        /* in the proper order */
          {
            case (CMD_PREP): Prep4tH      ();             break;
            case (CMD_COMP): Compile4tH   ();             break;
            case (CMD_WIPE): if (AreSelected (CMD_PREP|CMD_COMP))
                                 unlink (PpFile);
                             break;
            case (CMD_CGEN): CGenerate4tH ();             break;
            case (CMD_SAVE): Save4tH      ();             break;
            case (CMD_DUMP): Decompile4tH ();             break;
            case (CMD_EXEC): Execute4tH   (CArgn, CArgs); break;
          }

        switch (x)                     /* this is executed unconditionally */
          {                            /* free up memory after each stage */
            case (CMD_PREP): DEALLOC (PArgs);  break;
            case (CMD_WIPE): DEALLOC (PpFile); break;
          }
      }
}


/*
This is the main program. It checks the arguments and the options are checked.
Then the appropriate actions are taken. This prevents double commands and an
inappropriate order of execution. The price is some flexibility.
*/

#ifndef ARCHAIC
  int main (int argc, char **argv)
#else
  int main (argc, argv) int argc; char **argv;
#endif

{
  Enable (CMD_WIPE);                   /* delete temporary file */
  DecodeOptions (argc, argv);          /* now decode the options */

  if (optind < argc) InFile = argv [optind];
  else if (IsSelected (CMD_SHOW))      /* just show the version */
          ErrMsg (MCRIGHT, Version4th/256, Version4th%256);
       else ErrMsg (MUSAGE);           /* else show usage */
                                       /* we're pointing at the input file */
  PpFile = MakePpName (InFile);        /* now get the temporary filename */
  ExecuteCommands (argc - optind, argv + optind);
                                       /* we're ready to rock 'n roll */
  DROPOBJECT;                          /* deallocate any objects */
  return (EXIT_SUCCESS);               /* program terminated ok */
}
