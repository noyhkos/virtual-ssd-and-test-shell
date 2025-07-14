# dir paths
SRC_DIR := src
INC_DIR := includes

# compile options
CC := gcc
CFLAGS := -Wall -I$(INC_DIR)

# target and source
SRCS := $(SRC_DIR)/main.c $(SRC_DIR)/driver_write.c $(SRC_DIR)/driver_read.c $(SRC_DIR)/driver_fullwrite.c $(SRC_DIR)/driver_fullread.c $(SRC_DIR)/testApp.c
TARGET := driver

# build
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@

# clean
clean:
	rm -f $(TARGET)
