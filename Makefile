# Compiler settings
CXX      := g++
CXXFLAGS := -Wall -Wextra -O3 -std=c++17 -fopenmp -Iinclude -MMD -MP
LDFLAGS  := -fopenmp

# Directories (same as before)
SRC_DIR   := src
INC_DIR   := include
BUILD_DIR := build
BIN_DIR   := bin
OUT_DIR   := output

# Files
TARGET    := $(BIN_DIR)/fractal_renderer
SRCS      := $(wildcard $(SRC_DIR)/*.cpp)
OBJS      := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
DEPS      := $(OBJS:.o=.d) # Tracks header dependencies automatically

# Default target
.PHONY: all clean directories

all: directories $(TARGET)

directories:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OUT_DIR)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)
	@echo "Build successful! Run with: ./$(TARGET)"

# Compile object files (no hardcoded header requirement)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Include all automatically generated dependency files
-include $(DEPS)

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR) $(OUT_DIR)/*.bmp
	@echo "Cleaned build and output directories."