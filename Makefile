# ----------------------------------------------------
# >>>>>>>>>> UNIX <<<<<<<<<<
# = Distribuições Linux
# = MacOS X com SDL instalado pelo "brew", sem XCode
# ----------------------------------------------------

# Compilador
COMPILER=g++

# Comando para remover pastas
RMDIR = rm -rdf

# Comando para remover arquivos
RM = rm -f

# Bibliotecas
LIBS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

# Diretivas de compilacao
FLAGS = -std=c++11 -g -Wall -Wextra -Wno-unused-parameter

# Paths
INC_PATH = include
SRC_PATH = src
BIN_PATH = bin
OBJ_PATH = object

# Nome do executavel
EXECNAME = play.out

# Listas de arquivos por extensão
BIN = $(BIN_PATH)/$(EXECNAME)
CPP_FILES = $(wildcard $(SRC_PATH)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_PATH)/%.cpp, $(OBJ_PATH)/%.o, $(CPP_FILES))

# ----------------------------------------------------
# >>>>>>>>>> WINDOWS <<<<<<<<<<
# ----------------------------------------------------

ifeq (($OS),Windows_NT)

#Comando para remover um diretório recursivamente
RMDIR = rd /s /q

#comando para deletar um único arquivo
RM = del /q

#Possiíveis paths da SDL. Caso seja possível ter mais de um locak, adicione espaço entre eles
#Por exempolo.: SDL_PATHs = C:/SDL2 D:/Tools/SDL2 C:/dev-tools/SDL2s
SDL_PATH = C:/SDL2/x86_64-w64-mingw32 C:/Tools/msys64/mingw64

SDL_INC_PATH += $(addsuffix /include,$(SDL_PATHS))
LINK_PATH = $(addprefix -L,$(addsufix /lib,$(SDL_PATHS)))
FLAGS += -mwindows
DFLAGS += -mconsole
LIBS := -lmingw32 -lSDL2main $(LIBS)

#nome do executável
EXEC := $(EXEC).exe

else

UNAME_S := $(shell uname -s)
endif


# ----------------------------------------------------
# >>>>>>>>>> MacOS X <<<<<<<<<<
# = (usando os .frameworks) 
# ----------------------------------------------------
# 		ifeq ($(UNAME_S), Darwin)
# 		LIBS = -lm -framework SDL2 -framework SDL2_image -framework SDL2_mixer -framework SDL2_ttf

# 		endif

# ===========================================================
# ===========================================================

# Linkagem a partir dos objetos (.o)
all: $(OBJ_FILES)
	$(COMPILER) $(OBJ_FILES) $(LIBS)  $(FLAGS) -o $(EXECNAME)

# Geração dos objetos a partir dos arquivos src (.cpp)
%.o: $(patsubst $(OBJ_PATH)/%.o, $(SRC_PATH)/%.cpp, $@)
	$(COMPILER) -c $(FLAGS) $(patsubst $(OBJ_PATH)/%.o, $(SRC_PATH)/%.cpp, $@) -o $@

clean:
	rm -f $(OBJ_FILES) *~

