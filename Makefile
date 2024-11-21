# Definindo as variáveis do compilador
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

# Nome do executável
TARGET = kdtree_program

# Diretórios dos arquivos fonte, de cabeçalho e para arquivos objeto
SRC_DIR = src
INCLUDE_DIR = inc
OBJ_DIR = build

# Diretórios de bibliotecas (se houver)
LIB_DIRS = 

# Bibliotecas (se houver alguma, por exemplo, Boost ou outras)
LIBS =

# Arquivos fonte
SRC_FILES = $(SRC_DIR)/main.cpp $(SRC_DIR)/KdTree.cpp $(SRC_DIR)/parser.cpp

# Arquivos objeto (no diretório build)
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Regra padrão para compilar o programa
$(TARGET): $(OBJ_FILES)
	$(CXX) $(OBJ_FILES) -o $(TARGET) $(LIB_DIRS) $(LIBS)

# Como compilar os arquivos .cpp para .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)  # Cria o diretório build se não existir
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Limpeza de arquivos objeto e do executável
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Recompilação completa
rebuild: clean $(TARGET)

.PHONY: clean rebuild
