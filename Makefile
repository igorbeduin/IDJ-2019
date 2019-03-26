CC=g++
EXECNAME = Play.out
SRCDIR = src
INCDIR = include
BINDIR = bin
OBJDIR = object
LFLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
CFLAGS = -std=c++11 -g -Wall -Wextra

BIN = $(BINDIR)/$(EXECNAME)
SRC = $(wildcard $(SRCDIR)/*.cpp)
OBJ = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRC))

all: $(OBJ)
	$(CC) $(OBJ) $(LFLAGS)  $(CFLAGS) -o $(EXECNAME)

%.o: $(patsubst $(OBJDIR)/%.o, $(SRCDIR)/%.cpp, $@)
	$(CC) -c $(CFLAGS) $(patsubst $(OBJDIR)/%.o, $(SRCDIR)/%.cpp, $@) -o $@

clean:
	rm -f $(OBJ) *~
