CC=gcc
CFLAGS=-c -Wall
LDFLAGS=
DFLAGS=-g -D DEBUG
SOURCES=stack.c pointer.c board.c main.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=befungeec

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

debug:
	@$(MAKE) $(MFLAGS) CFLAGS="$(CFLAGS) $(DFLAGS)"

clean:
	rm -f $(OBJECTS)
	rm -f $(EXECUTABLE)

distclean: clean
	rm -f *~

.PHONY: clean distclean debug
