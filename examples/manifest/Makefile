CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I../../include -I../../../librid/include
LDFLAGS = -lsodium

SRC_DIR = ../../src
SRC = $(SRC_DIR)/hash.c $(SRC_DIR)/manifest.c

TARGETS = manifest_sign manifest_verify

all: $(TARGETS)

manifest_sign: manifest_sign.c $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ -lsodium

manifest_verify: manifest_verify.c $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ -lsodium

clean:
	rm -f $(TARGETS)

run: $(TARGETS)
	./manifest_sign
	./manifest_verify 036659010eee58010e000000000000000000000000000000000000000000000000deadbeefdeadbeef00000000000000000000000000000000ba542b7203b88c56e1bd81569714f45189dad1b17cd5aaea704cd0b1f674002d54d728c4236dd8cca43b5a98cffff8532887d2857f8d6162fbde3830dc34930d

.PHONY: all clean run
