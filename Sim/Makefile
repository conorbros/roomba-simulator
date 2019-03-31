IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR =../lib

LIBS=-lm

_DEPS = gui.h
DEPS = $(patsubst %, $(ODIR)/%,$(_OBJ))

_OBJ = main.o gui.o


%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

a1_n10009671: main.o gui.o
		$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
