# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# Directories
SRC_DIR = src
BUILD_DIR = build

# Find all source files automatically
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Generate object file names by replacing the source directory with the build directory
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# Target binary
TARGET = $(BUILD_DIR)/task_manager

# Default target
all: $(BUILD_DIR) $(TARGET)

# Linking the final executable, add -lsqlite3 to link with the SQLite library
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lsqlite3

# Compile source files to object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean up the build files
clean:
	rm -f $(OBJS) $(TARGET)
