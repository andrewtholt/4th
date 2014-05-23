/*
+-------+-----------------+------+-----------------+-------+-----------------+
|Program| 4TSH.C          |Module| None            |Library| None            |
+-------+-----------------+------+-----------------+-------+----------+------+
|HISTORY                                           |    Programmer    | Date |
+--------------------------------------------------+------------------+------+
| GCC 3.4.5 version                                | J.L. Bezemer     |010207|
+--------------------------------------------------+------------------+------+
|MODIFICATION LOG                                  |    Programmer    | Date |
+--------------------------------------------------+------------------+------+
| Added error messages to KillTask()               | J.L. Bezemer     |020207|
| Monitor now passes its value by the stack        | J.L. Bezemer     |060207|
| Redesigned Interpret(), added SaveTask()         | J.L. Bezemer     |070207|
| Added write_4th(), SeeTask(); changed SaveTask() | J.L. Bezemer     |080207|
| Made it compile properly under Turbo C           | J.L. Bezemer     |141207|
| Added output buffer flush                        | J.L. Bezemer     |171207|
| StatusTask() added; added CLI arguments          | J.L. Bezemer     |150108|
| Fixed silly Turbo C error                        | J.L. Bezemer     |190108|
| Added K&R prototypes                             | J.L. Bezemer     |190108|
| Rewrote most of the program                      | J.L. Bezemer     |040509|
| Optimized it by removing functions and checks    | J.L. Bezemer     |050509|
| Rewrote MultiTasker(), removed another check     | J.L. Bezemer     |060509|
| Fixed K&R prototypes with function pointers      | J.L. Bezemer     |070509|
| Fixed LoadTask() prototype, removed parameter    | J.L. Bezemer     |080509|
| Fixed bug in ExecuteSys() when monitor dies      | J.L. Bezemer     |040411|
| Applied Coherent patches                         | J.L. Bezemer     |020112|
| Applied Coherent patch WRITETEXT                 | J.L. Bezemer     |290312|
+--------------------------------------------------+------------------+------+
|REMARKS                                           |    Programmer    | Date |
+--------------------------------------------------+------------------+------+
| Demonstration for 4th toolkit                    | J.L. Bezemer     |010207|
+--------------------------------------------------+------------------+------+

  Copyright (C) 2007, 2012 J.L. Bezemer

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

#include "4th.h"
#include "cmds_4th.h"
#include "mon.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USTACKSIZ   64                 /* 4tH user stack size */
#define MAXNAME    128                 /* maximum job name length */
#define MAXDUMP     16                 /* no. lines on decompile */
#define MAXJOBS     64                 /* maximum number of jobs */
#define INIT         0                 /* first job */
#define KILLED      -1                 /* not a valid task */
                                       /* -TASK STATUS- */
#define SSLEEP 0                       /* sleeping task */
#define SNORM  0                       /* normal task */
#define SAWAKE 1                       /* awake task */
#define SKILL  2                       /* killed task */
#define SSYST  4                       /* system task */
#define SUSER  (SAWAKE|SNORM)
#define SINIT  (SAWAKE|SSYST)
                                       /* -MONITOR COMMANDS- */
#define JLOAD  0
#define JCOMP  1
#define JPAUSE 2
#define JRUN   3
#define JAWAKE 4
#define JSLEEP 5
#define JKILL  6
#define JTASKS 7
#define JSAVE  8
#define JWRITE 9
#define JSTAT 10
#define JHALT 11
#define JBOOT 12
#define JPID  13
#define JSEE  14
                                       /* pointer calculator macros */
#define MK_CP(a,b) ((a)->CellSeg+STACKSIZ+SYS4TH+((int)b))
#define MK_UP(a,b) ((a)->UnitSeg+((int)b))
#define CHECK(a)   ((a)!=(INT_MIN))

#ifdef ARCHAIC
#define WRITETEXT "w"
#else
#define WRITETEXT "wt"
#endif

/*
This program uses a stack to store its applets. Every element
of this stack is called a SLOT. Every new applet is stored in
the topmost slot. A slot with an active applet is called a JOB.
Every job is assigned a pid. A job identified by a pid is a TASK.
The user of the monitor works with tasks, the multitasker with
jobs. If a job is killed, the topmost job is moved to the free
slot while retaining its pid.
*/

typedef struct {
   Hcode *Job;                         /* pointer to Hcode */
   char   Name [MAXNAME];              /* name of job */
   unit   Stat;                        /* status of job */
   int    Id;                          /* process id */
} Job;

Job Process [MAXJOBS];                 /* job table */
int ToS = INIT;                        /* top of job stack */

/*
This function gets a value from the 4tH user stack
*/

#ifndef ARCHAIC
  int from_4th (Hcode* Object, cell stack)
#else
  int from_4th (Object, stack) Hcode* Object; cell stack;
#endif

{
  cell *sp = MK_CP (Object, stack);

  return (*sp > stack ? (int) *(MK_CP (Object, (*sp)--)) : INT_MIN);
}


/*
This function puts a value on the 4tH user stack.
*/

#ifndef ARCHAIC
  void to_4th (Hcode* Object, cell stack, int item)
#else
  to_4th (Object, stack, item) Hcode* Object; cell stack; int item;
#endif

{
  cell *sp = MK_CP (Object, stack);

  if (*sp < (stack + (USTACKSIZ-1))) *(MK_CP (Object, ++(*sp))) = (cell) item;
}


/*
This function is just a wrapper to create a similar protoype to load_4th().
It returns an Hcode pointer or NULL if an error occurs.
*/

#ifndef ARCHAIC
  Hcode* source_4th (char* filename)
#else
  Hcode* source_4th (filename) char* filename;
#endif

{
  return (comp_4th (open_4th (filename)));
}


/*
This function is just a wrapper to create a similar protoype to save_4th().
*/

#ifndef ARCHAIC
  void write_4th (Hcode* Object, char* filename)
#else
  write_4th (Object, filename) Hcode* Object; char* filename;
#endif

{
  FILE *COut;

  if ((COut = fopen (filename, WRITETEXT)) != NULL)
    {
      cgen_4th (Object, COut);
      fclose (COut);
    }
}


/*
This function converts the pid to a job. It returns ToS if not found.
*/

#ifndef ARCHAIC
  int ToJob (int pid) 
#else
  int ToJob (pid) int pid;
#endif

{
  int job = INIT;
                                       /* try to find a job with this pid */ 
  while ((job < ToS) && (Process [job].Id != pid)) job++;
  return (job);
}


/*
This function moves a job down to an open slot.
*/

#ifndef ARCHAIC
  void MoveJob (int job)
#else
  MoveJob (job) int job;
#endif

{                                      /* copy the fields from the top job */
  strcpy (Process [job].Name, Process [ToS].Name);
  Process [job].Job  = Process [ToS].Job;
  Process [job].Stat = Process [ToS].Stat;
  Process [job].Id   = Process [ToS].Id;
}


/*
This function checks whether it is a valid task and AWAKEs it or
puts it to SLEEP.
*/

#ifndef ARCHAIC
  void AwakeTask (int pid, int Awake)
#else
  AwakeTask (pid, Awake) int pid; int Awake;
#endif

{
  int job = ToJob (pid);               /* convert pid to job */

  if (job < ToS)                       /* if it is a valid job */
     {                                 /* change the status */
       if (Awake) Process [job].Stat |= SAWAKE;
       else Process [job].Stat &= ~(SAWAKE);
     }
}


/*
This function checks whether it is a valid task and subsequently kills it.
*/

#ifndef ARCHAIC
  void KillTask (int pid)
#else
  KillTask (pid) int pid;
#endif

{
  int job = ToJob (pid);               /* convert pid to job */

  if (job < ToS)                       /* if it is a valid job */
     {                                 /* free the Hcode */
       printf ("Task %d terminated: %s\n", Process [job].Id,
               errs_4th [Process [job].Job->ErrNo]);
       free_4th (Process [job].Job);   /* decrement ToS */
       if (job < --ToS) MoveJob (job); /* do we have to move a job? */
     }
}


/*
This routine adds a task to the process space. It returns the job
if successful.
*/

#ifndef ARCHAIC
  int AddTask (Hcode* Prog, char* Name, char Mode)
#else
  int AddTask (Prog, Name, Mode) Hcode* Prog; char* Name; char Mode;
#endif

{
  static int TaskId = 0;

  if ((Prog) && (ToS < MAXJOBS))    /* if empty slot found */
     {                              /* add the job name */
       Process [ToS].Name [MAXNAME - 1] = '\0';
       strncpy (Process [ToS].Name, Name, MAXNAME - 1);
       Process [ToS].Job = Prog;    /* add the task */
       Process [ToS].Stat = Mode;   /* set the status */
       Process [ToS].Id = (TaskId++ & INT_MAX);  
       printf ("Task %d started\n", Process [ToS].Id);
       return (ToS++);              /* increment top of stack */
     }
  return (ToS);                     /* return always top of stack */
}


/*
This function loads or compiles to bytecode. The resulting code is added as
a task to the process space. If successful, it leaves the pid on
the 4tH user stack.
*/

#ifndef ARCHAIC
  void LoadTask (Hcode* (*loader) (char *name), Hcode* obj, cell stk)
#else
  LoadTask (loader, obj, stk) Hcode* (*loader) (); Hcode* obj; cell stk;
#endif

{
  int a;
  char *name;                          /* program name */

   if (CHECK (a = from_4th (obj, stk)))
      {                                /* if there is a value on the stack */
        name = (char*) MK_UP (obj, a); /* make a pointer to the name */
        a = AddTask ((*loader) (name), name, SUSER);
        to_4th (obj, stk, a < ToS ? Process [a].Id : KILLED);
      }                                /* load job and leave pid on stack */
   else to_4th (obj, stk, KILLED);     /* leave "killed" pid on error */
}


/*
This function will save a task to disk. It gets the filename and
pid before calling save_4th(). Like save_4th() it returns nothing.
*/

#ifndef ARCHAIC
  void SaveTask (void (*saver) (Hcode* obj, char* name), Hcode* obj, cell stk)
#else
  void SaveTask (saver, obj, stk) void (*saver) (); Hcode* obj; cell stk;
#endif

{
  int a;
  char *name;                          /* program name */

   if (CHECK (a = from_4th (obj, stk)))
      {                                /* if there is a value on the stack */
        name = (char*) MK_UP (obj, a); /* get the filename and the job */
        if (CHECK (a = from_4th (obj, stk)))
           if ((a = ToJob (a)) < ToS) (*saver) (Process [a].Job, name);
      }                                /* save it to disk */
}


/*
This function decompiles the first MAXDUMP bytecodes of a job, beginning
with an address issued by the user.
*/

#ifndef ARCHAIC
  void SeeTask (Hcode* obj, cell stk)
#else
  SeeTask (obj, stk) Hcode* obj; cell stk;
#endif

{
  int a, b;
                                        /* get linenumber */
  if (CHECK (a = from_4th (obj, stk)))  /* get pid */
     if (CHECK (b = from_4th (obj, stk)))
        if ((b = ToJob (b)) < ToS)      /* convert, if valid decompile */
           dump_4th (Process [b].Job, stdout, a, a + MAXDUMP);
}


/*
This function interprets a command that has been issued by the monitor.
It uses the 4tH user stack to fetch its parameters.
*/

#ifndef ARCHAIC
  int Interpret (int cmd, int job, Hcode* obj, cell stk)
#else
  int Interpret (cmd, job, obj, stk) int cmd; int job; Hcode* obj; cell stk;
#endif

{
  int  a;                              /* temporary variable */
  int next = job;                      /* next job to execute */
                                       /* (default is this monitor) */
  switch (cmd)                         /* select proper command */
  {                                    /* note JHALT executes JPAUSE */
    case (JHALT):  for (a = INIT; a < ToS; a++)
                       AwakeTask (Process [a].Id, FALSE);
    case (JPAUSE): next = ++job;       /* proceed with JPAUSE */
                   break;              /* give control to next job */
    case (JBOOT):  a = AddTask (fetch_4th (EmbeddedHX), "(monitor)", SINIT);
                   if (a < ToS) next = a;
                   break;              /* boot a new monitor */
    case (JRUN):   if (CHECK (a = from_4th (obj, stk)))
                      {                /* get pid from the stack */
                        AwakeTask (a, TRUE);
                        next = ToJob (a);
                      }                /* convert pid to job */
                   break;              /* awake task and give control */
    case (JAWAKE): if (CHECK (a = from_4th (obj, stk)))
                      AwakeTask (a, TRUE);
                   break;              /* set status to awake */
    case (JSLEEP): if (CHECK (a = from_4th (obj, stk)))
                      AwakeTask (a, FALSE);
                      if (Process [job].Id == a) next = ++job;
                   break;              /* are we going to sleep? */
    case (JKILL):  if (CHECK (a = from_4th (obj, stk)))
                      {                /* are we killing ourself? */
                        if (Process [job].Id == a) next = ++job;
                        if (job == (ToS - 1)) next = a;
                        KillTask (a);  /* are we being moved? */
                      }                /* kill the task */
                   break;              /* get the pid from the stack */
    case (JSTAT):  if (CHECK (a = from_4th (obj, stk)))
                      {
                        a = ToJob (a); /* convert pid to job */
                        to_4th (obj, stk, a < ToS ?
                                Process [a].Stat & SAWAKE : SKILL);
                      }                /* assume bad job is killed */
                   break;              /* return the status */
    case (JTASKS): for (a = INIT; a < ToS; a++)
                        printf ("%s %d: %s\n", Process [a].Stat & SAWAKE ?
                                "Awake" : "Sleep", Process [a].Id,
                                Process [a].Name);
                   break;              /* list all tasks */
    case (JLOAD):  LoadTask (load_4th, obj, stk); break;
    case (JCOMP):  LoadTask (source_4th, obj, stk); break;
    case (JSAVE):  SaveTask (save_4th, obj, stk); break;
    case (JWRITE): SaveTask (write_4th, obj, stk); break;
    case (JSEE):   SeeTask (obj, stk); break;
    case (JPID):   to_4th (obj, stk, Process [job].Id); break;
    default:       break;              /* ignore invalid commands */
  }
  return (next);
}


/*
This function executes the command that has been returned by a monitor
applet. It returns a job.
*/

#ifndef ARCHAIC
  int ExecuteSys (int job, int argn, char** args)
#else
  int ExecuteSys (job, argn, args) int job; int argn; char** args;
#endif

{
  int cmd;                             /* pointer to the command variable */
  int next = job;                      /* job returned by monitor */
  cell stk;                            /* 4tH stack pointer */
                                       /* start the monitor */
  while (next == job)
    {                                  /* if still current job and awake */
      stk = exec_4th (Process [job].Job, argn, args, 0);
      fflush (stdout);                 /* get the user stack address */
      if (Process [job].Job->Offset == 0) 
         {                             /* remove monitor when terminated */
           KillTask (Process [job].Id); return (++job);
         }                             /* return next job */

      if (CHECK (cmd = from_4th (Process [job].Job, stk)))
         next = Interpret (cmd, job, Process [job].Job, stk);
      else next = ++job;               /* get the next command */
    }                                  /* if not valid go to next job */

  return (next);
}


/*
This function runs any user defined job. If the job has finished, it is
killed explicitly. It returns the next job.
*/

#ifndef ARCHAIC
  int ExecuteUser (int job)
#else
  int ExecuteUser (job) int job;
#endif

{                                      /* execute and flush output buffer */
  (void) exec_4th (Process [job].Job, 0, NULL, 0);
  fflush (stdout);                     /* remove job when terminated */
  if (Process [job].Job->Offset == 0) KillTask (Process [job].Id);
  return (++job);                      /* return next job */
}


/*
This is the true multitasker. It keeps on looping through the jobs until
there are no jobs (awake) anymore.
*/

#ifndef ARCHAIC
  void MultiTasker (int argn, char** args)
#else
  MultiTasker (argn, args) int argn; char** args;
#endif

{
  int job = INIT;                      /* start the scheduler */
  int awake = 0;                       /* number of sleeping jobs */

  while (ToS && ((job < ToS) || (awake)))
    {                                  /* loop until no more jobs (awake) */
      if (job >= ToS)  job = INIT;     /* wrap scheduler around if needed */
      if (job == INIT) awake = 0;      /* reset awake jobs counter on start */
      if (Process [job].Stat & SAWAKE)
         {                             /* if awake job has been found */
           awake++;                    /* register awake job */
           job = Process [job].Stat & SSYST ?
                 ExecuteSys  (job, argn, args) : ExecuteUser (job);
         }                             /* execute either system or user */
      else job++;                      /* sleeping job, so skip */
    }

  while (ToS > INIT) KillTask (Process [INIT].Id);
}                                      /* kill all jobs */


/*
This is the main routine. It clears the job table, loads the monitor and
starts the multitasker. Finally, it returns success.
*/

#ifndef ARCHAIC
  int main (int argc, char** argv)
#else
  int main (argc, argv) int argc; char** argv;
#endif

{                                      /* start the monitor */
  if (AddTask (fetch_4th (EmbeddedHX), "(monitor)", SINIT) < ToS)
     MultiTasker (argc - 1, argv + 1);
                                       /* start the multitasker */
  return (EXIT_SUCCESS);               /* return success */
}
