# Compiler and compiler flags
CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -O3 -std=c++20

# Directories
SRC_DIR = src
INC_DIR = src/inc
BUILD_DIR = build
LIB_DIR = lib

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/**/*.cpp)

# Object files
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))

# Library
LIB_NAME = libComponentSDL.a
LIB_TARGET = $(BUILD_DIR)/$(LIB_NAME)

# Targets
all: $(LIB_TARGET)

$(LIB_TARGET): $(OBJ_FILES)
	ar rcs $@ $^

# Create build directory structure
$(BUILD_DIR):
	mkdir -p $(foreach dir,$(sort $(dir $(OBJ_FILES))),$(dir))

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@ -lSDL2 -lSDL2_image -lSDL2_ttf

clean:
	rm -rf $(BUILD_DIR) $(LIB_TARGET)

.PHONY: all clean
