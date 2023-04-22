CC = gcc -Wall
SRC_DIR = src
BUILD_DIR = build
COMMON_LIB= common

build: clean
	mkdir $(BUILD_DIR)
	$(CC) $(SRC_DIR)/server.c -o $(BUILD_DIR)/server -pedantic -D_GNU_SOURCE
	$(CC) $(SRC_DIR)/client.c -o $(BUILD_DIR)/client

common:
	$(CC) -c $(SRC_DIR)/$(SIGNALS_LIB).c -o $(BUILD_DIR)/$(SIGNALS_LIB).o
	ar rcs ./$(BUILD_DIR)/lib$(SIGNALS_LIB).a $(BUILD_DIR)/$(SIGNALS_LIB).o

clean:
	rm -rf $(BUILD_DIR)