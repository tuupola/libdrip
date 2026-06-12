CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Wno-implicit-fallthrough -I../../include -isystem ../external/cSHAKE128-tiny

CSHAKE_DIR = ../external/cSHAKE128-tiny
CSHAKE_SRC = $(CSHAKE_DIR)/SP800-185.c \
             $(CSHAKE_DIR)/KeccakSponge.c \
             $(CSHAKE_DIR)/KeccakP-1600-inplace32BI.c

SRC_DIR = ../../src
SRC = $(SRC_DIR)/det.c $(SRC_DIR)/hash.c

TARGETS = det_generate det_verify

all: $(TARGETS)

det_generate: det_generate.c $(SRC) $(CSHAKE_SRC)
	$(CC) $(CFLAGS) -o $@ $^

det_verify: det_verify.c $(SRC) $(CSHAKE_SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGETS)

run: det_generate det_verify
	./det_generate 16376 16376 b41176c5b305e1823a47715c398f575dcc2a4f16bbdeebdc42d6518907f23b72
	./det_verify 2001003ffe3ff80522879e7592f2d155 b41176c5b305e1823a47715c398f575dcc2a4f16bbdeebdc42d6518907f23b72

.PHONY: all clean run run_det_verify
