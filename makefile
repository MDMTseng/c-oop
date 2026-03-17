.PHONY: all test clean

export CC=gcc
export CFLAGS=-c -Wall -std=c99
export LDFLAGS=

export OBJ_FILE_DIR=obj
export EXE_BIN_DIR=bin

all:
	-mkdir -p $(OBJ_FILE_DIR)
	-mkdir -p $(EXE_BIN_DIR)
	$(MAKE) -C example
	
test:
	$(MAKE) -C test

clean:
	$(MAKE) -C example clean
	$(MAKE) -C test clean
	