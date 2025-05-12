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
