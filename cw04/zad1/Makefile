CC = gcc -Wall
BUILD_DIR_NAME = build
CLI_LIB_NAME = cli
SIGNALS_LIB_NAME = signals

build: clean
	mkdir $(BUILD_DIR_NAME)
	make cli
	$(CC) -c main.c -o $(BUILD_DIR_NAME)/main.o
	$(CC) $(BUILD_DIR_NAME)/main.o $(BUILD_DIR_NAME)/lib$(CLI_LIB_NAME).a -o $(BUILD_DIR_NAME)/main

test: build
	$(BUILD_DIR_NAME)/main ignore

cli:
	$(CC) -c $(CLI_LIB_NAME).c -o $(BUILD_DIR_NAME)/$(CLI_LIB_NAME).o
	ar rcs ./$(BUILD_DIR_NAME)/lib$(CLI_LIB_NAME).a $(BUILD_DIR_NAME)/$(CLI_LIB_NAME).o

signals:
	$(CC) -c $(SIGNALS_LIB_NAME).c -o $(BUILD_DIR_NAME)/$(SIGNALS_LIB_NAME).o
	ar rcs ./$(BUILD_DIR_NAME)/lib$(SIGNALS_LIB_NAME).a $(BUILD_DIR_NAME)/$(SIGNALS_LIB_NAME).o

clean:
	rm -rf $(BUILD_DIR_NAME)