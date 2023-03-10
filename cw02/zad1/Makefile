CC = gcc -Wall
BUILD_DIR_NAME = build
CLI_LIB_NAME = cli
SYSTEM_FILE_LIB_NAME = system_file
STDIO_FILE_LIB_NAME = stdio_file

build:
	mkdir $(BUILD_DIR_NAME)
	make cli; make sf; make stdf
	$(CC) -c main.c -o $(BUILD_DIR_NAME)/main.o
	$(CC) $(BUILD_DIR_NAME)/main.o $(BUILD_DIR_NAME)/lib$(CLI_LIB_NAME).a $(BUILD_DIR_NAME)/lib$(SYSTEM_FILE_LIB_NAME).a $(BUILD_DIR_NAME)/lib$(STDIO_FILE_LIB_NAME).a -o $(BUILD_DIR_NAME)/main

run: clean build
	$(BUILD_DIR_NAME)/main o a lorem.txt output.txt

cli:
	$(CC) -c $(CLI_LIB_NAME).c -o $(BUILD_DIR_NAME)/$(CLI_LIB_NAME).o
	ar rcs ./$(BUILD_DIR_NAME)/lib$(CLI_LIB_NAME).a $(BUILD_DIR_NAME)/$(CLI_LIB_NAME).o

sf:
	$(CC) -c $(SYSTEM_FILE_LIB_NAME).c -o $(BUILD_DIR_NAME)/$(SYSTEM_FILE_LIB_NAME).o
	ar rcs ./$(BUILD_DIR_NAME)/lib$(SYSTEM_FILE_LIB_NAME).a $(BUILD_DIR_NAME)/$(SYSTEM_FILE_LIB_NAME).o

stdf:
	$(CC) -c $(STDIO_FILE_LIB_NAME).c -o $(BUILD_DIR_NAME)/$(STDIO_FILE_LIB_NAME).o
	ar rcs ./$(BUILD_DIR_NAME)/lib$(STDIO_FILE_LIB_NAME).a $(BUILD_DIR_NAME)/$(STDIO_FILE_LIB_NAME).o

clean:
	rm -rf $(BUILD_DIR_NAME)