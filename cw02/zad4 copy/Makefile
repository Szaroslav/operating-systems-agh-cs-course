CC = gcc -Wall
BUILD_DIR_NAME = build
DIR_BROWSER_LIB_NAME = dir_browser

build: clean
	mkdir $(BUILD_DIR_NAME)
	make dirbrowser
	$(CC) -c main.c -o $(BUILD_DIR_NAME)/main.o
	$(CC) $(BUILD_DIR_NAME)/main.o $(BUILD_DIR_NAME)/lib$(DIR_BROWSER_LIB_NAME).a -o $(BUILD_DIR_NAME)/main

run: build
	$(BUILD_DIR_NAME)/main

dirbrowser:
	$(CC) -c $(DIR_BROWSER_LIB_NAME).c -o $(BUILD_DIR_NAME)/$(DIR_BROWSER_LIB_NAME).o
	ar rcs ./$(BUILD_DIR_NAME)/lib$(DIR_BROWSER_LIB_NAME).a $(BUILD_DIR_NAME)/$(DIR_BROWSER_LIB_NAME).o

clean:
	rm -rf $(BUILD_DIR_NAME)