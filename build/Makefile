# 빌드 설정
CC := gcc
CFLAGS := -Wall -Wextra -g -I../include

# 디렉토리
SRC_DIR := ../src
BIN_DIR := ../bin
UTILS_DIR := $(SRC_DIR)/utils
CORE_DIR := $(SRC_DIR)/core
SHELL_DIR := $(SRC_DIR)/shell
TESTS_DIR := $(SRC_DIR)/tests

# 타겟 실행파일
SSD_EXEC := $(BIN_DIR)/ssd.exe
SHELL_EXEC := ../testShell.exe
# TEST_EXEC := $(BIN_DIR)/testScript

# 소스 파일
SSD_SRC := $(CORE_DIR)/ssd.c $(UTILS_DIR)/file_io.c
SHELL_SRC := \
	$(SHELL_DIR)/TestShell.c \
	$(SHELL_DIR)/command.c \
	$(UTILS_DIR)/file_io.c \
	$(SHELL_DIR)/command_parser.c \
	$(SRC_DIR)/tests/testScript.c
TEST_SRC := $(TESTS_DIR)/testScript.c $(UTILS_DIR)/file_io.c

# 기본 타겟: 전체 빌드
all: $(SSD_EXEC) $(SHELL_EXEC)

# ssd.exe 빌드
$(SSD_EXEC): $(SSD_SRC)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# testShell.exe 빌드
$(SHELL_EXEC): $(SHELL_SRC)
	$(CC) $(CFLAGS) -o $@ $^

# testScript 빌드
$(TEST_EXEC): $(TEST_SRC)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# 정리
clean:
	rm -f $(SSD_EXEC) $(SHELL_EXEC) $(TEST_EXEC)


# # build/Makefile

# CC := gcc
# CFLAGS := -I../include -Wall -Wextra
# #CFLAGS += -Isrc/utils -Isrc/shell -Isrc/tests

# BUILD_DIR := ../build
# BIN_DIR := ../bin
# SRC_DIR := ../src

# # Core components
# CORE_SRCS := $(SRC_DIR)/core/ssd.c $(SRC_DIR)/core/ssd_api.c
# CORE_OBJS := $(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%,$(CORE_SRCS:.c=.o))

# # Shell components (testScript을 API로 포함)
# SHELL_SRCS := $(SRC_DIR)/shell/TestShell.c $(SRC_DIR)/shell/command_parser.c
# SHELL_OBJS := $(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%,$(SHELL_SRCS:.c=.o))

# # Test API components
# TEST_API_SRCS := $(SRC_DIR)/tests/testScript.c $(SRC_DIR)/tests/test_utils.c
# TEST_API_OBJS := $(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%,$(TEST_API_SRCS:.c=.o))

# # Utils
# UTILS_SRCS := $(SRC_DIR)/utils/file_io.c
# UTILS_OBJS := $(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%,$(UTILS_SRCS:.c=.o))

# # Targets
# TARGETS := $(BIN_DIR)/ssd.exe $(BIN_DIR)/testShell.exe

# .PHONY: all clean directories

# all: directories $(TARGETS)

# $(BIN_DIR)/ssd.exe: $(CORE_OBJS) $(UTILS_OBJS)
# 	$(CC) $(CFLAGS) -o $@ $^

# $(BIN_DIR)/testShell.exe: $(SHELL_OBJS) $(TEST_API_OBJS) $(UTILS_OBJS)
# 	$(CC) $(CFLAGS) -o $@ $^

# $(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
# 	@mkdir -p $(@D)
# 	$(CC) $(CFLAGS) -c -o $@ $<

# directories:
# 	@mkdir -p $(BUILD_DIR)/{core,shell,tests,utils}
# 	@mkdir -p $(BIN_DIR)

# clean:
# 	rm -rf $(BUILD_DIR)/*
# 	rm -rf $(BIN_DIR)/*