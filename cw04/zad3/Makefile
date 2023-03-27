CC = gcc -Wall
SRC_DIR = src
BUILD_DIR = build
CATCHER_NAME = catcher
SENDER_NAME = sender
MODE_LIB = mode

build: clean
	mkdir $(BUILD_DIR)
	make mode
	make catcher; make sender

catcher:
	$(CC) -c $(SRC_DIR)/$(CATCHER_NAME).c -o $(BUILD_DIR)/$(CATCHER_NAME).o
	$(CC) $(BUILD_DIR)/$(CATCHER_NAME).o -o $(BUILD_DIR)/$(CATCHER_NAME)

sender:
	$(CC) -c $(SRC_DIR)/$(SENDER_NAME).c -o $(BUILD_DIR)/$(SENDER_NAME).o
	$(CC) $(BUILD_DIR)/$(SENDER_NAME).o $(BUILD_DIR)/lib$(MODE_LIB).a -o $(BUILD_DIR)/$(SENDER_NAME)

mode:
	$(CC) -c $(SRC_DIR)/$(MODE_LIB).c -o $(BUILD_DIR)/$(MODE_LIB).o
	ar rcs ./$(BUILD_DIR)/lib$(MODE_LIB).a $(BUILD_DIR)/$(MODE_LIB).o

test: build
	$(BUILD_DIR)/catcher

clean:
	rm -rf $(BUILD_DIR)