CC=gcc
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.c stack.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=befungeec

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(DEBUG) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $(DEBUG) $< -o $@

debug:
	@$(MAKE) $(MFLAGS) $(MAKEFILE) DEBUG="-g -D DEBUG"

clean:
	rm -f $(OBJECTS)
	rm -f $(EXECUTABLE)

distclean: clean
	rm -f *~

.PHONY: clean distclean debug
