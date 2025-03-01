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
EXTERNAL_DIR = external

# External Libraries (Dear ImGui, ImPlot)
IMGUI_DIR = $(EXTERNAL_DIR)/imgui
IMPLOT_DIR = $(EXTERNAL_DIR)/implot

# Dependencies (OpenGL and GLFW)
LIBS = -lglfw -lGL

# Source files and output
SRC = main.cpp \
      $(IMGUI_DIR)/imgui.cpp \
      $(IMGUI_DIR)/imgui_draw.cpp \
      $(IMGUI_DIR)/imgui_tables.cpp \
      $(IMGUI_DIR)/imgui_widgets.cpp \
      $(IMGUI_DIR)/backends/imgui_impl_glfw.cpp \
      $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp \
      $(IMPLOT_DIR)/implot.cpp \
      $(IMPLOT_DIR)/implot_items.cpp

# Output Executable
TARGET = $(BIN_DIR)/exec

# Rule to build the final program
$(TARGET): $(SRC) $(INC_DIR)/*.hpp
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -I$(IMGUI_DIR) -I$(IMPLOT_DIR) $(SRC) -o $(TARGET) $(LIBS)

# Clean up build files
clean:
	rm -rf $(BIN_DIR)

# Phony targets
.PHONY: clean
