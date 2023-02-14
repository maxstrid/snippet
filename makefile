CC := clang++ -std=c++17
CFLAGS := -Wall -Wpedantic -Wextra -g

SRC_DIR := src
OBJ_DIR := obj

# These are set to blank values b/c they're expected
# to be set by the user/default.nix
EXE ?=
LDLIBS ?=
CONFIG_DIR := $(HOME)/.config/sippet

SRC := $(wildcard $(SRC_DIR)/*.cc)
HEADER := $(wildcard $(SRC_DIR)/*.h)

OBJ  := $(SRC:$(SRC_DIR)/%.cc=$(OBJ_DIR)/%.o)

all: $(EXE)

.PHONY: all

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $(LDLIBS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc $(HEADER)| $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR) $(CONFIG_DIR):
	mkdir -p $@
