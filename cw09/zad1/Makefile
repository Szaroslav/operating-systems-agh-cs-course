CC = gcc
CFLAGS = -Wall -O3
SRC_DIR = src
BUILD_DIR = build
SOURCE_FILES = $(SRC_DIR)/simulation.c

all: life
	
life: clean
	mkdir $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SOURCE_FILES) -o $(BUILD_DIR)/santa -lpthread

clean:
	rm -rf $(BUILD_DIR)
