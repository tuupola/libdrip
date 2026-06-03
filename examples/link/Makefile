CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I../../include -I../../../librid/include
LDFLAGS = -lsodium

SRC_DIR = ../../src
SRC = $(SRC_DIR)/hash.c $(SRC_DIR)/link.c

TARGET = example_link_sign example_link_verify

all: $(TARGET)

example_link_sign: example_link_sign.c $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ -lsodium

example_link_verify: example_link_verify.c $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ -lsodium

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run