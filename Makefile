CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

# Executable
TARGET = heuristic

SRC_DIR = src
INCLUDE_DIR = inc
OBJ_DIR = build

LIB_DIRS =

LIBS =

# Source files
SRC_FILES = $(SRC_DIR)/main.cpp $(SRC_DIR)/KdTree.cpp $(SRC_DIR)/parser.cpp $(SRC_DIR)/NearestNeighbourHeuristic.cpp \
			$(SRC_DIR)/TwoOpt.cpp $(SRC_DIR)/ThreeOpt.cpp $(SRC_DIR)/VND.cpp $(SRC_DIR)/ILS.cpp

# Object files (inside build directory)
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

$(TARGET): $(OBJ_FILES)
	$(CXX) $(OBJ_FILES) -o $(TARGET) $(LIB_DIRS) $(LIBS)

# Compile .cpp files to .o files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)  # Creates the build directory if it doesn't exist
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Rebuild the project
rebuild: clean $(TARGET)

.PHONY: clean rebuild
