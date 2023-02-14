CC := g++ -std=c++17
CFLAGS := -Wall -Wpedantic -Wextra -g

SRC_DIR := src
OBJ_DIR := obj

EXE := snippet
LDLIBS := -lboost_program_options -lboost_filesystem
CONFIG_DIR := $(HOME)/.config/sippet

SRC := $(wildcard $(SRC_DIR)/*.cc)
HEADER := $(wildcard $(SRC_DIR)/*.h)

OBJ  := $(SRC:$(SRC_DIR)/%.cc=$(OBJ_DIR)/%.o)

all: $(EXE)

release: CFLAGS += -O3
release: all

.PHONY: all release

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $(LDLIBS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc $(HEADER)| $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR) $(CONFIG_DIR):
	mkdir -p $@
