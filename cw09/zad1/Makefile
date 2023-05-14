CC = gcc
CFLAGS = -Wall -O3
SRC_DIR = src
BUILD_DIR = build
SOURCE_FILES = $(SRC_DIR)/world.c $(SRC_DIR)/common.c $(SRC_DIR)/santa.c $(SRC_DIR)/reindeer.c $(SRC_DIR)/elf.c

all: santa
	
santa: clean
	mkdir $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SOURCE_FILES) -o $(BUILD_DIR)/santa -lpthread

test: santa
	$(BUILD_DIR)/santa

clean:
	rm -rf $(BUILD_DIR)
