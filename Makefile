# 140143882_T1

# Compilador
COMPILER = g++

# Play
PLAY = blabla

# Comando para remover pastas
RMDIR = rm -rdf

# Comando para remover arquivos
RM = rm -f

# Bibliotecas
LIBS = -lstdc++ -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm 

# Diretivas de compilacao
FLAGS = -std=c++11 -Wall -lstdc++

# Paths
INC_PATH = include
SRC_PATH = src

# Nome do executavel
# EXEC = PLAY

# CPP_FILES = $(wildcard $(SRC_PATH)/*.cpp)

# INC_FILES = $(wildcard $(INC_PATH)/*.h)

all: EXEC

EXEC: Main.o Game.o Music.o Sprite.o State.o
	$(COMPILER) Main.o Game.o Music.o Sprite.o State.o -o $(PLAY)

Main.o: Main.cpp
	$(COMPILER) $(FLAGS) Main.cpp

Game.o: src/Game.cpp
	$(COMPILER) $(FLAGS) src/Game.cpp

Sprite.o: src/Sprite.cpp
	$(COMPILER) $(FLAGS) src/Sprite.cpp

State.o: src/State.cpp
	$(COMPILER) $(FLAGS) src/State.cpp

Music.o: src/Music.cpp
	$(COMPILER) $(FLAGS) src/Music.cpp







