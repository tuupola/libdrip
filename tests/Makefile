CC = gcc
CSHAKE_DIR = ../examples/external/cSHAKE128-tiny
CFLAGS = -Wall -Wextra -Wdouble-promotion -Werror=double-promotion -std=c11 -Wno-implicit-fallthrough -I../include -I. -I$(CSHAKE_DIR)
LDFLAGS = -lsodium

SRC_DIR = ../src
SRC = $(SRC_DIR)/manifest.c $(SRC_DIR)/hash.c $(SRC_DIR)/link.c $(SRC_DIR)/det.c

CSHAKE_SRC = $(CSHAKE_DIR)/SP800-185.c \
             $(CSHAKE_DIR)/KeccakSponge.c \
             $(CSHAKE_DIR)/KeccakP-1600-inplace32BI.c

TEST_SRC = unit.c test_manifest.c test_hash.c test_link.c test_det.c

OBJ = $(SRC:.c=.o)
CSHAKE_OBJ = $(CSHAKE_SRC:.c=.o)
TEST_OBJ = $(TEST_SRC:.c=.o)

TARGET = test_runner

all: $(TARGET)

$(TARGET): $(OBJ) $(TEST_OBJ) $(CSHAKE_OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(CSHAKE_DIR)/%.o: $(CSHAKE_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TEST_OBJ) $(CSHAKE_OBJ) $(TARGET)

test: $(TARGET)
	./$(TARGET)

.PHONY: all clean test
