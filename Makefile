# Compiler and flags
CC = g++
# Safety and debugging flags:
# -Wall: Enable all warnings
# -Wextra: Enable additional warnings
# -Werror: Treat warnings as errors
# -g: Generate debug info
# -fsanitize=address: Enable Address Sanitizer to detect memory errors
# -fstack-protector-all: Enable stack protection
# -D_FORTIFY_SOURCE=2: Use fortify source for additional runtime checks
# -Iinclude and -Iexternal: Include directories
# -O3: Optimization level (you might remove this when debugging)
# -std=c++20: Use C++20 standard
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address -fstack-protector-all -D_FORTIFY_SOURCE=2 -Iinclude -Iexternal -O3 -std=c++20

# Directories
INC_DIR = include
BIN_DIR = bin

# Source files and output
SRC = main.cpp
TARGET = $(BIN_DIR)/exec

# Rule to build the final program
$(TARGET): $(SRC) $(INC_DIR)/*.hpp
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Clean up build files
clean:
	rm -rf $(BIN_DIR)

# Phony targets
.PHONY: clean test
