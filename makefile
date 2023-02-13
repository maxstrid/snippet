CC := clang++
CFLAGS := -std=c++17 -Wall -O2

SRC_DIR := src
OBJ_DIR := obj

# Set to main b/c if EXE isn't set by default.nix
# something is very very wrong.
EXE ?= main
CONFIG_DIR := $(HOME)/.config/sippet

SRC := $(wildcard $(SRC_DIR)/*.cc)
HEADER := $(wildcard $(SRC_DIR)/*.h)

OBJ  := $(SRC:$(SRC_DIR)/%.cc=$(OBJ_DIR)/%.o)

all: $(EXE)

.PHONY: all

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc $(HEADER)| $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR) $(CONFIG_DIR):
	mkdir -p $@
