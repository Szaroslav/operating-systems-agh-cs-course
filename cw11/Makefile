CC = gcc -Wall -O3
SRC_DIR = src
BUILD_DIR = build
COMMON_LIB= common

build: clean
	mkdir $(BUILD_DIR)
	$(CC) $(SRC_DIR)/server.c -o $(BUILD_DIR)/server
	$(CC) $(SRC_DIR)/client.c -o $(BUILD_DIR)/client

test: clean build
	clear

clean:
	rm -rf $(BUILD_DIR)
