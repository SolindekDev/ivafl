CC=gcc
CFLAGS=-std=c2x -I./include

SRC_DIR=./src
LIB_DIR=./lib
LIB_NAME=ivafl

SRCS=$(shell find $(SRC_DIR) -name '*.c')
OBJS=$(patsubst $(SRC_DIR)/%.c,$(SRC_DIR)/%.o,$(SRCS))

all: lib$(LIB_NAME).a

lib$(LIB_NAME).a: $(OBJS)
	ar rcs $@ $^

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJS) lib$(LIB_NAME).a