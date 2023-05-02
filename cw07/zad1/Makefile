CC = gcc -Wall -O3
SRC_DIR = src
BUILD_DIR = build
COMMON_LIB = common
SEM_LIB = semaphore

build: clean buildir common semaphore
	$(CC) -c $(SRC_DIR)/hairdresser.c -o $(BUILD_DIR)/hairdresser.o
	$(CC) $(BUILD_DIR)/hairdresser.o $(BUILD_DIR)/lib$(COMMON_LIB).a $(BUILD_DIR)/lib$(SEM_LIB).a -o $(BUILD_DIR)/hairdresser -pedantic -D_GNU_SOURCE
	$(CC) $(SRC_DIR)/client.c -o $(BUILD_DIR)/client

buildir:
	mkdir $(BUILD_DIR)

common:
	$(CC) -c $(SRC_DIR)/$(COMMON_LIB).c -o $(BUILD_DIR)/$(COMMON_LIB).o
	ar rcs $(BUILD_DIR)/lib$(COMMON_LIB).a $(BUILD_DIR)/$(COMMON_LIB).o

semaphore:
	$(CC) -c $(SRC_DIR)/$(SEM_LIB).c -o $(BUILD_DIR)/$(SEM_LIB).o
	ar rcs $(BUILD_DIR)/lib$(SEM_LIB).a $(BUILD_DIR)/$(SEM_LIB).o

clean:
	rm -rf $(BUILD_DIR)