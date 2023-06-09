CC = gcc
LFLAGS = -lncurses

SRCDIR = src
INCDIR = include
BINDIR = bin

SOURCES = $(wildcard $(SRCDIR)/*.c)
HEADERS = $(wildcard $(INCDIR)/*.h)
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(BINDIR)/%.o, $(SOURCES))
EXECUTABLE = $(BINDIR)/myprogram

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LFLAGS)

$(BINDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	$(CC) -c $< -o $@

run: $(EXECUTABLE)
	$(EXECUTABLE)

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

CC = gcc
LFLAGS = -lncurses

SRCDIR = src
INCDIR = include
BINDIR = bin

SOURCES = $(wildcard $(SRCDIR)/*.c)
HEADERS = $(wildcard $(INCDIR)/*.h)
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(BINDIR)/%.o, $(SOURCES))
EXECUTABLE = $(BINDIR)/myprogram

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LFLAGS)

$(BINDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	$(CC) -c $< -o $@

run: 
	$(EXECUTABLE)
	$(EXECUTABLE)

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

crun:
	rm -f $(OBJECTS) $(EXECUTABLE)
	$(EXECUTABLE)
	$(EXECUTABLE)

runc:
	$(EXECUTABLE)
	$(EXECUTABLE)
	rm -f $(OBJECTS) $(EXECUTABLE)



