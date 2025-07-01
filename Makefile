# Compiler and flags
CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -Werror -pedantic

# Source and object files
SRC = src/main.c src/calculator.c src/menu.c
OBJ = $(patsubst src/%.c, build/%.o, $(SRC))
TARGET = build/calc

.PHONY: all clean run build

# Default target: build + run
all: run

# Run the binary
run: build
	@./$(TARGET)

# Build only
build: $(TARGET)

# Link the final executable
$(TARGET): $(OBJ)
	@$(CC) $(CFLAGS) $^ -o $@ -lm

# Compile .c to .o (ensure build dir exists)
build/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# Clean everything
clean:
	@rm -rf build
