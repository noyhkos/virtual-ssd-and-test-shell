# dir paths
SRC_DIR := src
INC_DIR := includes

# compile options
CC := gcc
CFLAGS := -Wall -I$(INC_DIR)

# target and source
SRCS := $(SRC_DIR)/ssd.c $(SRC_DIR)/ssd_write.c $(SRC_DIR)/ssd_read.c
TARGET := ssd  

# build
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@

# clean
clean:
	rm -f $(TARGET)
