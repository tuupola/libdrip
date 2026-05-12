CC = gcc
CFLAGS = -Wall -Wextra -Wdouble-promotion -Werror=double-promotion -std=c99 -I../include -I.
LDFLAGS =

SRC_DIR = ../src
SRC = $(SRC_DIR)/manifest.c

TEST_SRC = unit.c test_manifest.c

OBJ = $(SRC:.c=.o)
TEST_OBJ = $(TEST_SRC:.c=.o)

TARGET = test_runner

all: $(TARGET)

$(TARGET): $(OBJ) $(TEST_OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TEST_OBJ) $(TARGET)

test: $(TARGET)
	./$(TARGET)

.PHONY: all clean test