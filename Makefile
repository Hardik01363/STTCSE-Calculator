CC ?= gcc
CFLAGS ?= -Wall -Wextra -std=c99 -pedantic -Iinclude -O2
LDFLAGS ?= -lm

SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin
TEST_DIR = tests

APP_TARGET = $(BIN_DIR)/calculator
TEST_TARGET = $(BIN_DIR)/test_calculator

APP_SRCS = $(SRC_DIR)/calculator.c $(SRC_DIR)/main.c
APP_OBJS = $(OBJ_DIR)/calculator.o $(OBJ_DIR)/main.o

TEST_SRCS = $(SRC_DIR)/calculator.c $(TEST_DIR)/test_calculator.c
TEST_OBJS = $(OBJ_DIR)/calculator.o $(OBJ_DIR)/test_calculator.o

.PHONY: all run test clean help

all: $(APP_TARGET)

$(APP_TARGET): $(APP_OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
	@ln -sf $(APP_TARGET) calculator
	@ln -sf $(APP_TARGET) adder

$(TEST_TARGET): $(TEST_OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

run: $(APP_TARGET)
	@./$(APP_TARGET)

test: $(TEST_TARGET)
	@./$(TEST_TARGET)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) calculator adder

help:
	@echo "Available Make targets:"
	@echo "  make        - Build the calculator binary"
	@echo "  make run    - Build and run calculator in interactive mode"
	@echo "  make test   - Build and run unit tests"
	@echo "  make clean  - Remove compiled objects, binaries, and symlinks"
	@echo "  make help   - Display this help message"
