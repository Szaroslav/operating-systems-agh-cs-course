CC = gcc
CFLAGS = -Wall -O3
SRC_DIR = src
BUILD_DIR = build
SOURCE_FILES = $(SRC_DIR)/grid.c $(SRC_DIR)/life.c

all: life
	
life: $(SRC_DIR)/grid.c $(SRC_DIR)/life.c
	mkdir $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SOURCE_FILES) -o $(BUILD_DIR)/life -lncursesw
	
clean:
	rm -rf $(BUILD_DIR)
