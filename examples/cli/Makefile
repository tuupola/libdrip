CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I../../include

SRC_DIR = ../../src
SRC = $(SRC_DIR)/hash.c $(SRC_DIR)/link.c $(SRC_DIR)/manifest.c

TARGET = drip

all: $(TARGET)

$(TARGET): example_cli.c $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ -lsodium

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
