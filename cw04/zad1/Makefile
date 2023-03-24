CC = gcc -Wall
SRC_DIR = src
BUILD_DIR = build
SIGNALS_LIB= signals

build: clean
	mkdir $(BUILD_DIR)
	make signals; make exec
	$(CC) -c $(SRC_DIR)/main.c -o $(BUILD_DIR)/main.o
	$(CC) $(BUILD_DIR)/main.o $(BUILD_DIR)/lib$(SIGNALS_LIB).a -o $(BUILD_DIR)/main

test: build
	$(BUILD_DIR)/main ignore
	$(BUILD_DIR)/main handler

signals:
	$(CC) -c $(SRC_DIR)/$(SIGNALS_LIB).c -o $(BUILD_DIR)/$(SIGNALS_LIB).o
	ar rcs ./$(BUILD_DIR)/lib$(SIGNALS_LIB).a $(BUILD_DIR)/$(SIGNALS_LIB).o

exec:
	$(CC) -c $(SRC_DIR)/exec.c -o $(BUILD_DIR)/exec.o
	$(CC) $(BUILD_DIR)/exec.o $(BUILD_DIR)/lib$(SIGNALS_LIB).a -o $(BUILD_DIR)/exec

clean:
	rm -rf $(BUILD_DIR)