Read me first                  4tH version 3.62.2, 2014-02-22


4tH is basic framework for creating application specific scripting
languages. It is a library of functions centered around a virtual
machine, which guarantees high performance, ease of use and low overhead.

But in the meanwhile 4tH has acquired a reputation as an educational
tool. Its simplicity makes it perfectly suited to learn Forth, from which
it has been derived.

This package is an attempt to suit both audiences. It contains
instructions how to modify the package in order to fit your own
requirements. 4tH in its current form is a calculator for simple teletype
applications. All its basic building blocks (compiler, interpreter,
decompiler, loader and saver) can be called with a single line of C. No
initialization necessary.

On the other hand there are simple instructions to compile the example
applications, which allows you to compile and run very large 4tH programs
(80386 or better). We also included a host of sample applications, like
an adventure game, a line-editor and a Forth calculator.

It is impossible to answer every thinkable question with documentation.
NEVER EMAIL THE PEOPLE WHOSE SITE YOU GOT THIS FROM! THEY DON'T KNOW
EITHER! INSTEAD, MAIL TO:

      the.beez.speaks@gmail.com

Or visit our website:

      http://thebeez.home.xs4all.nl/4tH/

We welcome all feedback, so don't hesitate if something is not completely
clear to you or if you want to make a point. This feedback has made 4tH
into what it is today and we want to thank all who took the effort to
think and comment on 4tH.

Makefiles
=========
There are several different Makefiles for different platforms. The default is
Linux. If that one doesn't work for you, you can resort to the following
variants:

Makefile.UNX - a very vanilla Makefile, most likely to work on a host of
               different *Nix platforms.

Makefile.BSD - a vanilla Makefile, targetted at BSD-like platforms like HP-UX,
               NeXT, etc.

Makefile.OSX - a Makefile for the Apple OS/X platform.

Makefile.COH - a Makefile for the Coherent 4.x platform.

Makefile.NAN - a Makefile to the Linux Ben Nanonote platform.

Makefile.W32 - a Makefile (for cross compilation) using the MinGW compiler for
               the MS-Windows(32) platform.

Makefile.DOS - a Makefile (for cross compilation) using the DJGPP compiler for
               the MS-DOS platform.

64-bit architectures
====================
If you happen to compile 4tH on 64-bit architectures, you will find that some
functionalities don't work as advertised. In that case, perform the following
procedure:

      cd sources
      cp include/* .
      make clean
      make

This will make the executables fit for your 64-bit machine.

                          --- DOCUMENT ENDS HERE ---

                         Copyright 1997,2014 J.L. Bezemer
