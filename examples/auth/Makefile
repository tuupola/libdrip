CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I../../include

SRC_DIR = ../../src
SRC = $(SRC_DIR)/hash.c $(SRC_DIR)/manifest.c

TARGET = example_auth

all: $(TARGET)

example_auth: example_auth.c $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ -lsodium

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run