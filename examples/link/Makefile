CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I../../include -I../../../librid/include
LDFLAGS = -lsodium

SRC_DIR = ../../src
SRC = $(SRC_DIR)/hash.c $(SRC_DIR)/link.c

TARGET = example_link

all: $(TARGET)

example_link: example_link.c $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ -lsodium

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run