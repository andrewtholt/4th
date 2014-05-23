# GNU Make - Rebuilding .c and .h sources
# Copyright 2011,2014 Hans Bezemer

CC=gcc
CFLAGS=-fsigned-char -Wall -O3 -s
LDLIBS=-l4th
LDFLAGS=-s

ifdef STAGEDIR
  FOURTH=$(STAGEDIR)/stage
else
  FOURTH=4th
endif

%.c : %.4th
	$(FOURTH) cgq $< $@

%.hx : %.4th
	$(FOURTH) csq $< $@

%.c : %.hx
	$(FOURTH) lgq $< $@

%.4th : %.4pp
	pp4th -o $@ $<

%.h : %.hx
	$(FOURTH) cxq bin2h.4th EmbeddedHX $< $@

.INTERMEDIATE: teditor.4th zeditor.4th edit.4th pp.4th pp4th.hx editor.hx

all:	pp4th.h mon.h editor.h teditor.h zeditor.h

edit.4th: editor.4th
	sed -e '16 s/false/true/' -e '17 s/true/false/' -e '18 s/small/large/' $< > $@

editor.hx: edit.4th
	$(FOURTH) csq $< $@

pp.4th: pp4th.4th
	sed -e '16 s/false/true/' $< > $@

pp4th.hx: pp.4th
	$(FOURTH) csq $< $@

teditor.4th: editor.4th
	sed -e '16 s/false/true/' -e '17 s/true/false/' -e '18 s/small/medium/' $< > $@

zeditor.4th: editor.4th
	sed -e '16 s/false/true/' -e '17 s/true/false/' -e '18 s/small/huge/' -e '19 s/64/32/' -e '20 s/16/8/' $< > $@

mostlyclean:
	-rm teditor.4th teditor.hx zeditor.4th zeditor.hx edit.4th editor.hx pp.4th pp4th.hx

clean: mostlyclean
	-rm pp4th.h mon.h editor.h teditor.h zeditor.h

.SUFFIXES:
.SUFFIXES: .c .hx .h .4th .o
