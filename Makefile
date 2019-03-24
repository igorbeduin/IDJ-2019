# 140143882_T1

# Compilador
COMPILER = g++
# COMPILER = /usr/local/bin/g++-8

# Nome do executavel
EXEC = blabla.out

# Comando para remover pastas
RMDIR = rm -rdf

# Comando para remover arquivos
RM = rm -f

# Bibliotecas
LIBS = -lstdc++ -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm
#LIBS = -lm -lstdc++ -framework SDL2 -framework SDL2_image -framework lSDL2_mixer -framework SDL2_ttf

# Diretivas de compilacao
FLAGS = -std=c++11 -Wall -Wextra -g -v

# Paths
INC_PATH = include
SRC_PATH = src
BIN_PATH = bin
OBJ_PATH = object

# Binario para execucao
BIN = $(BIN_PATH)/$(EXEC)

# Variavel com uma lista de todos arquivos .cpp em SRC_PATH
SRC = $(wildcard $(SRC_PATH)/*.cpp)

# Objects para compilação
OBJ = $(patsubst $(SRC_PATH)/%.cpp, $(OBJ_PATH)/%.o, $(SRC))

all: $(OBJ)
	$(COMPILER) $(OBJ) $(LIBS) $(FLAGS) -o $(EXEC)

%.o: $(patsubst $(OBJ_PATH)/%.o, $(SRC_PATH)/%.cpp, $@)
	$(COMPILER) -c $(FLAGS) $(patsubst $(OBJ_PATH)/%.o, $(SRC_PATH)/%.cpp, $@) -o $@

clean:
	rm -f $(OBJ) *~






