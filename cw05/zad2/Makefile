CC = gcc -Wall
SRC_DIR = src
BUILD_DIR = build
SIGNALS_LIB= signals

build: clean
	mkdir $(BUILD_DIR)
	$(CC) -c $(SRC_DIR)/main.c -o $(BUILD_DIR)/main.o
	$(CC) $(BUILD_DIR)/main.o -o $(BUILD_DIR)/main -lm

test: build
	build/main 0.001 2

clean:
	rm -rf $(BUILD_DIR)