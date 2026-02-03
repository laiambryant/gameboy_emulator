APP_NAME := gameboy_emulator
BIN := $(APP_NAME)
BUILD_DIR := build
LIB_NAME := libgbcore.a
CC ?= gcc
AR ?= ar

C_SRCS := $(wildcard src/*.c)
C_OBJS := $(C_SRCS:src/%.c=$(BUILD_DIR)/%.o)

ifneq ($(OS),Windows_NT)
    EXE :=
else
    EXE := .exe
    CC := gcc
endif

.PHONY: build build-core run run-windows clean tidy help

help:
	@echo "Targets:"
	@echo "  build        Build the emulator"
	@echo "  run          Run with ROM (POSIX shell)"
	@echo "  run-windows  Run with ROM (cmd.exe)"
	@echo "  clean        Remove built binary"
	@echo "  tidy         Run go mod tidy"
	@echo ""
	@echo "Examples:"
	@echo "  make build"
	@echo "  make run ROM=path/to/rom.gb"
	@echo "  make run-windows ROM=path\\to\\rom.gb"

build: build-core
	go build -o $(BIN)$(EXE) .

build-core: $(BUILD_DIR)/$(LIB_NAME)


$(BUILD_DIR)/$(LIB_NAME): $(C_OBJS)
	@mkdir -p $(BUILD_DIR)
	$(AR) rcs $(BUILD_DIR)/$(LIB_NAME) $(C_OBJS)

$(BUILD_DIR)/%.o: src/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) -c $< -Iinclude -Isrc -o $@

run: build
	@if [ -z "$(ROM)" ]; then echo "ROM is required. Usage: make run ROM=path/to/rom.gb"; exit 1; fi
	./$(BIN)$(EXE) $(ROM)

run-windows: build
	@if [ -z "$(ROM)" ]; then echo "ROM is required. Usage: make run-windows ROM=path/to/rom.gb"; exit 1; fi
	./$(BIN)$(EXE) "$(ROM)"

clean:
	@rm -f $(BIN)$(EXE)
	@rm -rf $(BUILD_DIR)

tidy:
	go mod tidy
