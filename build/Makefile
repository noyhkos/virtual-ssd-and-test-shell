# build/Makefile

CC := gcc
CFLAGS := -I../include -Wall -Wextra
BUILD_DIR := ../build
BIN_DIR := ../bin
SRC_DIR := ../src

# Core components
CORE_SRCS := $(SRC_DIR)/core/ssd.c $(SRC_DIR)/core/ssd_api.c
CORE_OBJS := $(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%,$(CORE_SRCS:.c=.o))

# Shell components (testScript을 API로 포함)
SHELL_SRCS := $(SRC_DIR)/shell/TestShell.c $(SRC_DIR)/shell/command_parser.c
SHELL_OBJS := $(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%,$(SHELL_SRCS:.c=.o))

# Test API components
TEST_API_SRCS := $(SRC_DIR)/tests/testScript.c $(SRC_DIR)/tests/test_utils.c
TEST_API_OBJS := $(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%,$(TEST_API_SRCS:.c=.o))

# Utils
UTILS_SRCS := $(SRC_DIR)/utils/file_io.c
UTILS_OBJS := $(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%,$(UTILS_SRCS:.c=.o))

# Targets
TARGETS := $(BIN_DIR)/ssd.exe $(BIN_DIR)/testShell.exe

.PHONY: all clean directories

all: directories $(TARGETS)

$(BIN_DIR)/ssd.exe: $(CORE_OBJS) $(UTILS_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(BIN_DIR)/testShell.exe: $(SHELL_OBJS) $(TEST_API_OBJS) $(UTILS_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<

directories:
	@mkdir -p $(BUILD_DIR)/{core,shell,tests,utils}
	@mkdir -p $(BIN_DIR)

clean:
	rm -rf $(BUILD_DIR)/*
	rm -rf $(BIN_DIR)/*
