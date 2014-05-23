# 4tH Makefile (c) 1997 G.B. Stott
#
# This is for use with the linux operating system. Do the following:
#
# 1. Check the variables below which may need to be changed.
#
# 2. Type `make' to build everything.
#
# 3. As superuser, type `make install' to install the programs and library.
#
# 4. Type `make clean'. This restores the directory to the initial state.
#

# The following variables may need to be changed

LIBRARIES=/usr/lib
INCLUDES=/usr/include
BINARIES=/usr/local/bin
MANDIR=/usr/share/man
DOCDIR=/usr/share/doc
SOURCES=../4th
CFLAGS= -DUNIX -fsigned-char -Wall -O3 -s

# Cross compilation variables
LD=$(CROSS)ld
AR=$(CROSS)ar
CC=$(CROSS)gcc

BYTECODES = mon.h editor.h zeditor.h teditor.h pp4th.h

OBJ4TH = errs_4th.o save_4th.o load_4th.o free_4th.o comp_4th.o \
	name_4th.o dump_4th.o exec_4th.o open_4th.o cgen_4th.o \
	str2cell.o

.INTERMEDIATE: stage stage.c

all: 4th 4tsh pp4th lib4th

ifdef SHARED
MAJOR=3
MINOR=62
MICRO=2
SHARED_LIB=lib4th.so.$(MAJOR).$(MINOR).$(MICRO)
endif

ifdef STATIC
STATIC_LIB=lib4th.a
else
ifndef SHARED
STATIC_LIB=lib4th.a
endif
endif

lib4th: $(SHARED_LIB) $(STATIC_LIB)

lib4th.a: $(OBJ4TH)
	$(AR) r $@ $(OBJ4TH)

$(SHARED_LIB): $(OBJ4TH)
	$(CC) -shared -o $@ $(OBJ4TH) -Wl,-soname,lib4th.so.$(MAJOR)
	ln -sf $@ lib4th.so.$(MAJOR)
	ln -sf $@ lib4th.so

stage.c: 4th.c
	cp stage.h editor.h
	cp $< $@

stage: stage.o lib4th
	$(CC) $(CFLAGS) -I. -o $@ $< -L. -l4th

4th.o: generated
4tsh.o: generated
pp4th.o: generated

4th: 4th.o lib4th
	$(CC) $(CFLAGS) -I. -o $@ $< -L. -l4th

4tsh: 4tsh.o lib4th
	$(CC) $(CFLAGS) -I. -o $@ $< -L. -l4th

pp4th: pp4th.o lib4th
	$(CC) $(CFLAGS) -I. -o $@ $< -L. -l4th

generated: $(BYTECODES)

pp4th.h: stage
	$(MAKE) -C $(SOURCES) STAGEDIR=$(CURDIR) $@
	mv $(SOURCES)/$@ .

editor.h: stage
	$(MAKE) -C $(SOURCES) STAGEDIR=$(CURDIR) $@
	mv $(SOURCES)/$@ .

zeditor.h: stage
	$(MAKE) -C $(SOURCES) STAGEDIR=$(CURDIR) $@
	mv $(SOURCES)/$@ .

teditor.h: stage
	$(MAKE) -C $(SOURCES) STAGEDIR=$(CURDIR) $@
	mv $(SOURCES)/$@ .

mon.h: stage
	$(MAKE) -C $(SOURCES) STAGEDIR=$(CURDIR) $@
	mv $(SOURCES)/$@ .

mostlyclean:
	-rm *.o stage stage.c editor.h zeditor.h teditor.h mon.h pp4th.h
	$(MAKE) -C $(SOURCES) clean

clean: mostlyclean
	-rm -f lib4th.{a,so*}
	-rm 4th 4tsh pp4th

# Superuser privileges will probably be required for the rest

libinstall: lib4th
	cp $(SHARED_LIB) $(STATIC_LIB) $(LIBRARIES)
ifdef SHARED
	ln -sf $(SHARED_LIB) $(LIBRARIES)/lib4th.so.$(MAJOR)
	ln -sf $(SHARED_LIB) $(LIBRARIES)/lib4th.so
endif

mostlyinstall: libinstall all
	cp 4th 4tsh pp4th $(BINARIES)

install: mostlyinstall
	install -Dm644 ../documentation/4th.1 $(MANDIR)/man1/4th.1
	install -Dm644 ../documentation/4tHmanual.txt $(DOCDIR)/4th/

uninstall:
	-rm -f $(LIBRARIES)/lib4th.{a,so*}
	-rm $(BINARIES)/4th $(BINARIES)/4tsh $(BINARIES)/pp4th

.SUFFIXES:
.SUFFIXES: .c .o
