CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -pedantic
SRC = src/main.c src/calculator.c
OBJ = $(SRC:.c=.o)
TARGET = calc

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(TARGET)
