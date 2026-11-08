CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I../../include -I../../../librid/include
LDFLAGS = -lsodium

SRC_DIR = ../../src
SRC = $(SRC_DIR)/hash.c $(SRC_DIR)/manifest.c $(SRC_DIR)/det.c $(SRC_DIR)/error.c

TARGETS = manifest_sign manifest_verify

all: $(TARGETS)

manifest_sign: manifest_sign.c $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ -lsodium

manifest_verify: manifest_verify.c $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ -lsodium

clean:
	rm -f $(TARGETS)

run: $(TARGETS)
	set -e; \
	out=$$(./manifest_sign); \
	printf '%s\n' "$$out"; \
	./manifest_verify "$$(printf '%s\n' "$$out" | sed -n 's/^.*manifest_verify //p')"

.PHONY: all clean run
