CC = gcc -Wall
BUILD_DIR_NAME = build
CLI_LIB_NAME = cli
DP_LIB_NAME = dir_process

build: clean
	mkdir $(BUILD_DIR_NAME)
	make cli; make dp
	$(CC) -c main.c -o $(BUILD_DIR_NAME)/main.o
	$(CC) $(BUILD_DIR_NAME)/main.o $(BUILD_DIR_NAME)/lib$(CLI_LIB_NAME).a $(BUILD_DIR_NAME)/lib$(DP_LIB_NAME).a -o $(BUILD_DIR_NAME)/main

run: build
	$(BUILD_DIR_NAME)/main "/mnt/c/Users/Jakub/Desktop/test" "#include"

cli:
	$(CC) -c $(CLI_LIB_NAME).c -o $(BUILD_DIR_NAME)/$(CLI_LIB_NAME).o
	ar rcs ./$(BUILD_DIR_NAME)/lib$(CLI_LIB_NAME).a $(BUILD_DIR_NAME)/$(CLI_LIB_NAME).o

dp:
	$(CC) -c $(DP_LIB_NAME).c -o $(BUILD_DIR_NAME)/$(DP_LIB_NAME).o
	ar rcs ./$(BUILD_DIR_NAME)/lib$(DP_LIB_NAME).a $(BUILD_DIR_NAME)/$(DP_LIB_NAME).o

clean:
	rm -rf $(BUILD_DIR_NAME)