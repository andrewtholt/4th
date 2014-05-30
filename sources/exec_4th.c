/*
   +-------+-----------------+------+-----------------+-------+-----------------+
   |Program| EXEC_4TH.C      |Header| 4TH.H           |Library| 4TH             |
   +-------+-----------------+------+-----------------+-------+----------+------+
   |HISTORY                                           |    Programmer    | Date |
   +--------------------------------------------------+------------------+------+
   | Turbo C V2.0 version                             | J.L. Bezemer     |181094|
   | DPX/2 340 version                                | J.L. Bezemer     |181094|
   | Coherent V4.2 version                            | J.L. Bezemer     |201094|
   | DJGPP V2.72 version                              | J.L. Bezemer     |230597|
   | Linux 2.2.10 version                             | J.L. Bezemer     |170600|
   +--------------------------------------------------+------------------+------+
   |MODIFICATION LOG                                  |    Programmer    | Date |
   +--------------------------------------------------+------------------+------+
   | Added /MOD, * /, * /MOD, I', J, FAST, SLOW       | J.L. Bezemer     |191094|
   | Removed Flags, changed NOP to NOOP               | J.L. Bezemer     |191094|
   | Added M4UNKKEY message, .R, VARIABLE, V0@, USER@ | J.L. Bezemer     |201094|
   | Added STACK@, LIMIT@, BASE@, SP@, RP@            | J.L. Bezemer     |201094|
   | Added ABORT, EXIT, EXECUTE, TICK, C@, WAIT       | J.L. Bezemer     |241094|
   | Changed allocation of RStack, Stack, Vars        | J.L. Bezemer     |241094|
   | Added check on I/O, /. and /.R                   | J.L. Bezemer     |271094|
   | Added randomizer, RANDOM and TIME                | J.L. Bezemer     |161194|
   | Optimized +LOOP a little; fixed LEAVE bug        | J.L. Bezemer     |140395|
   | Optimized +LOOP a little more                    | J.L. Bezemer     |150395|
   | Fixed bug: ErrNo4th returns wrong errorcode      | J.L. Bezemer     |160395|
   | Changed , into C, and removed V0@                | J.L. Bezemer     |180395|
   | Switched LIMIT@ and USER@ commands               | J.L. Bezemer     |180395|
   | Merged Stack and RStack                          | J.L. Bezemer     |180395|
   | Fixed bug in ABORT                               | J.L. Bezemer     |210395|
   | Rearranged commands to optimize performance      | J.L. Bezemer     |210395|
   | Changed LIMIT@ to VARS, USER@ to USER, C, to ,   | J.L. Bezemer     |310395|
   | Changed STACK@ to STACK; added C,                | J.L. Bezemer     |310395|
   | Produced first interpreter of 4tH V2.0           | J.L. Bezemer     |200495|
   | Redesigned allocation of variables               | J.L. Bezemer     |240495|
   | Removed STACK and VALUE                          | J.L. Bezemer     |240495|
   | Reduced field in .R and /.R to max. 31 positions | J.L. Bezemer     |250495|
   | Removed obsolete check reading in values         | J.L. Bezemer     |250495|
   | Made +LOOP Forth-compatible again                | J.L. Bezemer     |280495|
   | Removed INPUT, added string words                | J.L. Bezemer     |280495|
   | Added INRSET, changed PAD to FORMAT on some words| J.L. Bezemer     |290495|
   | Increased field in .R and /.R to max. 63 pos.    | J.L. Bezemer     |300495|
   | Changed CONSTANT to LITERAL                      | J.L. Bezemer     |300495|
   | Added #, #S, <#, #>, HOLD & SIGN; removed /., /.R| J.L. Bezemer     |010595|
   | Changed ,@; added COPY                           | J.L. Bezemer     |020595|
   | Added sharpS(), sign(), lsharp(), type(), dotR() | J.L. Bezemer     |050995|
   | Removed dot(), changed emit(); removed BASEFCH   | J.L. Bezemer     |050995|
   | All I/O passes through emit(); added *Base       | J.L. Bezemer     |050995|
   | Made code more solid; added M4BADRDX messages    | J.L. Bezemer     |060995|
   | Fixed bug in dotR() and RSHARP code              | J.L. Bezemer     |060995|
   | Changed ,@ to '@; set radix limits correctly     | J.L. Bezemer     |060995|
   | Removed LEFT, RIGHT, !IN; added SHIFT and *In    | J.L. Bezemer     |110995|
   | Rewrote TEXT completely                          | J.L. Bezemer     |120995|
   | Fixed tiny bugs: init >IN, loading extern vars   | J.L. Bezemer     |130995|
   | Added EXPECT command                             | J.L. Bezemer     |140995|
   | Added expect(), FILE>, TTY>, DevIn               | J.L. Bezemer     |150995|
   | Added FILE* to expect(); QUERY reads from TTY    | J.L. Bezemer     |160995|
   | Added INFILE and OUTFILE                         | J.L. Bezemer     |180995|
   | Fixed small bug in TEXT (incrementing >IN)       | J.L. Bezemer     |200995|
   | Updated errors                                   | J.L. Bezemer     |220995|
   | Changed EXPECT to ACCEPT, TEXT to WORD           | J.L. Bezemer     |080296|
   | Added LOOP; removed conditionals                 | J.L. Bezemer     |080296|
   | Changed WORD, NUMBER and PRINT                   | J.L. Bezemer     |080296|
   | Removed RETURN                                   | J.L. Bezemer     |090296|
   | Added cell support; changed COPY; added NE0      | J.L. Bezemer     |100296|
   | Added Hcode support                              | J.L. Bezemer     |120296|
   | Added HI and support for allocation              | J.L. Bezemer     |140296|
   | Added extra check to NUMBER                      | J.L. Bezemer     |160296|
   | Added TO and VALUE                               | J.L. Bezemer     |240296|
   | Changed NOT4 to INVERT                           | J.L. Bezemer     |040396|
   | Removed LINE; changed VARS to LAST, USER to FIRST| J.L. Bezemer     |050396|
   | Added return-value to pop() and removed argument | J.L. Bezemer     |210496|
| Cleaned up code and added comment                | J.L. Bezemer     |220496|
| Changed store(), fetch(), sharp()                | J.L. Bezemer     |220496|
| Added additional optimizations in pop() calls    | J.L. Bezemer     |220496|
| Added some additional casts                      | J.L. Bezemer     |230496|
| Removed some casts                               | J.L. Bezemer     |060596|
| Rewrote to accomodate new Hcode format           | J.L. Bezemer     |021096|
| Added RSP and SP                                 | J.L. Bezemer     |041096|
| Renamed TICKFCH to FETCHPRM ('@ changed to @')   | J.L. Bezemer     |101096|
| Moved RSP and SP to headerfile                   | J.L. Bezemer     |201196|
| Removed ABORT, added SP! and RP!                 | J.L. Bezemer     |201196|
| Replaced M4UNKTOK by M4BADOBJ; added F_F and F_T | J.L. Bezemer     |031296|
| Added CLOSEIO                                    | J.L. Bezemer     |061296|
| Removed TTY>, >TTY, FILE>, >FILE, INFILE, OUTFILE| J.L. Bezemer     |280297|
| Added TTY, FILE, OPEN, CLOSE; removed CLOSEIO    | J.L. Bezemer     |280297|
| Optimized TRAILING a little                      | J.L. Bezemer     |150397|
| Made In local, added RESULT variable             | J.L. Bezemer     |100497|
| Added )                                          | J.L. Bezemer     |110497|
| Added throw(), THROW and HANDLER variable        | J.L. Bezemer     |170497|
| Added PassThru to throw()                        | J.L. Bezemer     |180497|
| Added M4THROW                                    | J.L. Bezemer     |190497|
| Optimized throw() a little                       | J.L. Bezemer     |200497|
| Changed return of rpop() on error                | J.L. Bezemer     |300497|
| Changed return of pop() on error                 | J.L. Bezemer     |040597|
| Added LOCAL_H support; fixed GCC warning (Now)   | J.L. Bezemer     |220597|
| Simplified PRINT and COPY; added toCharSeg()     | J.L. Bezemer     |240797|
| Added ARGN and ARGS                              | J.L. Bezemer     |240797|
| Fixed small bug in ARGS; cleaned up COPY         | J.L. Bezemer     |250797|
| Removed <limits.h>; fixed serious bug in throw() | J.L. Bezemer     |250797|
| Removed some redundant Applet->ErrNo             | J.L. Bezemer     |260797|
| Fixed GCC warning (setjmp); fixed small bug      | J.L. Bezemer     |270797|
| Changed throw(), pop() and rpop()                | J.L. Bezemer     |300797|
| Added BRANCHXT; changed header fieldname         | J.L. Bezemer     |120997|
| Removed BRANCHXT; replaced some variables        | J.L. Bezemer     |170997|
| Removed RCOPY2 and SHOW                          | J.L. Bezemer     |260997|
| Added unit to make Character Segment unsigned    | J.L. Bezemer     |270997|
| Removed INC2 and DEC2; added QDO                 | J.L. Bezemer     |151097|
| Removed QUERY, added REFILL                      | J.L. Bezemer     |311097|
| Fixed DJGPP I/O error in accept() when EOT       | J.L. Bezemer     |061197|
| Added CATCH and CAUGHT, changed Throw()          | J.L. Bezemer     |191197|
| Changed RANDOM to use RNDMASK                    | J.L. Bezemer     |221197|
| Removed EasyC syntax                             | J.L. Bezemer     |150198|
| Changed fileIO() for new file attributes         | J.L. Bezemer     |160298|
| Updated version info                             | J.L. Bezemer     |180298|
| Restored fileIO() and redesigned FOPEN code      | J.L. Bezemer     |200298|
| Added SQUOTE                                     | J.L. Bezemer     |200298|
| Integrated Web4tH variant                        | J.L. Bezemer     |290999|
| Removed unit datatype                            | J.L. Bezemer     |301099|
| Fixed error in accept() for GCC (flushing)       | J.L. Bezemer     |200600|
| Restored accept(); REFILL works again            | J.L. Bezemer     |200600|
| Removed WORD; added TOKEN and SKIP               | J.L. Bezemer     |160201|
| Fixed small bug in FCLOSE; redirect to tty       | J.L. Bezemer     |240401|
| Removed fileIO(); added OpenDevice, CloseDevice()| J.L. Bezemer     |230202|
| Fixed small bug in CloseDevice(), forced fclose()| J.L. Bezemer     |230202|
| Cleaned up pipe support for non-Unix platforms   | J.L. Bezemer     |240202|
| Pipes on non-Unix platforms always fail          | J.L. Bezemer     |240202|
| Added USE, removed TTY and FILE                  | J.L. Bezemer     |280202|
| Removed OpenDevice(), CloseDevice()              | J.L. Bezemer     |280202|
| Added OpenStream(), CloseStream()                | J.L. Bezemer     |280202|
| Changed emit(), accept()                         | J.L. Bezemer     |280202|
| Added NOPIPES directive; pipes are buggy         | J.L. Bezemer     |070302|
| Added fix for pipes; Popen() and Pclose()        | J.L. Bezemer     |080302|
| Fixed EOF bug in accept()                        | J.L. Bezemer     |090302|
| Restricted <dos.h> to TurboC to accomodate LCCW32| J.L. Bezemer     |060502|
| Added static modifier to Popen() and Pclose()    | J.L. Bezemer     |170902|
| Changed ARGS, NUMBER, CMOVE, FOPEN               | J.L. Bezemer     |060603|
| Removed COPY, NOOP, TOKEN, FETCHPRM, GE, LE      | J.L. Bezemer     |060603|
| Added PARSE, OFETCH, STRINGD, CELLD, PLACE       | J.L. Bezemer     |060603|
| Removed toCharSeg(); added cmove(), toPAD()      | J.L. Bezemer     |060603|
| Added toCstring()                                | J.L. Bezemer     |060603|
| Changed SKIP to OMIT                             | J.L. Bezemer     |120603|
| Changed RESULT to OUT (Wil Baden)                | J.L. Bezemer     |020703|
| Changed F4_UPDAT to F4_APPND; moved RPUT, RGET   | J.L. Bezemer     |070803|
| Redesigned cmove(); added Win32 pipes support    | J.L. Bezemer     |291003|
| Reshuffled init code in preparation of SLEEP     | J.L. Bezemer     |311003|
| Added SLEEP                                      | J.L. Bezemer     |031103|
| Fixed another 'clobbered' GCC warning            | J.L. Bezemer     |041103|
| Updated documentation header, fixed TurboC warns | J.L. Bezemer     |061103|
| Made dormant VM slightly more robust; deleted Out| J.L. Bezemer     |111103|
| Changed USE; error instead of ignore on NULL dev.| J.L. Bezemer     |131103|
| Fixed a count bug in cmove()                     | J.L. Bezemer     |211103|
| Added VECTOR                                     | J.L. Bezemer     |011203|
| Fixed small bugs in type() and -TRAILING         | J.L. Bezemer     |040104|
| Added Object->Offset support                     | J.L. Bezemer     |050104|
| Removed WAIT                                     | J.L. Bezemer     |140104|
| Added hidden variables, SaveStackFrame()         | J.L. Bezemer     |120304|
| Added support for SOURCE and SOURCE!             | J.L. Bezemer     |151004|
| Fixed small bug in FILL                          | J.L. Bezemer     |191104|
| Changed OFETCH to FETCHC                         | J.L. Bezemer     |040305|
| Rewrote the entire interpreter; fixed some bugs  | J.L. Bezemer     |050405|
| Added XT() macro, changed JUMP(), DDROP() macros | J.L. Bezemer     |060405|
| Changed DO, RDROP() macro; fixed GCC 3.x warns   | J.L. Bezemer     |070405|
| Fixed GCC 3.x error in SQUOTE and ARGS           | J.L. Bezemer     |170505|
| Fixed DSIZE() error in MOD, changed FETCHC       | J.L. Bezemer     |230505|
| Fixed potential bugs in CATCH                    | J.L. Bezemer     |240505|
| Removed superfluous check in PopStackFrame()     | J.L. Bezemer     |290505|
| Added comparison in throw()                      | J.L. Bezemer     |310505|
| Changed OpenStream() and CloseStream()           | J.L. Bezemer     |101105|
| Changed OPEN, CLOSE, CR and USE                  | J.L. Bezemer     |101105|
| Changed accept() and emit()                      | J.L. Bezemer     |211105|
| Removed CLSPAREN, HI, FIRST and LAST             | J.L. Bezemer     |110106|
| Added ENVIRON and UseStream()                    | J.L. Bezemer     |110106|
| Added PLITERAL                                   | J.L. Bezemer     |130106|
| Added UVAR(); changed STORE and ADDSTORE         | J.L. Bezemer     |160106|
| Added DEV(), FSEEK and FTELL                     | J.L. Bezemer     |180106|
| Added UDEV(), SDEV() and ODEV()                  | J.L. Bezemer     |190106|
| Removed UseStream(); cleaned up I/O              | J.L. Bezemer     |190106|
| Cleaned up FSEEK and FTELL a little              | J.L. Bezemer     |230106|
| Fixed TurboC warning in PopStackFrame()          | J.L. Bezemer     |160206|
| Changed CloseStream(); change channel if current | J.L. Bezemer     |160306|
| Changed accept(); all comparisons now VCIN, VCOUT| J.L. Bezemer     |160306|
| Fixed Unix pipe bug in OpenStream()              | J.L. Bezemer     |181106|
| Fixed NOPIPES pipe bug in OpenStream()           | J.L. Bezemer     |201106|
| Added CODE() and NEXT macros                     | J.L. Bezemer     |040107|
| Removed STSLHMOD; added SYNC                     | J.L. Bezemer     |030507|
| Added RADIX, OFFSET; removed HEX, DECIMAL, OCTAL | J.L. Bezemer     |201207|
| Changed accept() to Accept() on request          | J.L. Bezemer     |100708|
| Changed OpenStream(); return CELL_MIN on error   | J.L. Bezemer     |061108|
| Fixed tiny bug in OpenStream()                   | J.L. Bezemer     |111108|
| Moved emit() and Accept() to top                 | J.L. Bezemer     |060209|
| Changed SEED macro                               | J.L. Bezemer     |260909|
| Removed RANDOM and SEED, changed TIME            | J.L. Bezemer     |241009|
| Forced logical shift in SHIFT                    | J.L. Bezemer     |211109|
| Added BSD wait4() support                        | J.L. Bezemer     |170110|
| Improved FILL performance; added RANGE()         | J.L. Bezemer     |230110|
| Improved TYPE, ACCEPT and REFILL performance     | J.L. Bezemer     |240110|
| Added explicit count check to cmove()            | J.L. Bezemer     |200310|
| Added DELFILE                                    | J.L. Bezemer     |220610|
| Added length check to toPAD()                    | J.L. Bezemer     |280610|
| Made toPAD() and toCstring() more solid          | J.L. Bezemer     |300610|
| Made toPAD() more solid, added ENVFETCH          | J.L. Bezemer     |010710|
| Made (ERROR) special value for FSEEK             | J.L. Bezemer     |230211|
| Fixed fclose(), pclose() bug in CloseStream()    | J.L. Bezemer     |070311|
| Optimized NUMBER                                 | J.L. Bezemer     |120511|
| Made cmove() even smarter                        | J.L. Bezemer     |150511|
| Fixed TurboC warning in NUMBER                   | J.L. Bezemer     |160811|
| Replaced strtol() with str2cell(), cleaned up    | J.L. Bezemer     |091011|
| Fixed bug in OFFSET                              | J.L. Bezemer     |201211|
| Applied Coherent patches                         | J.L. Bezemer     |020112|
| Added NOUNLINK macro and TinyC detection         | J.L. Bezemer     |180312|
| Optimized VECTOR and EXECUTE a little            | J.L. Bezemer     |250712|
| Moved TO (higher priority)                       | J.L. Bezemer     |030812|
| Moved DO, LOOP; removed INC, DEC                 | J.L. Bezemer     |090812|
| Applied Raspberry Pi fixes; R0 to Rp0, S0 to Sp0 | J.L. Bezemer     |130812|
| Removed LEFT2, RIGHT2, added MLITERAL, DLITERAL  | J.L. Bezemer     |241012|
| Added GCC computed goto support                  | J.L. Bezemer     |241012|
| Reinstated LEFT2 and RIGHT2                      | J.L. Bezemer     |251012|
| Fixed @c bug, mapped STRINGD to NOOP             | J.L. Bezemer     |291012|
| Removed LEFT2, added SMOVE and smove()           | J.L. Bezemer     |021212|
| Added variable checks to TO and VALUE            | J.L. Bezemer     |160313|
| Fixed OMIT, PARSE to take TIB size into account  | J.L. Bezemer     |070413|
| Rewrote OMIT and PARSE                           | J.L. Bezemer     |080413|
| Fixed bugs in Accept() and PARSE                 | J.L. Bezemer     |090413|
+--------------------------------------------------+------------------+------+
|REMARKS                                           |    Programmer    | Date |
+--------------------------------------------------+------------------+------+
| None                                             |                  |      |
+--------------------------------------------------+------------------+------+

Copyright (C) 1994,2013 J.L. Bezemer

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


     This program executes a 4tH program. The user variables can be preloaded and
     used inside a 4th program. VarN is assigned to the number of variables
     that are preloaded. ArgN is equivalent to argc; ArgS is equivalent to argv.
     This interface allows you to pass arguments and strings to a 4tH program.
     It returns the contents of variable OUT on success or CELL_MIN on error.

Prototype: cell exec_4th (Hcode *Object, unsigned ArgN, char **ArgS,
        unsigned VarN, ...)
    Returns  : cell, the contents of OUT on succes or CELL_MIN on error
    Memory   : the size of the stack and variables and the user area
    Example  :


#include "4th.h"
#include <stdlib.h>
#include <ctype.h>

#ifndef ARCHAIC
int main (int argc, char **argv)
#else
    int main (argc, argv) int argc; char **argv;
#endif

{
    Hcode *object;
    char  *sources;
    cell   result;

    if (argc >= 2)
    {
        if ((sources = open_4th (argv [1])) == NULL)
            printf ("Loading; \'%s\' does not exist or too large\n", argv [1]);

        else
        {
            object = comp_4th (sources);

            if (object)
            {
                result = exec_4th (object, argc - 1, argv + 1, 2, 125L, 6L);
                printf ("Execute; word %u: %s\n", object->ErrLine,
                        errs_4th [object->ErrNo]);
                printf ("\nResult of script: %ld\n", result);
                return (EXIT_SUCCESS);
            }
        }
    }
    return (EXIT_FAILURE);
}


Input    : None
    Output   : depends on program
Related  : dump_4th(), comp_4th()
    */


#ifdef USRLIB4TH
#include <sys/cmds_4th.h>
#include <4th.h>
#else
#include "4th.h"
#include "cmds_4th.h"
#endif

#include <stdlib.h>
#include <setjmp.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#ifdef UNIX
#warning "UNIX Defined"
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#endif

#define EOTu   4                       /* Unix end of text character */
#define EOTm  26                       /* Microsoft end of text character */

#define EXCEPTION 1                    /* label for longjmp() */
#define OPERAND   Object->CodeSeg[Object->ErrLine].Value
#define PROGCOUNT Object->ErrLine
#define CIN  ((int)STD4IN)             /* input device number */
#define COUT ((int)STD4OUT)            /* output device number */
    /* stack commands */
#define DFREE(a)   if((ToRS-ToS)<(a))throw(M4SOVFLW)
#define RFREE(a)   if((ToRS-ToS)<(a))throw(M4ROVFLW)
#define DSIZE(a)   if(ToS<(a))throw(M4SEMPTY)
#define RSIZE(a)   if(ToRS>(Rp0-(a)))throw(M4REMPTY)
#define DPOP       (Stack[--ToS])
#define DPUSH(a)   (Stack[ToS++]=(a))
#define RPOP       (Stack[++ToRS])
#define RPUSH(a)   (Stack[ToRS--]=(a))
#define DDROP      ToS--
#define RDROP      ToRS++
#define RS(a)      (Stack[ToRS+(a)])
#define DS(a)      (Stack[ToS-(a)])
    /* main execution loop construct */
#ifdef USEGCCGOTO
#define CODE(a)    L_##a:
#define NEXT       if ((++Object->ErrLine) < Object->CodeSiz)\
        goto *commands [Object->CodeSeg [Object->ErrLine].Word];\
    else break;
#define UNKNOWN    L_UNKNOWN:
#else
#define CODE(a)    case(a):
#define NEXT       break
#define UNKNOWN    default:
#endif
    /* various other command routines */
#define JUMP(a)    Object->ErrLine=(int)(a)
#define RANGE(a,b) if((b)>0L)if(((a)<TIB)||(((a)+(b))>UnitSiz))throw(M4BADADR)
#define XT(a)      if(((a)>=(cell)Object->CodeSiz)||((a)<-1L))throw(M4BADTOK)
#define VAR(a)     if(((a)>=(cell)VarNum)||((a)<0L))throw(M4BADVAR)
#define CSTR(a)    if(((a)>=(cell)Object->StringSiz)||((a)<0L))throw(M4BADSTR)
#define UVAR(a)    if(((a)>=(cell)VarNum)||((a)<ENV4TH))throw(M4BADVAR)
#define DEV(a)     if(((a)<CIN)||((a)>=MAXDEVS))throw(M4BADDEV)
#define UDEV(a)    if(((a)<=COUT)||((a)>=MAXDEVS))throw(M4BADDEV)
#define ODEV(a)    if(Stream[(int)(a)].Device==NULL)throw(M4IOERR)
#define SDEV(a)    if(Stream[(int)(a)].Mode&F4_PIPE)throw(M4BADDEV)

#ifdef __TURBOC__                      /* TurboC supports no pipes */
#define NOPIPES
#endif

#ifdef __DJGPP__                       /* can't get DJGPP to work */
#define NOPIPES
#endif

#ifdef __TINYC__                       /* TCC doesn't support unlink() */
#define NOUNLINK
#endif

#ifdef NOUNLINK                        /* use ANSI equivalent instead */
#define unlink(a) remove(a)
#endif

    union semun {
        int              val;    /* Value for SETVAL */
        struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
        unsigned short  *array;  /* Array for GETALL, SETALL */
        struct seminfo  *__buf;  /* Buffer for IPC_INFO
                                    (Linux-specific) */
    };

/* define 4tH I/O device */
typedef struct {
    char    Mode;                        /* standard opening mode */
    FILE*   Device;                      /* external device opened */
#ifdef ARCHAIC
    FILE* (*Connect)    ();              /* device opening function (K&R) */
    int   (*Disconnect) ();              /* device closing function (K&R) */
#else
    FILE* (*Connect)    (const char*, const char*);
    int   (*Disconnect) (FILE *);        /* device closing function (ANSI) */
#endif
} Dev4th;
/* device standard opening table */
typedef struct {
    char Mode;                           /* standard opening mode */
    char CMode [4];                      /* C mode string mapping */
} Mode4th;
/* 4tH I/O devices */
static Dev4th Stream  [MAXDEVS];
static FILE  *Channel [2] = {NULL, NULL};

static unsigned ToS, ToRS;             /* top of stack/top of ret. stack */
static unsigned UnitSiz;               /* size of Character Segment */
static unsigned VarNum;                /* calculate number of variables */
static char     Sleeping;              /* VM is dormant if TRUE */
static cell    *Vars;                  /* pointer to Variable Area */
static cell    *Stack;                 /* pointer to stack */
static cell    *Handler;               /* throw handler */
static cell    *Hld;                   /* equivalent of forth HLD */
static cell    *Here;                  /* pointer to circular PAD buffer */
static cell    *Base;                  /* radix status */
static Hcode   *Applet;                /* externalize Object */
static jmp_buf  Thrown;                /* buffer for throw error-return */
/* THROW prototype */
static void throw __PROTO((cell ErrCode));

#ifdef NOPIPES                         /* dummy pipe functions */
static FILE* Popen(const char* a, const char* b) { if (a==b); return (NULL); }
static int Pclose(FILE *a) { if (a); return (0); }
#else
#ifdef UNIX

#ifdef BSD
#define WAIT(x,y) wait4((-1),x,y,(NULL))
#else
#define WAIT(x,y) waitpid((-1),x,y)
#endif
/* more reasonable pclose */
#ifndef ARCHAIC
static int Pclose (FILE *p)
#else
    static int Pclose (p) FILE *p;
#endif                                 /* no error if child died */
{
    return ((pclose (p)) && (errno != ECHILD) ? -1 : 0);
}

#ifndef ARCHAIC                        /* relatively safe popen() */
static FILE *Popen (const char *f, const char *m)
#else
    static FILE *Popen (f, m) const char *f; const char *m;
#endif
{
    FILE *p;                             /* filepointer to pipe */
    long  x;                             /* simple counter */
    int   s = 0;                         /* status of child */

    p = popen (f, m);                    /* perform a normal popen() */
    for (x = 0; x < PIPEWAIT && s == 0; x++) WAIT (&s, WNOHANG);
    return (s ? NULL : p);               /* check the status for a while */
}                                      /* return NULL if not normal */
#else
#ifdef _WIN32                          /* use equivalent Win32 calls */
static FILE* Popen (const char* a, const char* b) { return (_popen (a, b)); }
static int Pclose (FILE *a) { return (_pclose (a) == -1 ? -1 : 0); }
#endif                                 /* _pclose() returns -1 on error */
#endif
#endif


/*
   This routine saves a stackframe for PAUSE and CATCH.
   */

#ifndef ARCHAIC
static void PushStackFrame (void)
#else
static void PushStackFrame ()
#endif
{
    RFREE (3); RPUSH ((cell) ToS); RPUSH (*Handler);
    RPUSH ((cell) Applet->ErrLine); *Handler = ToRS;
}


/*
   This routine restores a stackframe for PAUSE and CATCH.
   */

#ifndef ARCHAIC
static unsigned PopStackFrame (void)
#else
static unsigned PopStackFrame ()
#endif

{                                      /* handler contains RP */
    if ((*Handler > Rp0) || (*Handler < (cell) ToS)) return (M4BADPTR);
    /* Return Stack may not collide */
    ToRS = (unsigned) *Handler;          /* restore RP from handler */
    if (ToRS > (Rp0 - 3)) return (M4REMPTY);
    /* check if enough items on ret stack */
    Applet->ErrLine = (int) RPOP + 1;
    *Handler = RPOP;                     /* retrieve handler from Return Stack */
    ToS = (unsigned) RPOP;               /* retrieve SP from Return Stack */
    /* SP might have shrunk after CATCH */
    if (ToS > ToRS) return (M4BADPTR);
    else return (M4NOERRS);              /* SP may not violate Return Stack */
}


/*
   This is the equivalent of Forths THROW.
   */

#ifndef ARCHAIC
static void throw (cell ErrCode)
#else
    static void throw (ErrCode) cell ErrCode;
#endif

{
    int  Caller;                         /* temporary storage for return addr */
    cell PopCode;                        /* What PopStackFrame() returns */

    if (ErrCode)                         /* THROW 0 does nothing */
    {
        if (*Handler)                   /* if a previous handler */
        {                            /* handler contains RP */
            Caller = Applet->ErrLine;
            if ((PopCode = (cell) PopStackFrame ()) != M4NOERRS)
            {                       /* invalid stack frame */
                Applet->ErrLine = Caller;
                ErrCode = PopCode;    /* update header vars */
            }
            else
            {                       /* prepare to return */
                DS (1) = -ErrCode;
                ErrCode = M4NOERRS;   /* update error vars */
                (Applet->ErrLine)++;  /* increment PROGCOUNT */
            }
        }                            /* no or invalid handler */
        if ((ErrCode < 0) || (ErrCode > LastMsg4th)) Applet->ErrNo = M4THROW;
        else Applet->ErrNo = (unsigned) ErrCode;
        longjmp (Thrown, EXCEPTION);    /* jump to main loop */
    }
}


/* Gets a value from the String User Area */

#ifndef ARCHAIC
static unit fetch (cell address)
#else
    static unit fetch (address) cell address;
#endif

{
    RANGE (address, 1); return (Applet->UnitSeg [(unsigned) address]);
}


/* Stores a value in the String User Area */

#ifndef ARCHAIC
static void store (cell address, unit value)
#else
    static void store (address, value) cell address; unit value;
#endif

{
    RANGE (address, 1); Applet->UnitSeg [(unsigned) address] = value;
}


/* This baby simply prints a single character. Equivalent of Forths EMIT */

#ifndef ARCHAIC
static void emit (unit c)
#else
    static void emit (c) unit c;
#endif

{
    if ((fputc ((int) c, Channel [COUT])) == EOF) throw (M4IOERR);
}


/*
   This routine reads J characters from input device DEV and places them at
   address I. It returns the number of characters actually read.
   Leaves ASCIIZ string when reading a textdevice.
   */

#ifndef ARCHAIC
static cell Accept (cell i, cell j, char mode)
#else
    static cell Accept (i, j, mode) cell i; cell j; char mode;
#endif

{
    int  c = 0;                          /* char read, default for 't' mode */
    char OK = TRUE;                      /* OK to read next char */
    unit *a = Applet->UnitSeg + (unsigned) i;
    cell  t = 0;                         /* counter */

    RANGE (i, j);                        /* check the range of the buffer */
    /* device is keyboard: textmode */
    if (Vars [VCIN] == STD4IN) mode = 't';
    while ((OK) && (t < j)) {
        c = fgetc (Channel [CIN]);      /* get character */
        if ((c == EOF) || ((mode == 't') && (c == (int) '\n'))) OK = FALSE;
        else if ((mode == 'b') ||       /* stop on EOF or LF in text mode */
                ((c != (int) '\r') && (c != EOTu) && (c != EOTm)))
        {                             /* store the character and inc count */
            *a++ = (unit) c; t++;       /* when in binary mode or no CR|EOF */
        }                             /* has been read (these are skipped) */
    }                                    /* until count reached or EOF */
    /* when reading from keyboard */
    if ((OK) && (Vars [VCIN] == STD4IN))
        do { c = fgetc (Channel [CIN]); } while ((c != EOF) && (c != '\n'));
    /* empty buffer (read till LF) */
    if (mode == 't')
    {
        store (i + t, '\0');            /* when in text mode terminate string */
        if ((t == 0) && (c == EOF)) return (-1);
    }                                 /* return -1 when nothing read */

    return (t);                          /* return #chars read */
}


/* This function is roughly equivalent with Forths <# */

#ifndef ARCHAIC
static void lsharp (void)
#else
static void lsharp ()
#endif

{
    *Hld = (PAD + PADSIZ); store ((cell) --(*Hld), '\0');
}


/* This function is equivalent with Forths SIGN */

#ifndef ARCHAIC
static void sign (cell x)
#else
    static void sign (x) cell x;
#endif

{
    if (x < 0) store ((cell) --(*Hld), '-');
}


/* This function is roughly equivalent with Forths # */

#ifndef ARCHAIC
static unit sharp (void)
#else
static unit sharp ()
#endif

{
    unit y = 0;

    if ((*Base < 2) || (*Base > 36)) throw (M4BADRDX);

    if (ToS)
    {
        y = (unit) (DS (1) % *Base);
        DS (1) /= *Base;
    }
    else throw (M4SEMPTY);

    return (y += (y > 9) ? '7' : '0');
}


/* This function is equivalent of Forths #S */

#ifndef ARCHAIC
static void sharpS (void)
#else
static void sharpS ()
#endif

{
    do store ((cell) --(*Hld), sharp ());
    while (DS (1));
}


/*
   This function prints y characters from address x. Equivalent of Forths TYPE.
   */

#ifndef ARCHAIC
static void type (cell x, cell y)
#else
    static void type (x, y) cell x; cell y;
#endif

{
    unit *a = Applet->UnitSeg + (unsigned) x;

    RANGE (x, y);
    while (y > 0) 
    {
        emit (*a); y--; a++;
    }
}


/*
   Prints a number according to the current radix. Roughly equivalent to D.R
   */

#ifndef ARCHAIC
static void dotR (cell n)
#else
    static void dotR (n) cell n;
#endif

{
    cell t;

    DSIZE (1); if ((t = DS (1)) < 0) DS (1) = -(DS(1));
    lsharp (); sharpS (); sign (t); DDROP;
    while (strlen ((char*) Applet->UnitSeg + (unsigned) *Hld) < n)
        store ((cell) --(*Hld), ' ');
    type ((cell) *Hld, (cell) (PAD + PADSIZ) - (*Hld + 1));
}


/* This routine is a 'smart' implementation of SMOVE. */

#ifndef ARCHAIC
static void smove (cell src, cell dst, cell cnt)
#else
    static void smove (src, dst, cnt) cell src; cell dst; cell cnt;
#endif

{
    cell *a = Vars + (unsigned) src;     /* temp pointer source */
    cell *b = Vars + (unsigned) dst;     /* temp pointer destination */
    cell  c = cnt;

    if (src < dst)                       /* are regions overlapping? */
    {                                 /* then reverse move */
        a = Vars + (unsigned) (src + (cnt - 1));
        b = Vars + (unsigned) (dst + (cnt - 1));
        while (c > 0)
        {
            *b = *a; c--; a--; b--;
        }
    }
    else                                 /* are regions not overlapping? */
    {                                 /* then start moving right away */
        if (src > dst)                  /* unless there is nothing to move */
            while (c > 0)
            {
                *b = *a; c--; a++; b++;
            }
    }
}


/* This routine is a 'smart' implementation of CMOVE. */

#ifndef ARCHAIC
static cell cmove (cell src, cell dst, cell cnt)
#else
    static cell cmove (src, dst, cnt) cell src; cell dst; cell cnt;
#endif

{
    unit *a = Applet->UnitSeg + (unsigned) src;  /* temp pointer source */
    unit *b = Applet->UnitSeg + (unsigned) dst;  /* temp pointer destination */
    cell  c = cnt;

    RANGE (src, cnt);
    RANGE (dst, cnt);

    if (src < dst)                       /* are strings overlapping? */
    {                                 /* then reverse move */
        a = Applet->UnitSeg + (unsigned) (src + (cnt - 1));
        b = Applet->UnitSeg + (unsigned) (dst + (cnt - 1));
        while (c > 0)
        {
            *b = *a; c--; a--; b--;
        }
    }
    else                                 /* are strings not overlapping? */
    {                                 /* then start moving right away */
        if (src > dst)                  /* unless there is nothing to move */
            while (c > 0)
            {
                *b = *a; c--; a++; b++;
            }
    }
    return (dst + cnt);                  /* return destination address */
}


/*
   This routine simply copies the string constant 'constr' to the PAD.
   */

#ifndef ARCHAIC
static cell toPAD (char* constr)
#else
    static cell toPAD (constr) char* constr;
#endif

{
    if ((*Here + strlen (constr) + 1) > STRTOP) *Here = PAD;
    DPUSH (*Here);

    for (;(*constr) && ((*Here + 1) < STRTOP); constr++, (*Here)++)
        store (*Here, (unit) *constr);
    store ((*Here)++, '\0');
    return (*Here - (DS (1) + 1));
}


/*
   This routine simply copies a string/count to the PAD and
   terminates it.
   */

#ifndef ARCHAIC
static char* toCstring (cell str, cell cnt)
#else
    static char* toCstring (str, cnt) cell str; cell cnt;
#endif

{
    unit *p;

    if ((*Here + cnt + 1) > STRTOP) *Here = PAD;
    p = (Applet->UnitSeg + (unsigned) *Here);

    *Here = (unsigned) cmove (str, *Here, cnt);
    store ((*Here)++, '\0');
    return ((char *) p);
}


/*
   This routine closes an input- or an output file. ErrCode determines which
   error is thrown. M4NOERRS will bypass the throw() routine and force the close.
   */

#ifndef ARCHAIC
static void CloseStream (int StrNo, unsigned ErrCode)
#else
    static void CloseStream (StrNo, ErrCode) int StrNo; unsigned ErrCode;
#endif

{
    UDEV (StrNo);                        /* is it a valid stream */ 
    if (Stream [StrNo].Device != NULL)   /* ignore unopened streams */
    {
        if ((Stream [StrNo].Mode & F4_READ) && (Vars [VCIN] == StrNo))
        {                           /* set CIN accordingly */
            Channel [CIN]  = stdin; Vars [VCIN] = STD4IN;
        }                           /* redirect output channel */
        if ((Stream [StrNo].Mode & F4_WRITE) && (Vars [VCOUT] == StrNo))
        {                           /* set COUT accordingly */
            Channel [COUT] = stdout; Vars [VCOUT] = STD4OUT;
        }                           /* call appropriate method */
        if (Stream [StrNo].Disconnect (Stream [StrNo].Device))
        {
            Stream [StrNo].Device = NULL; throw (ErrCode);
        }
        Stream [StrNo].Device = NULL;  /* signal external device closed */
    }
}


/*
   This routine opens an input- or an output file.
   */

#ifndef ARCHAIC
static cell OpenStream (char *Name, int Mode)
#else
    static cell OpenStream (Name, Mode) char *Name; int Mode;
#endif

{
#ifndef WEB4TH
    static Mode4th ModeList [] = {
        { F4_READ, "rb" },
        { F4_WRITE, "wb" },
        { F4_READ|F4_WRITE, "r+b" },
        { F4_APPND|F4_WRITE, "ab" },
        { F4_APPND|F4_WRITE|F4_READ, "a+b" },
#ifdef UNIX 
        { F4_READ|F4_PIPE, "r" },
        { F4_WRITE|F4_PIPE, "w" }
#else
        { F4_READ|F4_PIPE, "rb" },
            { F4_WRITE|F4_PIPE, "wb" }
#endif
    };

    static char Mapping [] ="\x0\x0\x1\x2\x3\x0\x3\x4\x5\x5\x6\x5\x6\x5\x6\x5";
    int x;

    for (x = COUT + 1; x < MAXDEVS; x++) /* do not search CIN and COUT */
        if (Stream [x].Device == NULL)   /* find unopened stream */
        {                             /* initialize stream */
            Stream [x].Mode = ModeList [(int) Mapping [Mode]].Mode;
            Stream [x].Disconnect = (Stream [x].Mode & F4_PIPE ?
                    Pclose : fclose);
            Stream [x].Connect =    (Stream [x].Mode & F4_PIPE ?
                    Popen  : fopen);
            return (((Stream [x].Device = Stream [x].Connect
                            (Name, ModeList [(int) Mapping [Mode]].CMode)) == NULL ?
                        CELL_MIN : (cell) x ));
        }                             /* open stream */
#endif
    return (CELL_MIN);
}

/*
 *   Returns 0 on error, non-zero on success.
 */
int semcall(int sid, int op) {
    struct sembuf   sb;

    sb.sem_num = 0;
    sb.sem_op = op;
    sb.sem_flg = 0;

    if (semop(sid, &sb, 1) == -1) {
        perror("4th: semcall ");
        return (-1);
    } else {
        return (0);
    }
}


/*
   Main routine and the only external.
   */

#ifndef ARCHAIC
cell exec_4th (Hcode *Object, unsigned ArgN, char **ArgS,
        unsigned VarN, ...)
#else
    cell exec_4th (Object, ArgN, ArgS, VarN) Hcode *Object;
    unsigned ArgN; char **ArgS; unsigned VarN;
#endif

{
    unsigned VarMax;                     /* maximum number of C variables */
    unsigned x;                          /* temporary counter */
    cell     a, b, c;                    /* internal stack variables */
    unit     t;                          /* temporary char */
    unit    *i;                          /* temporary pointer */
    char    *p;                          /* temporary pointer */
    cell    *In;                         /* equivalent of forth >IN */
    va_list  Vals;                       /* list of preloaded variables */

    if (! Object) return (CELL_MIN);     /* check if object is reliable */
    else if (! Object->Reliable) return (CELL_MIN);
    /* initialize main variables */
    Applet   = Object;                   /* externalize argument */
    Sleeping = FALSE;                    /* not a dormant VM */
    ToRS     = Rp0;                      /* reset return stack pointer */
    ToS      = Sp0;                      /* reset stackpointer */
    UnitSiz  = Object->Strings + TIBSIZ + PADSIZ;
    /* calculate size Unit Segment */
    for (x = CIN; x < MAXDEVS; x++) Stream [x].Device = NULL;
    Channel [CIN]  = Stream [CIN].Device  = stdin;
    Channel [COUT] = Stream [COUT].Device = stdout;
    Stream [CIN].Mode = F4_READ; Stream [COUT].Mode = F4_WRITE;
    /* read and write from tty */
    if (Object->Offset == 0)
    {                                 /* start a new VM */
        VarMax = Object->Offset = VarN + VAR4TH;
        VarNum = Object->Variables + Object->Offset;
        /* reserve space for BASE, >IN */
        Object->ErrNo   = M4NOERRS;     /* reset errorcode */
        Object->ErrLine = 0;            /* reset linepointer */

        if ((Object->CellSeg = Stack = (cell*)
                    calloc (STACKSIZ + SYS4TH + VarNum, sizeof (cell))) == NULL)
        {                            /* allocate Integer Segment */
            Object->ErrNo = M4NOMEM;
            return (CELL_MIN);
        }

        if ((Object->UnitSeg = (unit*)
                    calloc (UnitSiz + 1, sizeof (unit))) == NULL)
        {                            /* allocate Character Segment */
            free (Stack);
            Object->ErrNo = M4NOMEM;
            return (CELL_MIN);
        }
        /* assign hidden variables */
        Handler = Stack + STACKSIZ;     /* assign pointer to HANDLER */
        Here    = Handler + 1;          /* assign pointer to HERE */
        Hld     = Here + 1;             /* assign pointer to HLD */

        *Handler = 0;                   /* initialize HANDLER */
        *Here    = PAD;                 /* initialize HERE to PAD */
        /* set pointer to Variable Area */
        Vars = Stack + STACKSIZ + SYS4TH;
        /* preload variables and environs */
        Vars [VBASE]  = 10L;            /* initialize BASE */
        Vars [VIN]    = 0L;             /* initialize >IN */
        Vars [VOUT]   = CELL_MIN;       /* initialize OUT */
        Vars [VTIB]   = TIB;            /* initialize SOURCE, TIB address */
        Vars [VTIBS]  = TIBSIZ;         /* initialize SOURCE, TIB size */
        Vars [VHI]    = (cell) UnitSiz - 1;
        Vars [VFIRST] = (cell) Object->Offset;
        Vars [VLAST]  = (cell) VarNum - 1;
    }                                 /* end of new VM */
    else
    {                                 /* revive a dormant VM */
        Stack = Object->CellSeg;        /* setup CellSegment areas */
        Vars  = Stack + STACKSIZ + SYS4TH;
        /* set pointer to Variable Area */
        Handler = Stack + STACKSIZ;     /* assign pointer to HANDLER */
        Here    = Handler + 1;          /* assign pointer to HERE */
        Hld     = Here + 1;             /* assign pointer to HLD */
        /* now retrieve all variables */
        Object->ErrNo = PopStackFrame ();
        /* calculate Var Area variables */
        VarNum = Object->Variables + Object->Offset;
        VarMax = ((VarN + VAR4TH) > Object->Offset ? Object->Offset :
                (VarN + VAR4TH));
    }                                 /* depends on smallest value */
    /* end of dormant VM */
    va_start (Vals, VarN);               /* copy C variables */
    for (x = VAR4TH; x < VarMax; x++) Vars [x] = va_arg (Vals, cell);
    va_end (Vals);

    Vars [VCIN]  = STD4IN;               /* signal channel-in is stdin */
    Vars [VCOUT] = STD4OUT;              /* signal channel-out is stdout */

    Base = &(Vars [VBASE]);              /* assign pointer to BASE */
    In   = &(Vars [VIN]);                /* assign pointer to >IN */

#ifdef USEGCCGOTO
#include "gcc_exec.h"
#endif

    /*
       This is the main calculation engine. Most operators can be reduced to pop() and
       push() calls. It executes until there are no more operators left or QUIT is
       called.
       */

    (void) setjmp (Thrown);              /* Return from error */

    if ((! Object->ErrNo) && (Object->ErrLine >= 0))
    {
#ifdef USEGCCGOTO
        if ((Object->ErrLine) < Object->CodeSiz)
            goto *commands [Object->CodeSeg [Object->ErrLine].Word];
        for (;;)
#else
            for (;(Object->ErrLine < Object->CodeSiz); Object->ErrLine++)
                switch (Object->CodeSeg [Object->ErrLine].Word)
#endif
                {
                    CODE (CELLD)
                        CODE (STRINGD)  NEXT;
                    CODE (LITERAL)  DFREE (1); DPUSH (OPERAND); NEXT;
                    CODE (BRANCH)   JUMP (OPERAND); NEXT;
                    CODE (BRANCH0)  DSIZE (1);
                    if (DPOP == F_F) JUMP (OPERAND);
                    NEXT;
                    CODE (CALL)     RFREE (1); RPUSH ((cell) PROGCOUNT);
                    JUMP (OPERAND); NEXT;
                    CODE (EXIT)     RSIZE (1); a = RPOP; XT (a); JUMP (a); NEXT;
                    CODE (DUP)      DSIZE (1); DFREE (1); a = DS(1); DPUSH (a); NEXT;
                    CODE (DROP)     DSIZE (1); DDROP; NEXT;
                    CODE (SWAP)     DSIZE (2); a = DS (1); DS (1) = DS (2); DS (2) = a;
                    NEXT;
                    CODE (ROT)      DSIZE (3); a = DS (1); DS (1) = DS (3);
                    DS (3) = DS (2); DS (2) = a; NEXT;
                    CODE (OVER)     DSIZE (2); DFREE (1); a = DS (2); DPUSH (a); NEXT;
                    CODE (VARIABLE) DFREE (1);
                    DPUSH ((cell) Object->Offset + OPERAND); NEXT;
                    CODE (VALUE)    DFREE (1); a = (cell) Object->Offset + OPERAND;
                    VAR (a); DPUSH (Vars [(unsigned) a]); NEXT;
                    CODE (RCOPY)    RSIZE (1); DFREE (1); DPUSH (RS (1)); NEXT;
                    CODE (RGET)     RSIZE (1); DPUSH (RPOP); NEXT;
                    CODE (RPUT)     DSIZE (1); RPUSH (DPOP); NEXT;
                    CODE (STORE)    DSIZE (2); a = DPOP; UVAR (a);
                    Vars [(unsigned) a] = DPOP; NEXT;
                    CODE (FETCH)    DSIZE (1); a = DS (1); VAR (a);
                    DS (1) = Vars [(unsigned) a]; NEXT;
                    CODE (ADDSTORE) DSIZE (2); a = DPOP; UVAR (a);
                    Vars [(unsigned) a] += DPOP; NEXT;
                    CODE (TO)       DSIZE (1); a = (cell) Object->Offset + OPERAND;
                    UVAR (a); Vars [(unsigned) a] = DPOP; NEXT;
                    CODE (LOOP)     RSIZE (2);
                    if (++(RS (1)) < RS (2)) JUMP (OPERAND);
                    else { RDROP; RDROP; }
                    NEXT;
                    CODE (DO)       DSIZE (2); a = DPOP; RPUSH (DPOP); RPUSH (a); NEXT;
                    CODE (QDO)      DSIZE (2); a = DPOP; b = DPOP;
                    if (a == b) JUMP (OPERAND);
                    else { RPUSH (b); RPUSH (a); }
                    NEXT;
                    CODE (PLOOP)    RSIZE (2); DSIZE (1);
                    RS (1) += DPOP;
                    if ((DS(0) > 0L) ? (RS(1) < RS(2)) :
                            (RS(1) > RS(2))) JUMP (OPERAND);
                    else { RDROP; RDROP; }
                    NEXT;
                    CODE (LEAVE)    RSIZE (2); RS (1) = RS (2); NEXT;
                    CODE (EQ0)      DSIZE (1); DS (1) = DS (1) == 0L ? F_T : F_F; NEXT;
                    CODE (NE0)      DSIZE (1); DS (1) = DS (1) != 0L ? F_T : F_F; NEXT;
                    CODE (PLUS)     DSIZE (2); DDROP; DS (1) += DS (0); NEXT;
                    CODE (EQ)       DSIZE (2); DDROP;
                    DS (1) = DS (1) == DS (0) ? F_T : F_F; NEXT;
                    CODE (MOD)      DSIZE (2);
                    if (DPOP != 0L) DS(1) %= DS(0);
                    else throw (M4DIVBY0);
                    NEXT;
                    CODE (MINUS)    DSIZE (2); DDROP; DS (1) -= DS (0); NEXT;
                    CODE (MUL)      DSIZE (2); DDROP; DS (1) *= DS (0); NEXT;
                    CODE (DIV)      DSIZE (2);
                    if (DPOP != 0L) DS (1) /= DS (0); 
                    else throw (M4DIVBY0); NEXT;
                    CODE (SLASHMOD) DSIZE (2);
                    if (DS (1) != 0L)
                    {
                        a = DS (2);
                        DS (2) %= DS (1);
                        DS (1) = a / DS (1);
                    }
                    else throw (M4DIVBY0); NEXT;
                    CODE (GT)       DSIZE (2); DDROP;
                    DS (1) = DS (1) > DS (0) ? F_T : F_F; NEXT;
                    CODE (MIN)      DSIZE (2); DDROP;
                    if (DS (1) > DS (0)) DS (1) = DS (0); NEXT;
                    CODE (MAX)      DSIZE (2); DDROP;
                    if (DS (1) < DS (0)) DS (1) = DS (0); NEXT;
                    CODE (STARSLSH) DSIZE (3);
                    if (DPOP != 0L)
                    {
                        DS (2) *= DS (1); DS (2) /= DS (0); DDROP;
                    }
                    else throw (M4DIVBY0);
                    NEXT;
                    CODE (ABS)      DSIZE (1); if (DS (1) < 0) DS (1) = -(DS (1));
                    NEXT;
                    CODE (NEGATE)   DSIZE (1); DS (1) = -(DS (1)); NEXT;
                    CODE (OR)       DSIZE (2); DDROP; DS (1) |= DS (0); NEXT;
                    CODE (AND)      DSIZE (2); DDROP; DS (1) &= DS (0); NEXT;
                    CODE (XOR)      DSIZE (2); DDROP; DS (1) ^= DS (0); NEXT;
                    CODE (SHIFT)    DSIZE (2); a = DPOP;
                    if (a < 0L)
                    {        /* force logical right shift */
                        DS (1) = (DS (1) >> 1L) & CELL_MAX;
                        a = -1L - a; DS (1) >>= a;
                    }        /* shift one bit, clear it */
                    else DS (1) <<= a;
                    NEXT;
                    CODE (INVERT)   DSIZE (1); DS (1) = ~(DS (1)); NEXT;
                    CODE (RIGHT2)   DSIZE (1); DS (1) >>= 1L; NEXT;
                    CODE (LT)       DSIZE (2); DDROP;
                    DS (1) = DS (1) < DS (0) ? F_T : F_F; NEXT;
                    CODE (NE)       DSIZE (2); DDROP;
                    DS (1) = DS (1) != DS (0) ? F_T : F_F; NEXT;
                    CODE (LT0)      DSIZE (1); DS (1) = DS (1) < 0L ? F_T : F_F; NEXT;
                    CODE (GT0)      DSIZE (1); DS (1) = DS (1) > 0L ? F_T : F_F; NEXT;
                    CODE (RCOPY3)   RSIZE (3); DFREE (1); DPUSH (RS (3)); NEXT;
                    CODE (PRINT)    for (p = Object->StringSeg + (unsigned) OPERAND;
                            *p; p++) emit ((unit) *p);
                    NEXT;
                    CODE (CR)
#ifndef UNIX
                        if (Vars [VCOUT] != STD4OUT) emit ('\r');
#endif
                    emit ('\n'); NEXT;
                    CODE (SPACES)   DSIZE (1); DDROP; for (a = 0L; a < DS (0); a++)
                        emit (' '); NEXT;
                    CODE (DOT)      dotR (0); emit (' '); NEXT;
                    CODE (DOTR)     DSIZE (1); dotR (DPOP); NEXT;
                    CODE (EMIT)     DSIZE (1); emit ((unit) DPOP); NEXT;
                    CODE (VECTOR)   RFREE (1); RPUSH ((cell) PROGCOUNT);
                    a = Vars [Object->Offset + (unsigned) OPERAND];
                    XT (a); JUMP (a); NEXT;
                    CODE (EXECUTE)  DSIZE (1); a = DPOP; RPUSH ((cell) PROGCOUNT);
                    XT (a); JUMP (a); NEXT;
                    CODE (PLITERAL) DSIZE (1); DS (1) += OPERAND; NEXT;
                    CODE (MLITERAL) DSIZE (1); DS (1) *= OPERAND; NEXT;
                    CODE (DLITERAL) DSIZE (1); a = OPERAND;
                    if (a != 0L) DS (1) /= a; else throw (M4DIVBY0);
                    NEXT;
                    CODE (FETCHC)   DSIZE (1); a = DPOP;
                    if ((a < 0L) || (a >= (cell) Object->CodeSiz))
                        throw (M4BADTOK);
                    else
                    {
                        b = Object->CodeSeg [(int) a].Value;
                        if (Object->CodeSeg [(int) a].Word == NOOP)
                            (void) toPAD (Object->StringSeg +
                                    (unsigned) b);
                        else DPUSH (b);
                    }
                    NEXT;
                    CODE (TIME)     DFREE (1); DPUSH ((cell) time (NULL)); NEXT;
                    CODE (CFETCH)   DSIZE (1); DS (1) = (cell) fetch (DS (1)); NEXT;
                    CODE (CSTORE)   DSIZE (2); a = DPOP; store (a, (unit) DPOP); NEXT;
                    CODE (LSHARP)   lsharp (); NEXT;
                    CODE (RSHARP)   DSIZE (1); DFREE (1); DDROP; DPUSH ((cell) *Hld);
                    DPUSH ((cell) (PAD + PADSIZ) - (*Hld + 1)); NEXT;
                    CODE (HOLD)     DSIZE (1); store ((cell) --(*Hld), (unit) DPOP);
                    NEXT;
                    CODE (SIGN)     DSIZE (2); sign (DS (2)); DS (2) = DS (1); DDROP;
                    NEXT;
                    CODE (SHARP)    DSIZE (1); store ((cell) --(*Hld), sharp ()); NEXT;
                    CODE (SHARPS)   DSIZE (1); sharpS (); NEXT;
                    CODE (TYPE)     DSIZE (2); a = DPOP; type (DPOP, a); NEXT;
                    CODE (FILL)     DSIZE (3); t = (unit) DPOP; a = DPOP; b = DPOP;
                    RANGE (b, a); i = Object->UnitSeg + (unsigned) b;
                    for (;a > 0L; i++, a--) *i = t; NEXT;
                    CODE (COUNT)    DSIZE (1); DFREE (1); a = DS (1); RANGE (a, 1);
                    DPUSH ((cell) strlen ((char*) Object->UnitSeg +
                                (unsigned) a));
                    NEXT;
                    CODE (NUMBER)   if ((*Base < 2) || (*Base > 36))
                        throw (M4BADRDX);
                    else
                    {
                        DSIZE (2); p = toCstring (DS (2), DS (1));
                        DDROP; DS (1) = str2cell (p, *Base);
                    }
                    NEXT;
                    CODE (OMIT)     DSIZE (1); a = DPOP; b = Vars [VTIB];
                    c = b + Vars [VTIBS];
                    while (b + (*In) < c) {
                        t = fetch (b + (*In));
                        if ((t != (unit) a) || (! t)) break; 
                        else (*In)++;
                    }
                    NEXT;
                    CODE (PARSE)    DSIZE (1); DFREE (1); a = DS (1); b = Vars [VTIB];
                    c = b + Vars [VTIBS]; t = 0;
                    DS (1) = b + (*In); DPUSH ((*In));
                    while (b + (*In) < c) {
                        t = fetch (b + (*In));
                        if ((t == (unit) a) || (! t)) break;
                        else (*In)++;
                    }
                    DS (1) = (*In) - DS (1); 
                    if ((t) && (b + (*In) < c)) (*In)++; NEXT;
                    CODE (CMOVE)    DSIZE (3); a = DPOP; b = DPOP;
                    (void) cmove (DPOP, b, a); NEXT;
                    CODE (SMOVE)    DSIZE (3); c = DPOP; b = DPOP; a = DPOP;
                    VAR  (a); VAR  ((a + c) - 1);
                    UVAR (b); UVAR ((b + c) - 1);
                    (void) smove (a, b, c); NEXT;
                    CODE (PLACE)    DSIZE (3); a = DPOP; b = DPOP;
                    store (cmove (DPOP, a, b), '\0');
                    NEXT;
                    CODE (TRAILING) DSIZE (2);
                    do (DS (1))--;
                    while ((DS (1) >= 0) &&
                            (fetch (DS (2) + DS (1)) == ' '));
                    ++(DS (1)); NEXT;
                    CODE (ACCEPT)   DSIZE (2); DS (2) = Accept (DS (2), DS (1), 'b');
                    DDROP; NEXT;
                    CODE (REFILL)   DFREE (1);
                    DPUSH (Accept (Vars [VTIB], Vars [VTIBS] - 1, 't')
                            == -1 ? F_F : F_T);
                    *In = 0L; NEXT;
                    CODE (THROW)    DSIZE (1); throw (-(DPOP)); NEXT;
                    CODE (CATCH)    DSIZE (1); XT (DS (1)); PushStackFrame ();
                    JUMP (DPOP); NEXT;
                    CODE (CAUGHT)   RSIZE (2); *Handler = (unsigned) RPOP; RDROP;
                    DPUSH (0L); NEXT;
                    CODE (ENVIRON)  DFREE (1); DPUSH (Vars [(unsigned) OPERAND]); NEXT;
                    CODE (SPFETCH)  DFREE (1); a = ToS; DPUSH (a); NEXT; /* don't fix */
                    CODE (RPFETCH)  DFREE (1); DPUSH ((cell) ToRS); NEXT;
                    CODE (RADIX)    *Base = OPERAND; NEXT;
                    CODE (OFFSET)   DSIZE (1); a = DS (1) + OPERAND; CSTR (a);
                    t = (unit) Object->StringSeg [(unsigned) a];
                    DS (1) = (cell) t; NEXT;
                    CODE (PAUSE)    PushStackFrame (); Sleeping = TRUE;
                    CODE (QUIT)     PROGCOUNT = Object->CodeSiz - 1; NEXT;
                    CODE (ARGN)     DFREE (1); DPUSH ((cell) ArgN); NEXT;
                    CODE (SQUOTE)   DFREE (2);
                    a = toPAD (Object->StringSeg + (unsigned) OPERAND);
                    DPUSH (a); NEXT;
                    CODE (ARGS)     DSIZE (1); DFREE (1); a = DPOP;
                    if ((a < 0) || (a >= ArgN))
                        throw (M4BADSTR);
                    else
                    {
                        a = toPAD (ArgS [(unsigned) a]);
                        DPUSH (a);
                    }
                    NEXT;
                    CODE (USE)      DSIZE (1); a = DPOP; DEV (a); ODEV (a);
                    if (Stream [(int) a].Mode & F4_READ)
                    {
                        Channel [CIN] = Stream [(int) a].Device;
                        Vars [VCIN] = a;
                    }
                    if (Stream [(int) a].Mode & F4_WRITE)
                    {
                        Channel [COUT] = Stream [(int) a].Device;
                        Vars [VCOUT] = a;
                    }
                    NEXT;
                    CODE (FCLOSE)   DSIZE (1); CloseStream ((int) DPOP, M4IOERR); NEXT;
                    CODE (FSYNC)    fflush (Channel [COUT]); NEXT;
                    CODE (FTELL)    DSIZE (1); a = DPOP; UDEV (a); ODEV (a); SDEV (a);
                    b = (cell) ftell (Stream [(int) a].Device);
                    if (b == -1L) throw (M4IOERR); else DPUSH (b);
                    NEXT;
                    CODE (SEMTRAN)     {
                        int key;
                        int sid;
                        extern int errno;

                        DSIZE(1);
                        key = DPOP;
                        if(key < 0) {
                            DPUSH(-1);
                        } else {
                            sid = semget(key,1,0666 | IPC_CREAT);
                            DPUSH(sid);
                        }
                    }
                    NEXT;
                    CODE (SETSEMVALUE) {
                        int sid;
                        union semun arg;

                        DSIZE(2);
                        sid = DPOP;
                        arg.val = DPOP;

                        DPUSH(semctl(sid,0,SETVAL,arg));

                    }
                    NEXT;
                    CODE (GETSEMVALUE) {
                        int sid;

                        DSIZE(1);
                        sid = DPOP;
                        DPUSH(semctl(sid,0,GETVAL));
                    }
                    NEXT;
                    CODE(GETSEM) {
                        int sid;
                        int res;
                        DSIZE(1);

                        sid = DPOP;
                        res=semcall(sid, -1);
                        DPUSH(res);
                    }
                    NEXT;
                    CODE(RELSEM) {
                        int sid;

                        DSIZE(1);
                        sid = DPOP;
                        DPUSH(semcall(sid, 1));
                    }
                    NEXT;
                    CODE(RMSEM) {
                        int sid;

                        DSIZE(1);
                        sid = DPOP;

                        DPUSH(semctl(sid, 0, IPC_RMID));

                    }
                    NEXT;
                    CODE(SHMGET) {
                        int shm_id;
                        int key;
                        int size;
                        int flags;

                        DSIZE(3);
                        flags = DPOP;
                        size = DPOP;
                        key = DPOP;
                        shm_id = shmget(key, size, flags);

                        DPUSH(shm_id);
                    }
                    NEXT;
                    CODE(SHMAT) {
                        long ptr;
                        long shm_id;

                        DSIZE(1);
                        shm_id = DPOP;
                        ptr = (long) shmat(shm_id,0, SHM_RND);
                        DPUSH(ptr);
                    }
                    NEXT;
                    CODE(SHMDT) {
                        long shm_id;
                        DSIZE(1);
                        shm_id = DPOP;
                        if( 0 == shmdt(shm_id) ) {
                            DPUSH(-1);
                        } else {
                            DPUSH(0);
                        }
                    }
                    NEXT;
                    CODE(SHMRM) {
                        long shm_id;
                        int res;
                        struct shmid_ds buf;

                        DSIZE(1);
                        shm_id = DPOP;
                        res = shmctl(shm_id,IPC_STAT, &buf);
                        if( 0 == res ) {
                            res = shmctl(shm_id,IPC_RMID,&buf);
                        }
                        DPUSH( res );
                    }
                    NEXT;
                    CODE(MEMCAT) {
                        unsigned char *ptr;
                        DSIZE(1);

                        ptr=(unsigned char *)DPOP;

                        DPUSH( *ptr);
                    }
                    NEXT;
                    CODE(MEMCSTORE) {
                        unsigned char *ptr;
                        unsigned char c;

                        DSIZE(2);
                        ptr=(unsigned char *)DPOP;
                        c=DPOP;

                        *ptr=c;

                    }
                    NEXT;
                    CODE(MEMWAT) {
                        unsigned short *ptr;

                        DSIZE(1);
                        ptr = (unsigned short *)DPOP;
                        DPUSH(*ptr);
                    }
                    NEXT;
                    CODE(MEMWSTORE) {
                        unsigned short *ptr;
                        unsigned short c;

                        DSIZE(2);
                        ptr=(unsigned short *)DPOP;
                        c=(unsigned short)DPOP;
                        *ptr = c;
                    }
                    NEXT;
                    CODE(MEMAT) {
                        unsigned int *ptr;

                        DSIZE(1);

                        ptr = (unsigned int *)DPOP;
                        DPUSH(*ptr);
                    }
                    NEXT;
                    CODE(MEMSTORE) {
                        unsigned int *ptr;
                        unsigned int c;

                        DSIZE(2);
                        ptr=(unsigned int *)DPOP;
                        c=(unsigned int)DPOP;
                        *ptr = c;
                    }
                    NEXT;

                    CODE (FSEEK)    DSIZE (2); a = DPOP; b = DPOP;
                    UDEV (a); ODEV (a); SDEV (a);
                    c = b < 0L ? SEEK_END : SEEK_SET;
                    if (b == CELL_MIN) b = 0L;
                    a = (cell) fseek (Stream [(int) a].Device,
                            (long) b, (int) c) == 0 ? F_F : F_T;
                    DPUSH (a); NEXT;
                    CODE (FOPEN)    DSIZE (3); a = DPOP; b = DPOP; c = DPOP;
                    p = toCstring (c, b);
                    a &= (F4_READ|F4_WRITE|F4_APPND|F4_PIPE);
                    b = OpenStream (p, (int) a); DPUSH (b); NEXT;
                    CODE (ENVFETCH) DSIZE (2); a = DPOP;
                    p = getenv (toCstring (DPOP, a));
                    if (p == NULL)
                    {
                        DPUSH (0); DPUSH (0);
                    }
                    else
                    {
                        a = toPAD (p); DPUSH (a);
                    }
                    NEXT;
                    CODE (DELFILE)  DSIZE (2); p = toCstring (DS (2), DS (1)); DDROP;
#ifdef WEB4TH
                    DS (1) = F_T; NEXT;
#else
                    DS (1) = unlink (p) == 0 ? F_F : F_T; NEXT;
#endif
                    UNKNOWN         throw (M4BADOBJ); NEXT;
                }
    }
    /* close files forced */
    for (a = (cell) (COUT + 1); a < MAXDEVS; a++)
        CloseStream ((int) a,  M4NOERRS);

    a = Vars [VOUT];                     /* get result from OUT */

    if (Sleeping == FALSE)               /* if not PAUSEing */
    {                                 /* free environment */
        free (Object->UnitSeg); free (Object->CellSeg);
        Object->UnitSeg = NULL; Object->CellSeg = NULL;
        Object->Offset = 0;
    }

    if (Object->ErrNo) return (CELL_MIN);
    else return (a);                     /* return value */
}
