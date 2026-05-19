CC      = gcc
YACC    = yacc

CFLAGS  = -Wall

all: stretch calc

stretch: stretch.y
	$(YACC) -o stretch.c stretch.y
	$(CC) $(CFLAGS) -o stretch stretch.c
	rm -f stretch.c

calc: calc.y
	$(YACC) -o calc.c calc.y
	$(CC) $(CFLAGS) -o calc calc.c
	rm -f calc.c

clean:
	rm -f stretch calc stretch.c calc.c y.tab.c y.tab.h
