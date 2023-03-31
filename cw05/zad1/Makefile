CC = gcc -Wall
SRC_DIR = src
BUILD_DIR = build

build: clean
	mkdir $(BUILD_DIR)
	$(CC) -c $(SRC_DIR)/main.c -o $(BUILD_DIR)/main.o
	$(CC) $(BUILD_DIR)/main.o -o $(BUILD_DIR)/main

test: build
	$(BUILD_DIR)/main

clean:
	rm -rf $(BUILD_DIR)